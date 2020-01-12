const express = require('express');
const app = express();

const HTTP_PORT = 3000;

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.post('/', (req, res) => {
	console.info(`${Date.now()} HTTP POST: ${req.body.target}`);
	res.json({status: 'SUCCESS'});
});

app.get('/', (req, res) => {
	console.info(`${Date.now()} HTTP GET`);
	res.json({data: 'VALUES'});
});

app.listen(HTTP_PORT, () => console.info(`Server is listening on port ${HTTP_PORT}`));

