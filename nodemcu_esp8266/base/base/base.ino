#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);

const unsigned short SENSOR_PIN_01 = 15; // D8
const unsigned short LED_PIN_01 = 5; // D1

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

void setup_pins() {
  pinMode(LED_PIN_01, OUTPUT);
  pinMode(SENSOR_PIN_01, INPUT);
}

void setup() {
  setup_esp_serial();
  setup_pins();
}

void loop() {
  sensor_value = digitalRead(SENSOR_PIN_01);
  Serial.println(sensor_value);
  delay(300);
}
