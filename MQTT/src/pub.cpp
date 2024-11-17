#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// WiFi credentials
const char* ssid = "SSID";
const char* password = "Password";

// MQTT Broker settings
const char* mqtt_server = "IP Address"; // Replace with mqtt IP
const int mqtt_port = 1883;
const char* mqtt_user = "user1";
const char* mqtt_password = "password1";
const char* mqtt_topic = "esp8266/LED";

// LED Pin
const int ledPin = 2;  // Built-in LED on most ESP8266 boards

WiFiClient espClient;
PubSubClient client(espClient);
bool ledState = false;

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

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect with credentials
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Toggle LED state
  ledState = !ledState;
  digitalWrite(ledPin, ledState);

  // Publish the state
  const char* message = ledState ? "ON" : "OFF";
  client.publish(mqtt_topic, message);
  
  Serial.print("Published: ");
  Serial.println(message);

  // Wait for 2 seconds before next message
  delay(2000);
}