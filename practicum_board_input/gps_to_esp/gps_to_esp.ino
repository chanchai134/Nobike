#include <stdlib.h>
#include <SoftwareSerial.h>

//#define DEBUG

struct GpsInfo {
  uint8_t long_offset;
  uint8_t long_length;
  int8_t long_dir;
  uint8_t lat_offset;
  uint8_t lat_length;
  int8_t lat_dir;
};

void LOG(const char *str, size_t length) {
  #ifdef DEBUG
  Serial.write(str, length);
  #endif
}

void LOG(const char *str) {
  #ifdef DEBUG
  Serial.write(str);
  #endif
}

SoftwareSerial GPS(PIN_PB2, PIN_PB0);//Rx Tx

const char HEADER_FLAG[] = { 0xFF, 0x1F, 0x2F, 0x3F, 0x4F };

char TARGET_HEADER[] = "GPRMC";
const unsigned char TARGET_HEADER_LENGTH = sizeof(TARGET_HEADER) - 1;
char buffer[128];// = "$GPRMC,125150.000,A,1350.7564,N,10034.0909,E,2.04,26.69,131117,,,A*54\n";
unsigned char bufferLength = -1;//sizeof(buffer) - 2;
GpsInfo info;

inline void addBuffer(int8_t ch) {
  buffer[++bufferLength] = ch;
}

inline bool isEnd() {
  return buffer[bufferLength] == '\n';
}

inline void clearBuffer() {
  bufferLength = -1;
}

inline bool strCompare(int8_t *str1, int8_t *str2, int length) {
  for (int i = 0; i < length; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}

void send_gps_position_to_esp(GpsInfo info) {
  Serial.write(HEADER_FLAG, sizeof(HEADER_FLAG));
  //Serial.write((char)(5 + info.long_length + info.lat_length));
  Serial.write((char)123); // GPS INFO
  Serial.write(info.long_length + 1);
  Serial.write(buffer + info.long_offset, info.long_length);
  Serial.write(info.long_dir);
  Serial.write(info.lat_length + 1);
  Serial.write(buffer + info.lat_offset, info.lat_length);
  Serial.write(info.lat_dir);
}

bool parseGps(GpsInfo *gps) {

  if (buffer[0] != '$') {
    return false;
  }
  //Serial.println("HEADER BEGIN PASSED.");
  if (!strCompare(TARGET_HEADER, buffer + 1, TARGET_HEADER_LENGTH)) {
    return false;
  }
  //Serial.println("HEADER MATCHING PASSED.");

  int index = 7;
  while (index <= bufferLength && buffer[index] != ',')
    index++;

  if (index < bufferLength && buffer[index + 1] == 'V') {
    return false;
  }

  //Serial.println("POSITION FLAG PASSED.");

  index += 3;

  gps->long_offset = index;
  int length = 0;
  while (index <= bufferLength && buffer[index] != ',') {
    index++;
    length++;
  }
  gps->long_length = length;

  if (index >= bufferLength) {
    return false;
  }

  gps->long_dir = buffer[index + 1];

  index += 3;

  gps->lat_offset = index;
  length = 0;
  while (index <= bufferLength && buffer[index] != ',') {
    index++;
    length++;
  }
  gps->lat_length = length;

  //Serial.println("LATITUDE PASSED.");

  if (index >= bufferLength) {
    return false;
  }
  gps->lat_dir = buffer[index + 1];

  return true;
}

void setup() {
  Serial.begin(115200);
  GPS.begin(9600);
  //mega.begin(9600);
  //Serial.println("PRACTICUM READY!");
  LOG("READY\n");
}

uint32_t last_esp_sent_time = 0;

void loop() {
  if (GPS.available()) {
    char value = GPS.read();
    addBuffer(value);
    if (isEnd()) {
      LOG("GPS END");
      if (parseGps(&info)) {
        LOG("READY TO SENDING");
        uint32_t cur_time = millis();
        if (cur_time - last_esp_sent_time >= 5000) {
          LOG("SENT");
          send_gps_position_to_esp(info);
          last_esp_sent_time = cur_time;
        }
      }
      clearBuffer();
    }
  }
}
