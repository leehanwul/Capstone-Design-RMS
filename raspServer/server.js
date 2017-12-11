var app = require('express')();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var http = require('http');
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
	res.send('Hello Arduino!');
});

io.on('connection', function(socket) {
	socket.on('isUse', function(data) {
		console.log('isUse Message from Arduino: ' +data);
		var req = http.request(useOptions, function(res) {
			console.log('Status: ' +res.statusCode);
			console.log('Headers: ' +JSON.stringify(res.headers));
			res.setEncoding('utf8');
			res.on('data', function (body) {
				console.log('Body: ' +body);
			});
		});
		req.on('error', function(e) {
			console.log('problem with request: ' +e.message);
		});
		var jsonData = '{"no": "' +data.no+ '","flag": "' +data.flag+ '"}';
		console.log('jsonData : ' +jsonData);
		req.write(jsonData);
		req.end();
	});

	socket.on('isBlock', function(data) {
		console.log('isBlock Message from Arduino: ' +data);
		var req = http.request(blockOptions, function(res) {
			console.log('Status: ' +res.statusCode);
			console.log('Headers: ' +JSON.stringify(res.headers));
			res.setEncoding('utf8');
			res.on('data', function (body) {
				console.log('Body: ' +body);
			});
		});
		req.on('error', function(e) {
			console.log('problem with request: ' +e.message);
		});
		var jsonData = '{"no": "' +data.no+ '","flag": "' +data.flag+ '"}';
		console.log('jsonData : ' +jsonData);
		req.write(jsonData);
		req.end();
	});
});

server.listen(3003, function() {
	console.log('Socket IO server listening on port 3003');
});

