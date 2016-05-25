"use strict";
var hivemind = hivemind || {};

hivemind.UserInfo = Backbone.View.extend({

	userListTemplate: _.template([
	    "<% users.each(function(user) { %>",
	        "<%= userTemplate(user.toJSON()) %>",
	    "<% }); %>",
	].join('')),

	render: function () {
		var usersMarkup = this.userListTemplate({
			users: this.collection,
			userTemplate: this.template
		});
		this.$el.html(usersMarkup);
		return this;
    }
});