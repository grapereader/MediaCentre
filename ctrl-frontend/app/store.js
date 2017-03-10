var Vuex = require("vuex")

var authState = require("./state/auth.js").authState;
var configState = require("./state/config.js").configState;
var inputState = require("./state/input.js").inputState;
var playerState = require("./state/player.js").playerState;

var store = new Vuex.Store({
    modules: {
        auth: authState,
        config: configState,
        input: inputState,
        player: playerState
    }
});

exports.store = store;
