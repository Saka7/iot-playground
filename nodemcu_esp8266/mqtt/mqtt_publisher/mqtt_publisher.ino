#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);

const char* SSID = "<WIFI SID>";
const char* WIFI_PASSWORD = "<WIFI PASSWORD>";

const char* MQTT_HOST = "<MQTT HOST>";
const char* MQTT_TOPIC = "TOPIC_01"; // Default MQTT topic
const unsigned short MQTT_PORT = 1883; // Default MQTT PORT

const unsigned short SENSOR_PIN_01 = D8;
const unsigned short LED_PIN_01 = D1;

WiFiClient wifiClient;
MqttClient mqtt(wifiClient);

unsigned short sensor_value = 0;

// Serial monitor set-up for debugging
void setup_esp_serial() {
  Serial.begin(9600);
  ESPserial.begin(115200);
  ESPserial.println("AT+IPR=9600");

  delay(1000);

  ESPserial.end();
  ESPserial.begin(9600);
  Serial.println("Ready");
  ESPserial.println("AT+GMR");
}

void setup_wifi() {
  WiFi.begin(SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void setup_mqtt() {
  if (!mqtt.connect(MQTT_HOST, MQTT_PORT)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqtt.connectError());

    while (1);
  }

  // mqtt.subscribe(MQTT_TOPIC);
}

void setup_pins() {
  pinMode(LED_PIN_01, OUTPUT);
}

void setup() {
  setup_esp_serial();
  setup_wifi();
  setup_mqtt();
  setup_pins();
}

void mqtt_send_sensor_value(const char* topic, unsigned short value) {
  mqtt.beginMessage(topic);
  mqtt.print(value);
  mqtt.endMessage();
}

void loop() {
  sensor_value = analogRead(SENSOR_PIN_01);

  if (sensor_value > 0) {
    mqtt_send_sensor_value(MQTT_TOPIC, sensor_value);
    digitalWrite(LED_PIN_01, HIGH);
    delay(300);
  } else {
    digitalWrite(LED_PIN_01, LOW);
  }

  delay(100);
}
