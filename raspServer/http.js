var express = require('express');
var app = express();
var http = require('http');
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({extended:true}));
app.use(bodyParser.json());

var useOptions = {
	hostname: '13.124.118.230',
	port: 3000,
	path: '/updateUse',
	method: 'POST',
	headers: {
		'Content-Type': 'application/json',
	}
};

var blockOptions = {
	hostname: '13.124.118.230',
	port: 3000,
	path: '/updateBlock',
	method: 'POST',
	headers: {
		'Content-Type': 'application/json',
	}
};

app.get('/', function(req, res) {
	console.log('raspberrypi main page');
	res.send('Hello Arduino!');
});

app.post('/use', function(req, res) {
	req.accepts('application/json');
	console.log('hi arduino, i am use url on raspberrypi');
	var no = req.body.no;
	var flag = req.body.flag;
	console.log('no : ' +no);
	console.log('flag : ' +flag);
	res.send('use request OK');
	var httpReq = http.request(useOptions, function(response) {
		console.log('Status: ' +response.statusCode);
		console.log('Headers: ' +JSON.stringify(response.headers));
		response.setEncoding('utf8');
		response.on('data', function (body) {
			console.log('Body: ' +body);
		});
	});
	httpReq.on('error', function(e) {
		console.log('problem with request: ' +e.message);
	});
	var jsonData = '{"no": "' +no+ '","flag": "' +flag+ '"}';
	console.log('jsonData : ' +jsonData);
	httpReq.write(jsonData);
	httpReq.end();
});

app.post('/block', function(req, res) {
	req.accepts('application/json');
	console.log('hi arduino, i am block url on raspberrypi');
	var no = req.body.no;
	var flag = req.body.flag;
	console.log('no : ' +no);
	console.log('flag : ' +flag);
	res.send('block request OK');
	var httpReq = http.request(blockOptions, function(response) {
		console.log('Status: ' +response.statusCode);
		console.log('Headers: ' +JSON.stringify(response.headers));
		response.setEncoding('utf8');
		response.on('data', function (body) {
			console.log('Body: ' +body);
		});
	});
	httpReq.on('error', function(e) {
		console.log('problem with request: ' +e.message);
	});
	var jsonData = '{"no": "' +no+ '","flag": "' +flag+ '"}';
	console.log('jsonData : ' +jsonData);
	httpReq.write(jsonData);
	httpReq.end();
});

app.listen(3000, function() {
	console.log('raspberryPi server listening on port 3000');
});
