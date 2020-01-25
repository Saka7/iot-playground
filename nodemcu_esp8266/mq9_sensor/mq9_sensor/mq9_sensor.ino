#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);

HTTPClient http;
std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

const unsigned short SENSOR_PIN_01 = 17; // A0
const unsigned short LED_PIN_01 = 5; // D1

const unsigned short VOLTAGE = 5;
const float MIN_ALARMING_GAS_VALUE = 2.5;

const unsigned short SENSOR_DELAY = 3000; // 3 seconds
const unsigned short HTTP_REQUEST_DELAY = 15000; // 15 seconds

const char* SSID = "<WiFI SID>";
const char* WIFI_PASSWORD = "<WiFi Password>";
const char* X_API_KEY = "<AWS API GATEWAY API KEY>";
const char* BASE_URL = "<AWS API GATEWAY URL>";

const uint8_t FINGERPRINT[20] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
};

float sensor_value = 0;

// Serial monitor set-up for debugging
void setup_esp_serial() {
        Serial.begin(9600);
        ESPserial.begin(115200);
        ESPserial.println("AT+IPR=9600");

        delay(1000);

        ESPserial.end();
        ESPserial.begin(9600);
        Serial.println("Serial Ready");
        ESPserial.println("AT+GMR");
}

void setup_wifi() {
        WiFi.begin(SSID, WIFI_PASSWORD);

        while (WiFi.status() != WL_CONNECTED) {
                delay(1000);
                Serial.println("WiFi Connecting...");
        }
}

void setup_pins() {
        pinMode(LED_PIN_01, OUTPUT);
        pinMode(SENSOR_PIN_01, INPUT);
}

void setup_tls() {
        client->setFingerprint(FINGERPRINT);
}

void setup() {
        setup_esp_serial();
        setup_pins();
        setup_wifi();
        setup_tls();
}

float gas_value(float mq9_sensor_value) {
        return mq9_sensor_value / 1024 * VOLTAGE;
}

String post_request(String path, String req_body) {
        if (WiFi.status() == WL_CONNECTED) {
                http.begin(*client, BASE_URL + path);

                http.addHeader("content-type", "application/json");
                http.addHeader("x-api-key", X_API_KEY);

                int httpCode = http.POST(req_body);

                String payload = httpCode > 0 ? http.getString() : "ERROR";

                http.end();

                return payload;
        }
}

void loop() {
        sensor_value = analogRead(SENSOR_PIN_01);

        float v = gas_value(sensor_value);

        if (v >= MIN_ALARMING_GAS_VALUE) {
                const String body = "{\"v\": " + String(v) + "}";
                const String result = post_request("/", body);

                Serial.println(result);

                delay(HTTP_REQUEST_DELAY);
        }

        delay(SENSOR_DELAY);
}
