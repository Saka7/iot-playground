#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

#include "./config.h"

SoftwareSerial ESPserial(2, 3);

HTTPClient http;
std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

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

		Serial.println(v);

		if (v >= MIN_ALARMING_GAS_VALUE) {
				digitalWrite(LED_PIN_01, HIGH);
				const String body = "{\"v\": " + String(v) + "}";
				const String result = post_request("/", body);

				Serial.println(result);

				delay(HTTP_REQUEST_DELAY);
		} else {
				digitalWrite(LED_PIN_01, LOW);
		}

		delay(SENSOR_DELAY);
}
