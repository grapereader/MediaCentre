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
