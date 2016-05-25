"use strict";
var hivemind = hivemind || {};
hivemind.User = Backbone.Model.extend({
    idAttribute : "uid",
    defaults : {
        name: "Default",
        email: "None"
    }
});
