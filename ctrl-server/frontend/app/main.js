var Vue = require("vue");
var VueRouter = require("vue-router");
var Vuex = require("vuex")

Vue.use(VueRouter);
Vue.use(Vuex);

var authState = require("./authState.js").authState;

var store = new Vuex.Store({
    modules: {
        auth: authState
    }
});

store.dispatch("authRefresh");

var Home = {
    template: require("./templates/home.html")
};

var Login = {
    template: require("./templates/login.html"),
    methods: {
        loginSubmit: function(event) {
            if (this.username.length <= 0 || this.password.length <= 0) {
                this.message = {
                    success: false,
                    msg: "Missing login details"
                };
                return;
            }

            this.message = {
                success: true,
                msg: "Logging in..."
            };

            this.$store.dispatch("authLogin", {
                username: this.username,
                password: this.password
            });
        }
    },
    data: function() {
        return {
            username: "",
            password: "",
            message: false
        }
    }
};


var routes = [
{ path: "/", component: Home },
{ path: "/login", component: Login }
];

var router = new VueRouter({
    routes: routes
});

var app = new Vue({
    store: store,
    router: router
}).$mount("#app");

