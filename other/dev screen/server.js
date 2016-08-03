// Set some variables that won't change.
var serverport = 41337;
var owm_key = '&APPID=a802a7042548d1f8d72b40894d2d5b28';

// Get our required frameworks.
var koa = require('koa');
var router = require('koa-route');
var bodyParser = require('koa-bodyparser');
var request = require('request');

// Create the app.
var app = koa();
app.use(bodyParser());

// Triggered by a get request with url '/api/weather/'
// Uses the IP of the request source and two external APIs to get the data and return it.
app.use(router.get(('/api/weather'), function *(next) {
	var self = this;

	// Get the source IP.
	self.source = this.request.ip;

	// This can be uncommented to spoof an IP for testing.
	//self.source = '54.152.9.132';

	// Use a different API request if the IP is local.
	var ip_req;
	if (self.source === '::1') {
		ip_req = 'http://ip-api.com/json/';
	}
	else {
		ip_req = 'http://ip-api.com/json/' + self.source;
	}

	// Use a promise so we can set the response after the two API calls.
	yield new Promise((resolve, reject) => {

		// Get the latitude and longitude of the IP.
		request(ip_req, function(error, response, body) {
			var parsed = JSON.parse(body);
			self.source = parsed.query;

			// Store the latitude and longitude.
			self.lat = parsed.lat;
			self.lon = parsed.lon;

			// Generate the weather API request and send it off.
			var weather_req = 'http://api.openweathermap.org/data/2.5/weather?lat=' + self.lat + '&lon=' + self.lon + owm_key;
			request(weather_req, function(error, response, body) {

				// Parse the weather API response.
				var parsed = JSON.parse(body);

				// Store the results (also the temperature we get is in Kelvin... so I convert to celsius).
				self.temp = (parseFloat(parsed.main.temp) - 273.15).toPrecision(4);
				self.weatherCode = parsed.weather[0].id;
				self.weatherDesc = parsed.weather[0].description;

				// Set the server response object and resolve the promise.
				self.body = {'ip':self.source, 'latitude':self.lat, 'longitude':self.lon, 'temperature':self.temp, 'weather code':self.weatherCode, 'weather description':self.weatherDesc};
				resolve();
			});
		});
	});

	// Allow the next middleware to be called.
	yield next;
}));

// Middleware for static files.
app.use(require('koa-static')(__dirname + '/public'));

// Starts the server.
app.listen(serverport);
console.log('Listening on port ' + serverport);