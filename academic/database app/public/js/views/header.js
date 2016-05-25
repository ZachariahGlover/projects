"use strict";
var hivemind = hivemind || {};

hivemind.Header = Backbone.View.extend({

    render: function () {
        this.$el.html(this.template());
        return this;
    },

    removeActive: function () {
        $('.nav li').removeClass('active');
    },
    selectMenuItem: function (button) {
        this.removeActive();
        $(button).addClass('active');
    }
});
