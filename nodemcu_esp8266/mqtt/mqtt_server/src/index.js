const mqtt = require('mqtt');

const MQTT_BROKER_URI = 'mqtt://mqtt-broker:1883';
const MQTT_TOPIC = 'TOPIC_01';
const client = mqtt.connect(MQTT_BROKER_URI);
 
client.on('connect', () => {
  console.info(`INFO: connected to ${MQTT_BROKER_URI}`);
  client.subscribe(MQTT_TOPIC);
});
 
client.on('message', (topic, message) => {
  console.info(`${topic} MESSAGE: ${message.toString()}`);
});

