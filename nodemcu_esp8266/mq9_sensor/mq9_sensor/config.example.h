const unsigned short SENSOR_PIN_01 = 17; // A0
const unsigned short LED_PIN_01 = 15; // D8

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
