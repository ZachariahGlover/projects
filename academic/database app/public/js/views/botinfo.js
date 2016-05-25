"use strict";
var hivemind = hivemind || {};

hivemind.BotInfo = Backbone.View.extend({

	botListTemplate: _.template([
	    "<% bots.each(function(bot) { %>",
	        "<%= botTemplate(bot.toJSON()) %>",
	    "<% }); %>",
	].join('')),

	render: function () {
		var botsMarkup = this.botListTemplate({
			bots: this.collection,
			botTemplate: this.template
		});
		this.$el.html(botsMarkup);
		return this;
    }
});