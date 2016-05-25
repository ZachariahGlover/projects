'use strict';
var hivemind =  hivemind || {};
hivemind.Users = Backbone.Collection.extend({
    model: hivemind.User,
    url:'/users'
});
