# NodeMCU V3 ESP8266 MQTT EXAMPLE


## MQTT PUBLISER

Sends sensor value to MQTT topic on sensor touch using [ArduinoMqttClient](https://github.com/arduino-libraries/ArduinoMqttClient) lib.

```sh
make install_board # if not installed
make compile
make upload
```

Serial Monitor:

```sh
make logs
```

## MQTT CONSUMER

Simple nodejs mqtt consumer

## MQTT BROKER

Eclipse Mosquitto MQTT broker runs on port 1883

```sh
docker-compose up -d
```


