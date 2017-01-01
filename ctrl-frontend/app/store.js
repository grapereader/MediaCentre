var Vuex = require("vuex")

var authState = require("./state/auth.js").authState;
var configState = require("./state/config.js").configState;
var inputState = require("./state/input.js").inputState;

var store = new Vuex.Store({
    modules: {
        auth: authState,
        config: configState,
        input: inputState
    }
});

exports.store = store;
