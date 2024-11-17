#include <ESP8266WiFi.h>

// WiFi credentials
const char* ssid = "SSID";
const char* password = "Password";


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  
  Serial.begin(115200);
  setup_wifi();
}

void loop() {

}