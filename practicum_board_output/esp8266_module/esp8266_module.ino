//http://arduino.esp8266.com/stable/package_esp8266com_index.json

#include <ESP8266WiFi.h>

const char ssid[] = "PHANMSI";
const char password[] = "phan1840";

//int status = WL_IDLE_STATUS;
IPAddress Hotspot_server(192,168,137,1);
const int Hotspot_port = 80;

// Initialize the client library
WiFiClient client;

void setup() {
  bool state = false;
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(10, LOW);
  //Serial.begin(9600);
  //Serial.println("Attempting to connect to WPA network...");
  //Serial.print("SSID: ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    if(state) {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
    state = !state;
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  /////////////////////////////
  digitalWrite(2, HIGH);
  char keep = getstatus();
  if(keep == '0')
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if(keep == '1')
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  if(keep == '2')
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  if(keep == '3')
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
  digitalWrite(10, HIGH);
  /////////////////////////////
}
//4noise
//5light
void loop() {
  char keep = getstatus();
  if(keep == '0')
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if(keep == '1')
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  if(keep == '2')
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  if(keep == '3')
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
}
char getstatus()
{
  client.connect(Hotspot_server, Hotspot_port);
  delay(500);
  while(!client.connected()) {
      //Serial.println("not connected");
      client.connect(Hotspot_server, Hotspot_port);
      delay(500);
  }
  client.print("GET /nobike/esp8266_get.php?ip=");
  client.print(WiFi.localIP());
  client.println(" HTTP/1.1");
  client.println("Host: 192.168.137.1");
  client.println("User-Agent: BuildFailureDetectorESP8266");
  client.print("Connection: close\r\n\r\n");
  String line;
  while (client.connected()) {
    line = client.readStringUntil('\n');
  }
  client.stop();
  return line[0];
}

