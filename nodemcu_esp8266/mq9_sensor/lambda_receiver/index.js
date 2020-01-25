const {promisify} = require('util');
const https = require('https');
const qs = require('querystring');

const AWS = require('aws-sdk');
const dynamodb = new AWS.DynamoDB();

async function saveItem(data) {
    const TABLE_NAME = 'NODEMCU_MQ9';

    return dynamodb.putItem({
        TableName: TABLE_NAME,
        Item: {
            t: { N: String(Date.now()) },
            v: { N: String(data) },
        }
    }).promise();
}

async function sendAlert(value) {
    const TOKEN = process.env.TELEGRAM_BOT_TOKEN;
    const CHAT_ID = process.env.TELEGRAM_CHAT_ID;
    const URL = `https://api.telegram.org/bot${TOKEN}/sendMessage`;
    const text = `🚨 MQ9_SENSOR_VALUE: ${value}`;

    const url = [URL, qs.stringify({chat_id: CHAT_ID, text})].join('?');
    return promisify(https.get)(url).catch(error => void 0);
}

exports.handler = async event => {
    if (!event.body) return {
        statusCode: 400,
        body: 'EMPTY_BODY'
    };
    
    const body = JSON.parse(event.body);
    
    await Promise.all([
        saveItem(body.v),
        sendAlert(body.v),
    ]);
    
    return {
        statusCode: 201,
        body: 'OK'
    };
};
