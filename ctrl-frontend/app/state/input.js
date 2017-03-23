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
var axios = require("axios");

var inputState = {
    state: {
        currentInput: false,
        available: []
    },
    mutations: {
        inputSetAvailable: function(state, available) {
            state.available = available;
        },
        inputSetCurrent: function(state, current) {
            for (var i = 0; i < state.available.length; i++) {
                var input = state.available[i];
                if (input.id === current) {
                    state.currentInput = input;
                    break;
                }
            }
        }
    },
    actions: {
        inputRefresh: function(context) {
            return axios.get("/getInputs").then(function(response) {
                if (response.data.okay) {
                    var inputs = response.data.inputs;
                    context.commit("inputSetAvailable", inputs);
                    var currentInput = response.data.currentInput;
                    context.commit("inputSetCurrent", currentInput);
                }
            });
        },
        inputSet: function(context, id) {
            var exists = false;
            for (var i = 0; i < context.state.available.length; i++) {
                var input = context.state.available[i];
                if (input.id === id) {
                    exists = true;
                    break;
                }
            }

            if (!exists) return;

            return axios.post("/setInput", {
                id: id
            }).then(function(response) {
                if (response.data.okay) {
                    var current = response.data.currentInput;
                    context.commit("inputSetCurrent", current);
                }
            });
        }
    }
};

exports.inputState = inputState;
