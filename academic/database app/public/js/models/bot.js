"use strict";
var hivemind = hivemind || {};
hivemind.Bot = Backbone.Model.extend({
    idAttribute : "bid",
    defaults : {
        address: "0.0.0.0",
        rental: null
    }
});
