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
var Login = {
    template: require("../templates/login.html"),
    methods: {
        setMessage: function(msg) {
            this.$store.commit("authSetMessage", msg);
        },
        loginSubmit: function(event) {
            if (this.username.length <= 0 || this.password.length <= 0) {
                this.setMessage({
                    success: false,
                    text: "Missing login details"
                });
                return;
            }

            this.setMessage({
                success: true,
                text: "Logging in..."
            });

            var router = this.$router;

            this.$store.dispatch("authLogin", {
                username: this.username,
                password: this.password
            }).then(function() {
                router.push("/dash");
            });
        },
        guestSubmit: function(event) {
            if (this.displayName.length <= 0) {
                this.setMessage({
                    success: false,
                    text: "Please enter a display name for guest access"
                });
                return;
            }

            this.setMessage({
                success: true,
                text: "Logging in..."
            });

            var router = this.$router;

            this.$store.dispatch("authLogin", {
                username: "guest",
                displayName: this.displayName
            }).then(function() {
                router.push("/dash");
            });
        }
    },
    data: function() {
        return {
            username: "",
            password: "",
            displayName: ""
        }
    },
    computed: {
        message: function() {
            return this.$store.state.auth.message;
        },
        registrationEnabled: function() {
            return this.$store.state.config.registration;
        },
        guestEnabled: function() {
            return this.$store.state.config.guest;
        }
    }
};

exports.Login = Login;
