"use strict";
var hivemind = hivemind || {};
hivemind.Home = Backbone.View.extend({
    render: function () {
        this.$el.html(this.template());
        return this;
    }
});
