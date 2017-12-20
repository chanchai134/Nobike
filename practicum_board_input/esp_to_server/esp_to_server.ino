#include <ESP8266WiFi.h>

//#define DEBUG

void LOG(const char* str) {
  #ifdef DEBUG
  Serial.print(str);
  #endif
}

void LOG(const char *str, size_t length) {
  #ifdef DEBUG
  Serial.write(str, length);
  #endif
}

const char SSID[] = "PHANMSI";
const char PASSWORD[] = "phan1840";

int status = WL_IDLE_STATUS;
const IPAddress HOTSPOT_ADDR(192,168,137,1);
const unsigned char HOTSPOT_PORT = 80;

// Initialize the client library
WiFiClient client;

const unsigned char STATE_FRAME_HEADER = 0;
const unsigned char STATE_FLAG = 1;
const unsigned char STATE_PAYLOAD = 2;

const unsigned char STATE_GPS_LONG_LENGTH = 0;
const unsigned char STATE_GPS_LONG_DATA = 1;
const unsigned char STATE_GPS_LONG_DIR = 2;
const unsigned char STATE_GPS_LAT_LENGTH = 3;
const unsigned char STATE_GPS_LAT_DATA = 4;
const unsigned char STATE_GPS_LAT_DIR = 5;

const unsigned char HEADER_FRAME[] = { 0xFF, 0x1F, 0x2F, 0x3F, 0x4F };
const unsigned char HEADER_FRAME_LENGTH = sizeof(HEADER_FRAME) / sizeof(unsigned char);
unsigned char header_index = 0;
unsigned char header_flag = 0;
unsigned char state_main = STATE_FRAME_HEADER;

// FOR GPS DATA
const unsigned char GPS_DATA_BUFFER_SIZE = 128;
unsigned char state_gps = STATE_GPS_LONG_LENGTH;
char gps_data_buffer[2][GPS_DATA_BUFFER_SIZE];
uint8_t gps_data_length[2];
uint8_t gps_data_actual_length[2];

void esp_send_gps_data_to_server() {
  if (client.connected()) {
    client.stop();
  }
  client.connect(HOTSPOT_ADDR, HOTSPOT_PORT);
  
  client.write("GET /nobike/save.php?flag=123&long=");
  LOG("GET /nobike/save.php?flag=123&long=");
  client.write(gps_data_buffer[0], gps_data_actual_length[0]);
  LOG(gps_data_buffer[0], gps_data_actual_length[0]);
  client.write("&lat=");
  LOG("&lat=");
  client.write(gps_data_buffer[1], gps_data_actual_length[1]);
  LOG(gps_data_buffer[1], gps_data_actual_length[1]);
  client.write(" HTTP/1.1\r\nConnection: Close\r\nHost: localhost\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.94 Safari/537.36\r\n\r\n");
  LOG(" HTTP/1.1\r\nConnection: Close\r\nHost: localhost\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.94 Safari/537.36\r\n\r\n");
  
  client.stop();
}

void esp_send_debug(const char *str) {
    if (client.connected()) {
    client.stop();
  }
  client.connect(HOTSPOT_ADDR, HOTSPOT_PORT);
  client.print(str);
  client.stop();
}

void setup() {
  Serial.begin(115200);
  
  LOG("Attempting to connect to WPA network...\n");

  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  LOG("WPA network, CONNECTED\n");
}

/*unsigned char raw_data[] = { 0xFF, 0x1F, 0x2F, 0x3F, 0x4F,
                   123,
                   10,
                   49,51,53,48,46,55,56,52,51,78,
                   11,
                   49,48,48,51,52,46,48,57,55,52,69
};

unsigned char raw_data_index = 0;
*/

void loop() {
  char value;
  if(Serial.available()){
    value = Serial.read(); 
  }
  
  switch (state_main) {
    case STATE_FRAME_HEADER:
      LOG("STATE_FRAME_HEADER\n");
      if (value == HEADER_FRAME[header_index]) {
        header_index++;
        if (header_index >= HEADER_FRAME_LENGTH) {
          state_main = STATE_FLAG;
          header_index = 0;
        }
      } else if (value == HEADER_FRAME[0]) {
        header_index = 1;
      } else {
        header_index = 0;
      }
      break;
    case STATE_FLAG:
      LOG("STATE_FLAG\n");
      header_flag = value;
      switch (header_flag) {
        case 123: // GPS DATA
          gps_data_length[0] = 0;
          gps_data_length[1] = 0;
          gps_data_actual_length[0] = 0;
          gps_data_actual_length[1] = 0;
          state_gps = STATE_GPS_LONG_LENGTH;
          state_main = STATE_PAYLOAD;
          break;
      }
      break;
    case STATE_PAYLOAD:
      LOG("STATE_PAYLOAD\n");
      switch (header_flag) {
        case 123:
          switch (state_gps) {
            case STATE_GPS_LONG_LENGTH:
              gps_data_length[0] = value;
              state_gps = STATE_GPS_LONG_DATA;
              LOG("STATE_GPS_LONG_LENGTH\n");
              break;
            case STATE_GPS_LONG_DATA:
              gps_data_buffer[0][gps_data_actual_length[0]] = value;
              gps_data_actual_length[0]++;
              LOG("STATE_GPS_LONG_DATA\n");
              if (gps_data_actual_length[0] < GPS_DATA_BUFFER_SIZE) {
                if (gps_data_actual_length[0] >= gps_data_length[0]) {
                  state_gps = STATE_GPS_LAT_LENGTH;
                }
              } else {
                state_main = STATE_FRAME_HEADER;
              }
              break;
            case STATE_GPS_LAT_LENGTH:
              LOG("STATE_GPS_LAT_LENGTH\n");
              gps_data_length[1] = value;
              state_gps = STATE_GPS_LAT_DATA;
              break;
            case STATE_GPS_LAT_DATA:
              LOG("STATE_GPS_LAT_DATA\n");
              gps_data_buffer[1][gps_data_actual_length[1]] = value;
              gps_data_actual_length[1]++;

              if (gps_data_actual_length[1] < GPS_DATA_BUFFER_SIZE) {
                if (gps_data_actual_length[1] >= gps_data_length[1]) {
                  esp_send_gps_data_to_server();
                  state_main = STATE_FRAME_HEADER;
                }
              } else {
                state_main = STATE_FRAME_HEADER;
              }
              break;
          }
          break;
      }
      break;
  }
}
