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
var Register = {
    template: require("../templates/register.html"),
    data: function() {
        return {
            username: "",
            password: "",
            confirmPassword: "",
            email: ""
        }
    },
    methods: {
        registerSubmit: function(event) {
            if (!this.validated) return;
            this.$store.dispatch("authRegister", {
                username: this.username,
                password: this.password,
                email: this.email
            });
        }
    },
    computed: {
        passwordsMatch: function() {
            return this.password == this.confirmPassword;
        },
        validated: function() {
            return this.passwordsMatch && this.username.length >= 4 && this.password.length >= 8 && this.email.length >= 6;
        },
        message: function() {
            return this.$store.state.auth.message;
        }
    }
}

exports.Register = Register;
