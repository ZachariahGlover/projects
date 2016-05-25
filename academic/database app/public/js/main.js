"use strict";
var hivemind = hivemind || {};

hivemind.AppRouter = Backbone.Router.extend({

    routes: {
        "": "home",
        "bots": "showBots",
        "bots/:bid": "showBots",
        "bots/create": "showBots",
        "bots/search": "showBots",
        "users": "showUsers",
        "users/:uid": "showUsers",
        "users/create": "showUsers",
        "users/search": "showUsers",
        "rentals": "showRentals",
        "rentals/create/:uid": "createUserRental",
        "rentals/search/:uid": "searchUserRentals",
        "rentals/:rid": "showRentals",
        "rentals/create": "showRentals",
        "rentals/search": "showRentals",
        "advanced": "showAdvanced",
        "*default": "home"
    },

    initialize: function() {
        this.users = new hivemind.Users();
        this.bots = new hivemind.Bots();
        this.rentals = new hivemind.Rentals();

        this.listenTo(Backbone, 'botSearchEvent', this.searchBots);
        this.listenTo(Backbone, 'userSearchEvent', this.searchUsers);
        this.listenTo(Backbone, 'rentalSearchEvent', this.searchRentals);

        this.listenTo(Backbone, 'submitQueryEvent', this.submitQuery);

        this.headerView = new hivemind.Header();
        $('.header').html(this.headerView.render().el);
    },

    home: function() {
        location.hash = "home";
        this.homeView = new hivemind.Home();
        hivemind.app.showView('#content', this.homeView);
        this.headerView.removeActive();
    },

    showBots: function(event) {
        var self = this;
        this.bots.fetch({
            success: function(coll, resp) {
                var botModel;
                if (event == null) {
                    botModel = new hivemind.Bot();
                    botModel.collection = self.bots;
                    self.botsView = new hivemind.ManageBots({model: botModel, collection: self.bots});
                    hivemind.app.showView('#content', self.botsView);
                    self.botsView.hideAll();
                }
                else if (event == 'create') {
                    botModel = new hivemind.Bot();
                    botModel.collection = self.bots;
                    self.botsView = new hivemind.ManageBots({model: botModel, collection: self.bots});
                    hivemind.app.showView('#content', self.botsView);
                    self.botsView.displayCreateForm();
                }
                else if (event == 'search') {
                    botModel = new hivemind.Bot();
                    botModel.collection = self.bots;
                    self.botsView = new hivemind.ManageBots({model: botModel, collection: self.bots});
                    hivemind.app.showView('#content', self.botsView);
                    self.botsView.displaySearchForm();
                }
                else {
                    botModel = self.bots.get(event);
                    if (botModel == undefined) {
                        location.hash = "bots";
                    }
                    else {
                        botModel.collection = self.bots;
                        self.botsView = new hivemind.ManageBots({model: botModel, collection: self.bots});
                        hivemind.app.showView('#content', self.botsView);
                        self.botsView.populate();
                        self.botsView.displayModifyForm();
                    }
                }
                self.headerView.selectMenuItem($("#headerBots"));
            },
            error: function(coll, resp) {
                alert("Error retrieving bots.");
            }
        }); 
    },

    showUsers: function(event) {
        var self = this;
        this.users.fetch({
            success: function(coll, resp) {
                var userModel;
                if (event == null) {
                    userModel = new hivemind.User();
                    userModel.collection = self.users;
                    self.usersView = new hivemind.ManageUsers({model: userModel, collection: self.users});
                    hivemind.app.showView('#content', self.usersView);
                    self.usersView.hideAll();
                }
                else if (event == 'create') {
                    userModel = new hivemind.User();
                    userModel.collection = self.users;
                    self.usersView = new hivemind.ManageUsers({model: userModel, collection: self.users});
                    hivemind.app.showView('#content', self.usersView);
                    self.usersView.displayCreateForm();
                }
                else if (event == 'search') {
                    userModel = new hivemind.User();
                    userModel.collection = self.users;
                    self.usersView = new hivemind.ManageUsers({model: userModel, collection: self.users});
                    hivemind.app.showView('#content', self.usersView);
                    self.usersView.displaySearchForm();
                }
                else {
                    userModel = self.users.get(event);
                    if (userModel == undefined) {
                        location.hash = "users";
                    }
                    else {
                        userModel.collection = self.users;
                        self.usersView = new hivemind.ManageUsers({model: userModel, collection: self.users});
                        hivemind.app.showView('#content', self.usersView);
                        self.usersView.populate();
                        self.usersView.displayModifyForm();
                    }
                }
                self.headerView.selectMenuItem($("#headerUsers"));
            },
            error: function(coll, resp) {
                alert("Error retrieving users.");
            }
        });  
    },

    showRentals: function(event) {
        var self = this;
        this.rentals.fetch({
            success: function(coll, resp) {
                var rentalModel;
                if (event == null) {
                    rentalModel = new hivemind.Rental();
                    rentalModel.collection = self.rentals;
                    self.rentalsView = new hivemind.ManageRentals({model: rentalModel, collection: self.rentals});
                    hivemind.app.showView('#content', self.rentalsView);
                    self.rentalsView.hideAll();
                }
                else if (event == 'create') {
                    rentalModel = new hivemind.Rental();
                    rentalModel.collection = self.rentals;
                    self.rentalsView = new hivemind.ManageRentals({model: rentalModel, collection: self.rentals});
                    hivemind.app.showView('#content', self.rentalsView);
                    self.rentalsView.displayCreateForm();
                }
                else if (event == 'search') {
                    rentalModel = new hivemind.Rental();
                    rentalModel.collection = self.rentals;
                    self.rentalsView = new hivemind.ManageRentals({model: rentalModel, collection: self.rentals});
                    hivemind.app.showView('#content', self.rentalsView);
                    self.rentalsView.displaySearchForm();
                }
                else {
                    rentalModel = self.rentals.get(event);
                    if (rentalModel == undefined) {
                        location.hash = "rentals";
                    }
                    else {
                        rentalModel.collection = self.rentals;
                        self.rentalsView = new hivemind.ManageRentals({model: rentalModel, collection: self.rentals});
                        hivemind.app.showView('#content', self.rentalsView);
                        self.rentalsView.populate();
                        self.rentalsView.displayModifyForm();
                    }
                }
                self.headerView.selectMenuItem($("#headerRentals"));
            },
            error: function(coll, resp) {
                alert("Error retrieving rentals.");
            }
        });  
    },

    showAdvanced: function(event) {
        this.advancedView = new hivemind.Advanced();
        hivemind.app.showView('#content', this.advancedView);
        this.headerView.selectMenuItem($("#headerAdvanced"));
    },

    searchBots: function(event) {
        var self = this;
        this.bots.fetch({
            data: event,
            success: function(coll, resp) {
                var filteredBots = self.bots.clone();
                if (event.bid) {
                    filteredBots = new hivemind.Bots(filteredBots.filter(function(item) {
                        return item.get('bid').indexOf(event.bid) != -1;
                    }));
                }
                if (event.address) {
                    filteredBots = new hivemind.Bots(filteredBots.filter(function(item) {
                        return item.get('address').indexOf(event.address) != -1;
                    }));
                }
                if (event.rid) {
                    filteredBots = new hivemind.Bots(filteredBots.filter(function(item) {
                        return item.get('rental').indexOf(event.rid) != -1;
                    }));
                }
                var botModel;
                botModel = new hivemind.Bot();
                botModel.collection = self.bots;
                self.botsView = new hivemind.ManageBots({model: botModel, collection: filteredBots});
                hivemind.app.showView('#content', self.botsView);
                self.botsView.displaySearchForm();
                self.headerView.selectMenuItem($("#headerBots"));
            },
            error: function(coll, resp) {
                alert("Error retrieving bots.");
            }
        }); 
    },

    searchUsers: function(event) {
        var self = this;
        this.users.fetch({
            data: event,
            success: function(coll, resp) {
                var filteredUsers = self.users.clone();
                if (event.uid) {
                    filteredUsers = new hivemind.Users(filteredUsers.filter(function(item) {
                        return item.get('uid').indexOf(event.uid) != -1;
                    }));
                }
                if (event.name) {
                    filteredUsers = new hivemind.Users(filteredUsers.filter(function(item) {
                        return item.get('name').indexOf(event.name) != -1;
                    }));
                }
                if (event.email) {
                    filteredUsers = new hivemind.Users(filteredUsers.filter(function(item) {
                        return item.get('email').indexOf(event.email) != -1;
                    }));
                }
                var userModel;
                userModel = new hivemind.User();
                userModel.collection = self.users;

                self.usersView = new hivemind.ManageUsers({model: userModel, collection: filteredUsers});
                hivemind.app.showView('#content', self.usersView);
                self.usersView.displaySearchForm();
                self.headerView.selectMenuItem($("#headerUsers"));
            },
            error: function(coll, resp) {
                alert("Error retrieving users.");
            }
        }); 
    },

    searchRentals: function(event) {
        var self = this;
        this.rentals.fetch({
            data: event,
            success: function(coll, resp) {
                var filteredRentals = self.rentals.clone();
                if (event.uid) {
                    filteredRentals = new hivemind.Rentals(filteredRentals.filter(function(item) {
                        return item.get('owner').indexOf(event.uid) != -1;
                    }));
                }
                if (event.rid) {
                    filteredRentals = new hivemind.Rentals(filteredRentals.filter(function(item) {
                        return item.get('rid').indexOf(event.rid) != -1;
                    }));
                }
                if (event.nodes) {
                    filteredRentals = new hivemind.Rentals(filteredRentals.filter(function(item) {
                        return item.get('nodes') == event.nodes;
                    }));
                }
                if (event.job) {
                    filteredRentals = new hivemind.Rentals(filteredRentals.filter(function(item) {
                        return item.get('job').indexOf(event.job) != -1;
                    }));
                }
                if (event.expiration) {
                    filteredRentals = new hivemind.Rentals(filteredRentals.filter(function(item) {
                        return item.get('expiration').indexOf(event.expiration) != -1;
                    }));
                }

                var rentalModel;
                rentalModel = new hivemind.Rental();
                rentalModel.collection = self.rentals;

                self.rentalsView = new hivemind.ManageRentals({model: rentalModel, collection: filteredRentals});
                hivemind.app.showView('#content', self.rentalsView);
                self.rentalsView.displaySearchForm();
                self.headerView.selectMenuItem($("#headerRentals"));
            },
            error: function(coll, resp) {
                alert("Error retrieving rentals.");
            }
        }); 
    },

    createUserRental: function(event) {
        this.navigate('rentals/create', {trigger: false});
        var self = this;
        this.rentals.fetch({
            success: function(coll, resp) {
                var rentalModel;
                rentalModel = new hivemind.Rental();
                rentalModel.collection = self.rentals;
                self.rentalsView = new hivemind.ManageRentals({model: rentalModel, collection: self.rentals});
                hivemind.app.showView('#content', self.rentalsView);
                self.rentalsView.displayCreateForm(event);
                self.headerView.selectMenuItem($("#headerRentals"));
            },
            error: function(coll, resp) {
                alert("Error retrieving rentals.");
            }
        });  
    },

    searchUserRentals: function(event) {
        this.navigate('rentals/search', {trigger: false});
        this.searchRentals({uid: event});
    },

    submitQuery: function(event) {
        $.get("/advanced", {string: event}, function(data) {
                var markup = "";
                if (data.length > 0) {
                    if (data[0].constructor === Array) {
                        markup += "<div style=\"overflow-x:auto;\"><table class=\"query-table\">\n";
                        for (var result in data) {
                            markup += "<td class=\"query-table-column\">";
                            markup += "<div style=\"overflow-x:auto;\"><table class=\"query-table\">\n";
                            var _data = data[result];
                            if (_data.length > 0) {
                                var columns = [];
                                markup += "<tr class=\"query-table-row\">\n"
                                for (var key in _data[0]) {
                                    markup += "<td class=\"query-table-column\">" + key + "</td>\n";
                                }
                                markup += "</tr>\n"
                                for (var i = 0; i < _data.length; i++) {
                                    markup += "<tr class=\"query-table-row\">\n"
                                    for (var key in _data[i]) {
                                        markup += "<td class=\"query-table-column\">" + (_data[i])[key] + "</td>\n";
                                    }
                                    markup += "</tr>\n"
                                }
                            }
                            markup += "</table></div>";
                            markup += "</td>\n";
                        }
                        markup += "</table></div>";
                    }
                    else {
                        markup += "<div style=\"overflow-x:auto;\"><table class=\"query-table\">\n";
                        var columns = [];
                        markup += "<tr class=\"query-table-row\">\n"
                        for (var key in data[0]) {
                            markup += "<td class=\"query-table-column\">" + key + "</td>\n";
                        }
                        markup += "</tr>\n"
                        for (var i = 0; i < data.length; i++) {
                            markup += "<tr class=\"query-table-row\">\n"
                            for (var key in data[i]) {
                                markup += "<td class=\"query-table-column\">" + (data[i])[key] + "</td>\n";
                            }
                            markup += "</tr>\n"
                        }
                        markup += "</table></div>";
                    }
                }
                else {
                    markup += "Query success. No results to display.";
                }
                $("#queryTableContent").html(markup);
            }).fail(function(err) {
                var markup = "Error processing query.";
                $("#queryTableContent").html(markup);
            });
    },
    showView: function(selector, view) {
        if (this.currentView) {
            this.currentView.close();
        }
        $(selector).html(view.render().el);
        this.currentView = view;
    }
});

Backbone.View.prototype.close = function () {
    if (this.onClose) {
        this.onClose();
    }
    this.remove();
    this.unbind();
};

var views = ['Home', 'Header', 'Advanced', 'ManageBots', 'ManageUsers', 'ManageRentals', 'UserInfo', 'BotInfo', 'RentalInfo'];
var deferreds = [];
$.each(views, function(index, view) {
    if (hivemind[view]) {
        deferreds.push($.get('tpl/' + view + '.html', function(data) {
            hivemind[view].prototype.template = _.template(data);
        }));
    }
});
$.when.apply(null, deferreds).done(function() {
    hivemind.app = new hivemind.AppRouter();
    Backbone.history.start();
});
