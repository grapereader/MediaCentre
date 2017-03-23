/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
var VueRouter = require("vue-router");

var Home = require("./components/home.js").Home;
var Login = require("./components/login.js").Login;
var Dashboard = require("./components/dash.js").Dashboard;
var Register = require("./components/register.js").Register;
var PlayQueue = require("./components/playing.js").PlayQueue;

var store = require("./store.js").store;

var routes = [
{
    path: "/",
    component: Home,
    meta: {
        authOnly: false,
        pageTitle: "Home"
    }
},
{
    path: "/login",
    component: Login,
    meta: {
        authOnly: false,
        pageTitle: "Login"
    }
},
{
    path: "/register",
    component: Register,
    meta: {
        authOnly: false,
        pageTitle: "Register"
    }
},
{
    path: "/dash",
    component: Dashboard,
    meta: {
        authOnly: true,
        pageTitle: "Dashboard"
    },
    beforeEnter: function(to, from, next) {
        if (store.state.auth.loggedIn) {
            store.dispatch("inputRefresh");
        }
        next();
    }
},
{
    path: "/playing",
    component: PlayQueue,
    meta: {
        authOnly: true,
        pageTitle: "Play Queue"
    },
    beforeEnter: function(to, from, next) {
        store.dispatch("playerRefresh");
        store.dispatch("playerRefreshPlaylist");
        next();
    }
}
];

var router = new VueRouter({
    linkActiveClass: "active",
    routes: routes
});

router.beforeEach(function(to, from, next) {
    store.commit("authClearMessage");
    store.dispatch("configRefresh");
    if (to.meta.pageTitle) {
        window.document.title = "VMC - " + to.meta.pageTitle;
    }
    store.dispatch("authRefresh").then(function() {
        if (to.meta.authOnly && !store.state.auth.loggedIn) {
            store.commit("authSetMessage", {
                success: false,
                text: "You must be logged in to access this page"
            });
            next("/login");
        } else {
            next();
        }
    });
});

exports.router = router;
