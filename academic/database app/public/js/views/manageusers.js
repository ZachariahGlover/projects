"use strict";
var hivemind = hivemind || {};

hivemind.ManageUsers = Backbone.View.extend({

	events: {
		"change .input-group-item" : "attributeChange",
		"click #createUserButton" : "createUser",
        "click #saveUserButton" : "saveUser",
        "click #deleteUserButton" : "deleteUser",
        "click #createRentalButton" : "createRental",
        "click #viewRentalsButton" : "viewRentals",
        "click #searchUserButton" : "searchUsers"
	},

    populate: function() {
        var fields = ["uid", "name", "email"];
        for (var value in fields) {
            $($("#modify-" + fields[value])[0]).val(this.model.get(fields[value]));
        }
    },

    hideAll: function() {
        $("#createUserGroup").hide();
        $("#modifyUserGroup").hide();
        $("#searchUserGroup").hide();
    },

    createRental: function() {
        location.hash = "rentals/create/" + this.model.get('uid');
    },

    viewRentals: function() {
        location.hash = "rentals/search/" + this.model.get('uid');
    },

    displayCreateForm: function() {
        $("#createUserGroup").show();
        $("#modifyUserGroup").hide();
        $("#searchUserGroup").hide();
    },

    displayModifyForm: function() {
        $("#createUserGroup").hide();
        $("#modifyUserGroup").show();
        $("#searchUserGroup").hide();
    },

    displaySearchForm: function() {
        $("#createUserGroup").hide();
        $("#modifyUserGroup").hide();
        $("#searchUserGroup").show();
    },

	attributeChange: function(event) {
		var field = {};
        var f = event.target.id;
        f = f.substring(f.indexOf("-") + 1);
        field[f] = event.target.value;
        this.model.set(field);
	},

    searchUsers: function(event) {
        var fields = ["uid", "name", "email", "rid", "job"];
        var search = {};
        for (var value in fields) {
            var f = $("#search-" + fields[value])[0].value;
            if (f){
                search[fields[value]] = f;
            }
        }
        Backbone.trigger('userSearchEvent', search); 
    },

    createUser: function(event) {
        var self = this;
        this.model.collection.create(this.model, {
            success: function(model, response) {
                location.hash = "users/" + response.insertId;
            },
            error: function(model, response) {
                alert("Error creating user.");
            }
        });
    },

	saveUser: function(event) {
    	var self = this;
    	this.model.collection.create(this.model, {
    		success: function(model, response) {
    			window.location.reload();
    		},
    		error: function(model, response) {
    			alert("Error saving user.");
    		}
    	});
    },

    deleteUser: function(event) {
        var self = this;
        this.model.destroy({
            success: function(model, response) {
                location.hash = "users";
            },
            error: function(model, response) {
                alert("Error deleting user.");
            }
        });
    },

    render: function () {
        this.$el.html(this.template());

		this.userInfoView = new hivemind.UserInfo({collection: this.collection});
		this.$('#userList').append(this.userInfoView.render().el);

        return this;
    }

});
