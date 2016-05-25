'use strict';
var hivemind =  hivemind || {};
hivemind.Rentals = Backbone.Collection.extend({
    model: hivemind.Rental,
    url:'/rentals'
});
