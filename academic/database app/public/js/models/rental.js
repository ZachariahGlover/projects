"use strict";
var hivemind = hivemind || {};
hivemind.Rental = Backbone.Model.extend({
    idAttribute : "rid",
    defaults : {
        owner: "None",
        nodes: 0,
        job: "idle",
        expiration: "0000-00-00"
    }
});
