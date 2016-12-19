var axios = require("axios");

var configState = {
    state: {
        registration: false
    },
    mutations: {
        configSet: function(state, config) {
            state.registration = config.registration;
        }
    },
    actions: {
        configRefresh: function(context, details) {
            return axios.get("/config").then(function(response) {
                context.commit("configSet", response.data);
            });
        }
    }
}

exports.configState = configState;
