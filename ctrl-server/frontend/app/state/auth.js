var axios = require("axios");

var authState = {
    state: {
        loggedIn: false,
        username: undefined,
        email: undefined,
        privilege: 0,
        message: false
    },
    mutations: {
        authLogin: function(state, details) {
            state.loggedIn = true;
            state.username = details.username;
            state.email = details.email;
            state.privilege = details.privilege;
        },
        authLogout: function(state) {
            state.loggedIn = false;
            state.username = state.email = undefined;
            state.privilege = 0;
        },
        authSetMessage: function(state, msg) {
            state.message = msg;
        },
        authClearMessage: function(state) {
            state.message = false;
        }
    },
    actions: {
        authLogin: function(context, details) {
            return axios.post("/login", {
                username: details.username,
                password: details.password,
                displayName: details.displayName
            }).then(function(response) {
                if (response.data.okay) {
                    var userData = response.data.user;
                    context.commit("authLogin", userData);
                    context.commit("authSetMessage", {
                        text: "Login successful",
                        success: true
                    });

                }
            }).catch(function(error) {
                if (error.response) {
                    context.commit("authSetMessage", {
                        text: error.response.data.error,
                        success: false
                    });
                }
            });
        },
        authLogout: function(context) {
            return axios.post("/logout", {}).then(function(response) {
                if (response.data.okay) {
                    context.commit("authLogout");
                    context.commit("authSetMessage", {
                        text: "Logged out successfully",
                        success: true
                    });
                } else {
                    context.commit("authSetMessage", {
                        text: "Logout failure",
                        success: false
                    });
                }
            }).catch(function(error) {
                context.commit("authSetMessage", {
                    text: "Error occurred sending logout request",
                    success: false
                });
            });
        },
        authRegister: function(context, details) {
            return axios.post("/register", details).then(function(response) {
                if (response.data.okay) {
                    context.commit("authSetMessage", {
                        text: response.data.msg,
                        success: true
                    });
                }
            }).catch(function(error) {
                if (error.response) {
                    context.commit("authSetMessage", {
                        text: error.response.data.msg,
                        success: false
                    });
                }
            });
        },
        authRefresh: function(context) {
            return axios.get("/loginStatus", {}).then(function(response) {
                if (response.data.loggedIn) {
                    var details = {
                        username: response.data.username,
                        email: response.data.email,
                        privilege: response.data.privilege
                    };
                    context.commit("authLogin", details);
                } else {
                    context.commit("authLogout");
                }
            });
        }
    }
};

exports.authState = authState;
