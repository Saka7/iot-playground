# IoT Playground

## Microcontroller Boards

### NodeMCU (V3 ESP8266)

### Arduino CLI Set-up

- Follow the [Arduino Cli](https://github.com/arduino/arduino-cli) documentation to install `arduino-cli` tool.

- Add esp8266 repo to the index

```sh
arduino-cli core update-index --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
- Install esp8266 generic board

```sh
arduino-cli board install esp8266:esp8266:generic
```

### Compile and upload

Compile:

```sh
arduino-cli compile --fqbn esp8266:esp8266:generic <path-to-folder>
```

Upload:

```sh
arduino-cli upload -p <usb-link> --fqbn esp8266:esp8266:generic <path-to-folder>
```

### Troubleshooting

Set permissions to usb-link:
```sh
sudo chmod a+rw /dev/ttyUSB0
```


### Projects

- [base](nodemcu_esp8266/base/) - Basic Example (serial monitor);
- [http](nodemcu_esp8266/http/) - Simple JSON HTTP GET / POST requests via WiFi module (ESP8266);
- [mqtt](nodemcu_esp8266/mqtt/) - Simple MQTT Publisher (IoT Device) / Consumer (NodeJS app) via WiFi module (ESP8266);

### Pins

```
LED_BUILTIN = blue LED
0 = D3
1 = TX
2 = blue LED
3 = RX
4 = D2
5 = D1
12 = D6
13 = D7
14 = D5
15 = D8
16 = D0
```

