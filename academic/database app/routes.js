"use strict";

var uuid = require('uuid');
var config = require("./config");

var mysql = require('mysql');
var database = mysql.createConnection({
	host     : config.dbhost,
	port	 : config.dbport,
	user     : config.dbuser,
	password : config.dbpass,
	database : config.dbname,
	multipleStatements: true,
	dateStrings: true
});
database.connect();

this.initializeTables = function() {
	var q = "CREATE TABLE IF NOT EXISTS users (uid CHAR(32), name VARCHAR(60), email VARCHAR(60) UNIQUE, PRIMARY KEY (uid) ); "
	q += "CREATE TABLE IF NOT EXISTS rentals (rid CHAR(32), owner CHAR(32), job CHAR(16), nodes INT, expiration DATE, PRIMARY KEY (rid), FOREIGN KEY (owner) REFERENCES users(uid) ON DELETE CASCADE);"
	q += "CREATE TABLE IF NOT EXISTS bots (bid CHAR(32), address CHAR(15), rental CHAR(32), PRIMARY KEY (bid), FOREIGN KEY (rental) REFERENCES rentals(rid) ON DELETE SET NULL); "
	database.query(q, function(error, result) {
		if (error != null) {
			console.log("Failed to initialize tables.");
		}
	});
};
this.initializeTables();

// 404 page.
exports.missing = function(req, res) {
    res.status(404).send('404 Not Found.');
};

exports.getQuery = function(req, res) {
	var q = req.query.string;
	database.query(q, function(error, result) {
		if (error == null) {
			var response = [];
			for (var i = 0; i < result.length; i++) {
				if (result[i].constructor.name != "OkPacket"){
					response.push(result[i]);
				}
			}
			res.status(200).send(response);
		}
		else {
			console.log(error);
			res.status(500).send(error);
		}
	});
}

// User routes.

exports.getUsers = function(req, res) {
	if (Object.keys(req.query).length === 0) {
		database.query('SELECT * FROM users', function(error, result) {
			res.status(200).send(result);
		});
	}
	else {
		var b = '(users B) ';
		var r = ' (rentals R) ';
		if (req.query.job) {
			r = ' ((SELECT * FROM rentals E WHERE E.job LIKE \'%' + req.query.job + '%\') AS R) ';
			b = '(' + b + 'JOIN' + r + 'ON B.uid=R.owner) '
		}
		if (req.query.rid) {
			var u = ' ((SELECT * FROM' + r + 'WHERE R.rid LIKE\'%' + req.query.rid + '%\') AS U) '
			b = '(' + b + 'JOIN' + u + 'ON B.uid=U.owner)'
		}
		b = 'SELECT uid, name, email FROM ' + b;
		database.query(b, function(error, result) {
			res.status(200).send(result);
		});
	}
};

exports.addUser = function(req, res) {
	var id = uuid.v1().split('-').join('');
    var post = 'INSERT INTO users (uid, name, email) VALUES (\''
    + id
    + '\', '
    + mysql.escape(req.body.name)
    + ', '
    + mysql.escape(req.body.email)
    + ')';

    database.query(post, function(error, result) {
    	if (error == null) {
    		result.insertId = id;
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

exports.saveUser = function(req, res) {
	var put = 'UPDATE users SET name = \''
	+ req.body.name
	+ '\', email = \''
	+ req.body.email
	+ '\' WHERE uid = \''
	+ req.params.uid
	+ '\'';

	database.query(put, function(error, result) {
    	if (error == null) {
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

exports.deleteUser = function(req, res) {
    var del = 'DELETE FROM users WHERE uid = \''
    + req.params.uid
    + '\'';

    database.query(del, function(error, result) {
    	if (error == null) {
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

// ---

// Bot routes.

exports.getBots = function(req, res) {
	if (Object.keys(req.query).length === 0) {
		database.query('SELECT * FROM bots', function(error, result) {
			res.status(200).send(result);
		});
	}
	else {
		var b = '(bots B) ';
		var r = ' (rentals R) ';
		if (req.query.job) {
			r = ' ((SELECT * FROM rentals E WHERE E.job LIKE\'%' + req.query.job + '%\') AS R) ';
			b = '(' + b + 'JOIN' + r + 'ON B.rental=R.rid)'
		}
		if (req.query.uid) {
			var u = ' ((SELECT * FROM' + r + 'WHERE R.owner LIKE\'%' + req.query.uid + '%\') AS U) '
			b = '(' + b + 'JOIN' + u + 'ON B.rental=U.rid)'
		}
		b = 'SELECT bid, address, rental FROM ' + b;
		database.query(b, function(error, result) {
			res.status(200).send(result);
		});
	}
};

exports.addBot = function(req, res) {
	var id = uuid.v1().split('-').join('');
    var post = 'INSERT INTO bots (bid, address, rental) VALUES (\''
    + id
    + '\', '
    + mysql.escape(req.body.address)
    + ', '
    + mysql.escape(req.body.rental)
    + ')';

    database.query(post, function(error, result) {
    	if (error == null) {
    		result.insertId = id;
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

exports.saveBot = function(req, res) {
	var put = 'UPDATE bots SET address = \''
	+ req.body.address
	+ '\', rental = \''
	+ req.body.rental
	+ '\' WHERE bid = \''
	+ req.params.bid
	+ '\'';

	database.query(put, function(error, result) {
    	if (error == null) {
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

exports.deleteBot = function(req, res) {
    var del = 'DELETE FROM bots WHERE bid = \''
    + req.params.bid
    + '\'';

    database.query(del, function(error, result) {
    	if (error == null) {
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

// ---

// Rental routes.

exports.getRentals = function(req, res) {
	database.query('SELECT * FROM rentals', function(error, result) {
		res.status(200).send(result);
	});
};

exports.addRental = function(req, res) {
	var id = uuid.v1().split('-').join('');
	database.query('SELECT * FROM bots WHERE rental IS NULL', function(error, result) {

		var n = req.body.nodes;
		if (n > result.length) {
			n = result.length;
		}

		if (n <= 0) {
			var post = 'INSERT INTO rentals (rid, owner, nodes, job, expiration) VALUES (\''
		    + id
		    + '\', '
		    + mysql.escape(req.body.owner)
		    + ', '
		    + mysql.escape(n)
		    + ', '
		    + mysql.escape(req.body.job)
		    + ', '
		    + mysql.escape(req.body.expiration)
		    + ')';
		    database.query(post, function(error2, result2) {
		    	if (error2 == null) {
		    		result.insertId = id;
		    		res.status(200).send(result2);
		    	}
		    	else {
		    		// Have to fix bot rental ids.
		    		res.status(500).send(error2);
		    	}
			});
		}
		else {
			var put = '';
			for (var i = 0; i < n; i++) {
				put = put
				+ 'UPDATE bots SET rental=\''
				+ id
				+ '\' WHERE bid=\''
				+ result[i].bid
				+ '\'; ';
			}
			var post = 'INSERT INTO rentals (rid, owner, nodes, job, expiration) VALUES (\''
		    + id
		    + '\', '
		    + mysql.escape(req.body.owner)
		    + ', '
		    + mysql.escape(n)
		    + ', '
		    + mysql.escape(req.body.job)
		    + ', '
		    + mysql.escape(req.body.expiration)
		    + ')';
			database.query(post, function(error2, result2) {
		    	if (error2 == null) {
				    database.query(put, function(error3, result3) {
				    	if (error3 == null) {
				    		result.insertId = id;
				    		res.status(200).send(result3);
				    	}
				    	else {
				    		res.status(500).send(error3);
				    	}
					});
		    	}
		    	else {
		    		res.status(500).send(error2);
		    	}
			});
		}
    });
};

exports.saveRental = function(req, res) {
	var put = 'UPDATE rentals SET owner = \''
	+ req.body.owner
	+ '\', nodes = \''
	+ req.body.nodes
	+ '\', job = \''
	+ req.body.job
	+ '\', expiration = \''
	+ req.body.expiration
	+ '\' WHERE rid = \''
	+ req.params.rid
	+ '\'';
	database.query(put, function(error, result) {
    	if (error == null) {
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

exports.deleteRental = function(req, res) {
    var del = 'DELETE FROM rentals WHERE rid = \''
    + req.params.rid
    + '\'';
    database.query(del, function(error, result) {
    	if (error == null) {
    		res.status(200).send(result);
    	} else {
    		res.status(500).send(error);
    	}
	});
};

// ---
