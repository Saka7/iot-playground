# NodeMCU V3 ESP8266 HTTP EXAMPLE


## HTTP CLIENT

Sends http post request on Sensor touch. Blinks LED on response.

GPIO-s:
- Sensor - D8
- LED - D1

```sh
make install_boards # if not installed
make compile
make uplaod
```

## HTTP SERVER

Simple express-based server runs on port 3000.

```sh
npm i
npm start
```

