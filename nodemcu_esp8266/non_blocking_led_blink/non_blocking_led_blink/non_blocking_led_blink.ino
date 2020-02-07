#include <SoftwareSerial.h>

typedef struct LED_PIN {
	const byte pin;
	byte state;
	unsigned long prev_time;
};

LED_PIN LED_PIN_01 = {
	.pin = 14, // D5
	.state = 0,
	.prev_time = 0
};

LED_PIN LED_PIN_02 = {
	.pin = 15, // D8
	.state = 0,
	.prev_time = 0
};

SoftwareSerial ESPserial(2, 3);

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

void setup() {
		setup_esp_serial();

		pinMode(LED_PIN_01.pin, OUTPUT);
		pinMode(LED_PIN_02.pin, OUTPUT);
}

void blink_pin(LED_PIN* led_pin, unsigned long interval) {
	unsigned long current_time = millis();

	Serial.println(current_time - led_pin->prev_time);

	if((current_time - led_pin->prev_time) > interval) {
		led_pin->prev_time = current_time;
		led_pin->state = !led_pin->state;

		digitalWrite(led_pin->pin, led_pin->state);
	}
}

void loop() {
	blink_pin(&LED_PIN_01, 500);
	blink_pin(&LED_PIN_02, 5000);
}

