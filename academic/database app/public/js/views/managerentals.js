"use strict";
var hivemind = hivemind || {};

hivemind.ManageRentals = Backbone.View.extend({

	events: {
		"change .input-group-item" : "attributeChange",
		"click #createRentalButton" : "createRental",
        "click #saveRentalButton" : "saveRental",
        "click #deleteRentalButton" : "deleteRental",
        "click #viewUserButton" : "viewUser",
        "click #searchRentalButton" : "searchRentals"
	},

    populate: function() {
        var fields = ["rid", "owner", "nodes", "job", "expiration"];
        for (var value in fields) {
            $($("#modify-" + fields[value])[0]).val(this.model.get(fields[value]));
        }
    },

    hideAll: function() {
        $("#createRentalGroup").hide();
        $("#modifyRentalGroup").hide();
        $("#searchRentalGroup").hide();
    },

    displayCreateForm: function(uid) {
        $("#createRentalGroup").show();
        $("#modifyRentalGroup").hide();
        $("#searchRentalGroup").hide();
        if (uid) {
            this.model.set({owner: uid});
            $("#create-owner").val(uid);
        }
    },

    displayModifyForm: function() {
        $("#createRentalGroup").hide();
        $("#modifyRentalGroup").show();
        $("#searchRentalGroup").hide();
    },

    displaySearchForm: function() {
        $("#createRentalGroup").hide();
        $("#modifyRentalGroup").hide();
        $("#searchRentalGroup").show();
    },

	attributeChange: function(event) {
		var field = {};
        var f = event.target.id;
        f = f.substring(f.indexOf("-") + 1);
        field[f] = event.target.value;
        this.model.set(field);
	},

    searchRentals: function(event) {
        var fields = ["uid", "rid", "nodes", "job", "expiration"];
        var search = {};
        for (var value in fields) {
            var f = $("#search-" + fields[value])[0].value;
            if (f){
                search[fields[value]] = f;
            }
        }
        Backbone.trigger('rentalSearchEvent', search); 
    },

    viewUser: function(event) {
        location.hash = "users/" + this.model.attributes.owner;
    },

    createRental: function(event) {
        var self = this;
        this.model.collection.create(this.model, {
            success: function(model, response) {
                location.hash = "rentals/" + response.insertId;
            },
            error: function(model, response) {
                alert("Error creating rental.");
            }
        });
    },

	saveRental: function(event) {
    	var self = this;
    	this.model.collection.create(this.model, {
    		success: function(model, response) {
    			window.location.reload();
    		},
    		error: function(model, response) {
    			alert("Error saving rental.");
    		}
    	});
    },

    deleteRental: function(event) {
        var self = this;
        this.model.destroy({
            success: function(model, response) {
                location.hash = "rentals";
            },
            error: function(model, response) {
                alert("Error deleting rental.");
            }
        });
    },

    render: function () {
        this.$el.html(this.template());
		this.rentalInfoView = new hivemind.RentalInfo({collection: this.collection});
		this.$('#rentalList').append(this.rentalInfoView.render().el);
        return this;
    }

});
