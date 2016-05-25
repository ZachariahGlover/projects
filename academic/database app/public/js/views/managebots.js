"use strict";
var hivemind = hivemind || {};

hivemind.ManageBots = Backbone.View.extend({

	events: {
		"change .input-group-item" : "attributeChange",
		"click #createBotButton" : "createBot",
        "click #saveBotButton" : "saveBot",
        "click #deleteBotButton" : "deleteBot",
        "click #searchBotButton" : "searchBots"
	},

    populate: function() {
        var fields = ["bid", "address", "rental"];
        for (var value in fields) {
            $($("#modify-" + fields[value])[0]).val(this.model.get(fields[value]));
        }
    },

    hideAll: function() {
        $("#createBotGroup").hide();
        $("#modifyBotGroup").hide();
        $("#searchBotGroup").hide();
    },

    displayCreateForm: function() {
        $("#createBotGroup").show();
        $("#modifyBotGroup").hide();
        $("#searchBotGroup").hide();
    },

    displayModifyForm: function() {
        $("#createBotGroup").hide();
        $("#modifyBotGroup").show();
        $("#searchBotGroup").hide();
    },

    displaySearchForm: function() {
        $("#createBotGroup").hide();
        $("#modifyBotGroup").hide();
        $("#searchBotGroup").show();
    },

	attributeChange: function(event) {
		var field = {};
        var f = event.target.id;
        f = f.substring(f.indexOf("-") + 1);
        field[f] = event.target.value;
        this.model.set(field);
	},

    searchBots: function(event) {
        var fields = ["bid", "address", "rid", "uid", "job"];
        var search = {};
        for (var value in fields) {
            var f = $("#search-" + fields[value])[0].value;
            if (f){
                search[fields[value]] = f;
            }
        }
        Backbone.trigger('botSearchEvent', search); 
    },

    createBot: function(event) {
        var self = this;
        this.model.collection.create(this.model, {
            success: function(model, response) {
                location.hash = "bots/" + response.insertId;
            },
            error: function(model, response) {
                alert("Error creating bot.");
            }
        });
    },

	saveBot: function(event) {
    	var self = this;
    	this.model.collection.create(this.model, {
    		success: function(model, response) {
    			window.location.reload();
    		},
    		error: function(model, response) {
    			alert("Error saving bot.");
    		}
    	});
    },

    deleteBot: function(event) {
        var self = this;
        this.model.destroy({
            success: function(model, response) {
                location.hash = "bots";
            },
            error: function(model, response) {
                alert("Error deleting bot.");
            }
        });
    },

    render: function () {
        this.$el.html(this.template());

		this.botInfoView = new hivemind.BotInfo({collection: this.collection});
		this.$('#botList').append(this.botInfoView.render().el);

        return this;
    }

});
