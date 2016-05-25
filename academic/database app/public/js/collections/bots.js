'use strict';
var hivemind =  hivemind || {};
hivemind.Bots = Backbone.Collection.extend({
    model: hivemind.Bot,
    url:'/bots'
});
