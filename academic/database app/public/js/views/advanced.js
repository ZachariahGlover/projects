"use strict";
var hivemind = hivemind || {};

hivemind.Advanced = Backbone.View.extend({

	events: {
		"click #viewUsersButton" : "usersQuery",
		"click #viewBotsButton" : "botsQuery",
		"click #viewRentalsButton" : "rentalsQuery",
		"click #deleteUsersButton" : "deleteUsersQuery",
		"click #deleteBotsButton" : "deleteBotsQuery",
		"click #deleteRentalsButton" : "deleteRentalsQuery",
		"click #createTablesButton" : "createTablesQuery",
		"click #deleteTablesButton" : "deleteTablesQuery",
		"click #generateDataButton" : "generateDataQuery",
		"click #deleteDataButton" : "deleteDataQuery",
		"click #submitQueryButton" : "submitQuery",
		"click #numUsersButton" : "countTuplesQuery",
		"click #numBotsButton" : "countTuplesQuery",
		"click #numRentalsButton" : "countTuplesQuery",
		"click #numAllButton" : "countTuplesQuery",
		"click #countJobsButton" : "countQuery",
		"click #countUserRentalsButton" : "countQuery",
		"click #clearQueryButton" : "clearQuery"
	},

	deleteTablesQuery: function() {
		var query = "SET FOREIGN_KEY_CHECKS = 0; DROP TABLE IF EXISTS users; DROP TABLE IF EXISTS bots; DROP TABLE IF EXISTS rentals; SET FOREIGN_KEY_CHECKS = 1; "
		$("#queryInput").val(query);
	},

	createTablesQuery: function() {
		var query = "CREATE TABLE IF NOT EXISTS users (uid CHAR(32), name VARCHAR(60), email VARCHAR(60) UNIQUE, PRIMARY KEY (uid) ); "
		query += "CREATE TABLE IF NOT EXISTS rentals (rid CHAR(32), owner CHAR(32), job CHAR(16), nodes INT, expiration DATE, PRIMARY KEY (rid), FOREIGN KEY (owner) REFERENCES users(uid) ON DELETE CASCADE);"
		query += "CREATE TABLE IF NOT EXISTS bots (bid CHAR(32), address CHAR(15), rental CHAR(32), PRIMARY KEY (bid), FOREIGN KEY (rental) REFERENCES rentals(rid) ON DELETE SET NULL); "
		$("#queryInput").val(query);
	},

	generateUUID: function() {
		// I did not write this uuid generating function.
		var uuid = 'xxxxxxxxxxxx4xxxyxxxxxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
			var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
			return v.toString(16);
		});
		return uuid;
	},

	deleteDataQuery: function() {
		$("#queryInput").val("DELETE FROM rentals; DELETE FROM users; DELETE FROM bots;");
	},

	countTuplesQuery: function(event) {
		var button = event.target.id;
		if (button.indexOf("Users") != -1) {
			$("#queryInput").val("SELECT COUNT(uid) AS Users FROM users; ");
		}
		else if (button.indexOf("Bots") != -1) {
			$("#queryInput").val("SELECT COUNT(bid) AS Bots FROM bots; ");
		}
		else if (button.indexOf("Rentals") != -1) {
			$("#queryInput").val("SELECT COUNT(rid) AS Rentals FROM rentals; ");
		}
		else if (button.indexOf("All") != -1) {
			$("#queryInput").val("SELECT COUNT(uid) AS Users FROM users; SELECT COUNT(bid) AS Bots FROM bots; SELECT COUNT(rid) AS Rentals FROM rentals; ");
		}
	},

	countQuery: function(event) {
		var button = event.target.id;
		if (button.indexOf("Jobs") != -1) {
			var q = "((SELECT DISTINCT job AS Job, COUNT(job) AS Rentals FROM rentals GROUP BY Job) AS R)";
			var q2 = "((SELECT DISTINCT job AS Job, SUM(nodes) AS Nodes FROM rentals GROUP BY Job) AS N)";
			$("#queryInput").val("SELECT * FROM " + q + " JOIN " + q2 + "ON N.Job=R.Job; ");
		}
		else if (button.indexOf("UserRentals") != -1) {
			var q = "((SELECT DISTINCT owner AS UserID, COUNT(owner) AS Rentals FROM rentals GROUP BY UserID) AS R)";
			var q2 = "((SELECT DISTINCT owner AS UserID2, SUM(nodes) AS Nodes FROM rentals GROUP BY UserID2) AS N)";
			var q3 = "((SELECT * FROM (" + q + " JOIN " + q2 + "ON N.UserID2=R.UserID)) AS D)";
			$("#queryInput").val("SELECT UserID, name AS Username, Rentals, Nodes FROM (users U) JOIN " + q3 + " ON D.UserID=U.uid; ");
		}
	},

	generateDataQuery: function() {
		var query = "";
		var jobs = ["idle", "spam", "bitcoin", "ddos"];
		var u1 = [ "nostalgic", "moldy", "tall", "lazy", "dank", "numerous", "strong", "radical", "weak", "cagey", "abrupt", "extreme", "blue", "present", "versed", "earthy", "spiky", "amused", "sore", "envious", "naive", "arrogant", "astonishing", "instinctive", "fretful", "fluffy", "diligent", "dangerous", "unsightly", "disastrous", "maddening", "fearless", "gentle", "ripe", "super", "frequent", "anxious", "successful", "incredible", "tranquil" ];
		var u2 = [ "deer", "design", "support", "tax", "cave", "quartz", "fowl", "wood", "cent", "change", "industry", "marble", "desk", "quiver", "cup", "pickle", "pie", "business", "tank", "regret", "error", "stem", "ear", "meme", "ticket", "lamp", "brass", "sign", "act", "rainstorm", "toothbrush", "candle", "machine", "achiever", "request", "juice", "engine", "bear", "behavior", "debt" ];
		var u3 = [ "scare", "concentrate", "wreck", "bore", "encourage", "allow", "strengthen", "damage", "invite", "terrify", "trot", "irritate", "tempt", "tame", "consist", "moan", "tumble", "cheer", "call", "handle", "hop", "dress", "fall", "mess", "groan", "succeed", "disagree", "tip", "trap", "save", "float", "care", "explode", "share", "complete", "use", "point", "copy", "impress", "telephone" ];
		var u4 = [ "website", "internet", "email", "mail", "data", "cats", "dogs", "what", "coolstuff", "notcool", "nope", "domain", "stuff", "things", "hackers"];
		var u5 = [ "org", "com", "ca", "biz", "edu", "net", "int", "gov", "uk", "jp", "fr", "us", "ru", "mil", "au", "ch", "se", "cat" ];
		var num_users = Math.floor((Math.random() * 5) + 2);
		for (var i = 0; i < num_users; i++) {
			var uid = this.generateUUID();
			var ru1 = Math.floor((Math.random() * 40));
			var ru2 = Math.floor((Math.random() * 40));
			var ru3 = Math.floor((Math.random() * 40));
			var ru4 = Math.floor((Math.random() * 40));
			var ru5 = Math.floor((Math.random() * 15));
			var ru6 = Math.floor((Math.random() * 18));
			var ru7 = Math.floor((Math.random() * 9999));
			var ru8 = Math.floor((Math.random() * 10));
			var ru9 = Math.floor((Math.random() * 40));
			var ru10 = Math.floor((Math.random() * 10));
			var sep = "";
			var salt = "";
			if (ru8 > 4) {
				salt = "" + ru7;
			}
			if (ru10 < 2) {
				sep = "-";
			}
			else if (ru10 < 7) {
				sep = ".";
			}
		    query += 'INSERT INTO users (uid, name, email) VALUES (\''
		    + uid
		    + '\', '
		    + '\'' + u1[ru1] + " " + u2[ru2]
		    + '\', '
		    + '\'' + u1[ru9] + sep + u3[ru3] + sep + u2[ru4] + salt + '@' + u4[ru5] + '.' + u5[ru6] + '\''
		    + '); ';
		    var num_rentals = Math.floor((Math.random() * 2) + 1);
		    for (var j = 0; j < num_rentals; j++) {
		    	var rid = this.generateUUID();
		    	var work = jobs[Math.floor(Math.random() * 4)];
		    	var num_nodes = Math.floor((Math.random() * 4) + 2);
		    	var month = Math.floor((Math.random() * 12) + 1);
		    	var day = Math.floor((Math.random() * 28) + 1);
		    	query += 'INSERT INTO rentals (rid, owner, job, nodes, expiration) VALUES (\''
			    + rid
			    + '\', \''
			    + uid
			    + '\', \''
			    + work
			    + '\', '
			    + num_nodes
			    + ', '
			    + '\'2016-' + month + '-' + day
			    + '\'); ';
			    for (var k = 0; k < num_nodes; k++) {
			    	var bid = this.generateUUID();
			    	var addr = '' + Math.floor(Math.random() * 256) + '.' + Math.floor(Math.random() * 256) + '.' + Math.floor(Math.random() * 256) + '.' + Math.floor(Math.random() * 256);
			    	query += 'INSERT INTO bots (bid, address, rental) VALUES (\''
				    + bid
				    + '\', \''
				    + addr
				    + '\', \''
				    + rid
				    + '\'); ';
			    }
			}
		}
		$("#queryInput").val(query);
	},

	deleteUsersQuery: function() {
		$("#queryInput").val("DELETE FROM users;");
	},

	deleteBotsQuery: function() {
		$("#queryInput").val("DELETE FROM bots;");
	},

	deleteRentalsQuery: function() {
		$("#queryInput").val("DELETE FROM rentals;");
	},

	usersQuery: function() {
		$("#queryInput").val("SELECT * FROM users;");
	},

	botsQuery: function() {
		$("#queryInput").val("SELECT * FROM bots;");
	},

	rentalsQuery: function() {
		$("#queryInput").val("SELECT * FROM rentals;");
	},

	submitQuery: function() {
		var query = $("#queryInput").val();
		$("#queryInput").val("");
		if (query) {
			Backbone.trigger('submitQueryEvent', query); 
		}
	},

	clearQuery: function() {
		$("#queryTableContent").html("");
		$("#queryInput").val("");
	},

    render: function () {
        this.$el.html(this.template());
        return this;
    }
});
