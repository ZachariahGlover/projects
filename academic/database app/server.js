"use strict";

var config = require("./config");
var routes = require('./routes.js');

var bodyParser = require("body-parser");

var express = require('express');
var http = require('http');

var app = express();
var server = http.createServer(app);

app.get('/', function(req, res) {
    res.redirect("./index.html#home");
});

app.use(bodyParser.json({limit: '5mb'}));
app.use(bodyParser.urlencoded({
    extended: true, limit: '5mb'
}));

app.get('/users', routes.getUsers);
app.get('/users/create', routes.getUsers);
app.post('/users', routes.addUser);
app.put('/users/:uid', routes.saveUser);
app.delete('/users/:uid', routes.deleteUser);

app.get('/bots', routes.getBots);
app.get('/bots/create', routes.getBots);
app.post('/bots', routes.addBot);
app.put('/bots/:bid', routes.saveBot);
app.delete('/bots/:bid', routes.deleteBot);

app.get('/rentals', routes.getRentals);
app.post('/rentals', routes.addRental);
app.put('/rentals/:rid', routes.saveRental);
app.delete('/rentals/:rid', routes.deleteRental);

app.get('/advanced', routes.getQuery);

app.use(express.static(__dirname + "/public"));

app.use(routes.missing);

server.listen(config.serverport, config.serverhost);
server.on('listening', function() {
    console.log('Express server started on port %s at %s', server.address().port, server.address().address);
});
