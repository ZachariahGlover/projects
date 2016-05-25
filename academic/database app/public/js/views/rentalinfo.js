"use strict";
var hivemind = hivemind || {};

hivemind.RentalInfo = Backbone.View.extend({

	rentalListTemplate: _.template([
	    "<% rentals.each(function(rental) { %>",
	        "<%= rentalTemplate(rental.toJSON()) %>",
	    "<% }); %>",
	].join('')),

	render: function () {
		var rentalsMarkup = this.rentalListTemplate({
			rentals: this.collection,
			rentalTemplate: this.template
		});
		this.$el.html(rentalsMarkup);
		return this;
    }
});