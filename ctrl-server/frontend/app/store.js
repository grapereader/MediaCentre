var Vuex = require("vuex")

var authState = require("./authState.js").authState;

var store = new Vuex.Store({
    modules: {
        auth: authState
    }
});

exports.store = store;
