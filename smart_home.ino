#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi Configuration
const char* ssid = "YOUR_WIFI_SSID";       // Ganti dengan SSID WiFi Anda
const char* password = "YOUR_WIFI_PASSWORD"; // Ganti dengan password WiFi Anda

// MQTT Broker Configuration
const char* mqtt_server = "test.mosquitto.org";

// Initialize objects
WiFiClient espClient;
PubSubClient client(espClient);

// Message buffer for MQTT
char msg[50];
long lastMsg = 0;
int value = 0;

// Setup WiFi connection
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Callback function for MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Pesan baru: [");
  Serial.print(topic);
  Serial.print("] ");
  
  // Print message payload
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Control LED based on message
  if ((char)payload[0] == 'O' && (char)payload[1] == 'N') {
    digitalWrite(LED_BUILTIN, LOW); // Turn LED on (active low)
  } else if ((char)payload[0] == 'O' && (char)payload[1] == 'F') {
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED off
  }
}

// Reconnect to MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan MQTT...");
    if (client.connect("NodeMCUClient")) {
      Serial.println("Terhubung");
      client.subscribe("smartHome/hanif/lampu");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publish temperature data every 5 seconds
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    value++;
    snprintf(msg, 50, "Suhu %d°C", 25 + (value % 5)); // Simulate temperature data
    Serial.print("Publish pesan: ");
    Serial.println(msg);
    client.publish("smartHome/hanif/suhu", msg);
  }
}
