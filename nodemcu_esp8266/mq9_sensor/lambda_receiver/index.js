const AWS = require('aws-sdk');
const dynamodb = new AWS.DynamoDB();

const TABLE_NAME = 'NODEMCU_MQ9';

exports.handler = async event => {
    if (!event.body) return {
        statusCode: 400,
        body: 'EMPTY_BODY'
    };
    
    const body = JSON.parse(event.body);
    
    await dynamodb.putItem({
        TableName: TABLE_NAME,
        Item: {
            t: { N: String(Date.now()) },
            v: { N: String(body.v) },
        }
    }).promise();
            
    return {
        statusCode: 201,
        body: 'OK'
    };
};

