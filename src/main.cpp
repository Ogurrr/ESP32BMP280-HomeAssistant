#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BMP280.h>

// Wi-Fi and MQTT configuration
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "192.168.X.X"; // Replace with your Home Assistant MQTT server IP

WiFiClient espClient; // Wi-Fi client object
PubSubClient client(espClient); // MQTT client object

// Create BMP280 object
Adafruit_BMP280 bmp;

// Function to connect to Wi-Fi
void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi.");
}

// Function to reconnect to MQTT server if connection is lost
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) { // Attempt to connect to the MQTT server
      Serial.println("Connected.");
    } else {
      Serial.print("Error, retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  setup_wifi(); // Connect to Wi-Fi
  client.setServer(mqtt_server, 1883); // Set MQTT server and port

  // Initialize BMP280 sensor
  if (!bmp.begin()) {
    Serial.println("Failed to find BMP280 sensor. Check wiring!");
    while (1); // Halt if the sensor is not detected
  }

  Serial.println("BMP280 sensor initialized successfully.");
}

void loop() {
  // Reconnect to MQTT if disconnected
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Maintain MQTT connection

  // Read temperature and pressure from BMP280
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // Convert pressure to hPa

  // Send data every 5 seconds
  static unsigned long last_time = 0;
  if (millis() - last_time > 5000) {
    last_time = millis();

    // Convert temperature and pressure to strings
    String payload_temp = String(temperature);
    String payload_pressure = String(pressure);

    // Publish the temperature and pressure data to MQTT topics
    client.publish("home/esp/temperature", payload_temp.c_str());
    client.publish("home/esp/pressure", payload_pressure.c_str());

    // Log data to the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa");
  }
}
