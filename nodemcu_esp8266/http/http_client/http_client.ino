#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);
HTTPClient http;

const unsigned short SENSOR_PIN_01 = D8;
const unsigned short LED_PIN_01 = D1;

const char* SSID = "<WIFI SID>";
const char* WIFI_PASSWORD = "<WIFI PASSWORD>";
const char* BASE_URL = "<HTTP SERVICE URL -> PROTOCOL://HOST:PORT>";

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

void setup_pins() {
  pinMode(LED_PIN_01, OUTPUT);
}

void setup() {
  setup_esp_serial();
  setup_wifi();
  setup_pins();
}

String get_request(String path) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(BASE_URL + path);
    int httpCode = http.GET();
    String payload = httpCode > 0 ? http.getString() : "ERROR";
    http.end();

    return payload;
  }
}

String post_request(String path, String req_body) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(BASE_URL + path);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(req_body);
    String payload = httpCode > 0 ? http.getString() : "ERROR";
    http.end();

    return payload;
  }
}

void loop() {
  sensor_value = analogRead(SENSOR_PIN_01);

  if (sensor_value > 0) {
    const String req_body = "{\"target\": \"VALUE\"}";
    const String result = post_request("/", req_body);

    digitalWrite(LED_PIN_01, HIGH); // Blink LED on response

    Serial.println(result);
    delay(1000);
  } else {
    digitalWrite(LED_PIN_01, LOW);
  }

  delay(300);
}
