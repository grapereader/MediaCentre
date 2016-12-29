var Vuex = require("vuex")

var authState = require("./state/auth.js").authState;
var configState = require("./state/config.js").configState;

var store = new Vuex.Store({
    modules: {
        auth: authState,
        config: configState
    }
});

exports.store = store;
