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

void callback(char* topic, byte* payload, unsigned int length) {
  // Convert payload to string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Message received: ");
  Serial.println(message);

  // Control LED based on message
  if (message == "ON") {
    digitalWrite(ledPin, LOW);  // LOW turns on the LED (active low)
    Serial.println("LED ON");
  } 
  else if (message == "OFF") {
    digitalWrite(ledPin, HIGH); // HIGH turns off the LED
    Serial.println("LED OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect with credentials
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Subscribe to topic
      client.subscribe(mqtt_topic);
      Serial.println("Subscribed to topic");
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
  digitalWrite(ledPin, HIGH);  // Initially LED is off
  
  Serial.begin(115200);
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  stepper.runSpeed();
}