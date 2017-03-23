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
var Vue = require("vue");
var VueRouter = require("vue-router");
var Vuex = require("vuex")

Vue.use(VueRouter);
Vue.use(Vuex);

var store = require("./store.js").store;

var router = require("./router.js").router;

var app = new Vue({
    store: store,
    router: router,
    methods: {
        logout: function() {
            var router = this.$router;
            this.$store.dispatch("authLogout").then(function() {
                router.push("/");
            });
        }
    },
    computed: {
        isLoggedIn: function() {
            return this.$store.state.auth.loggedIn;
        },
        userData: function() {
            return {
                username: this.$store.state.auth.username,
                email: this.$store.state.auth.email,
                privilege: this.$store.state.auth.privilege
            }
        }
    }
}).$mount("#app");

