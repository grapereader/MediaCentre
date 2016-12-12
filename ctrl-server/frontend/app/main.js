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
        setMessage: function(msg) {
            this.$store.commit("authSetMessage", msg);
        },
        loginSubmit: function(event) {
            if (this.username.length <= 0 || this.password.length <= 0) {
                this.setMessage({
                    success: false,
                    text: "Missing login details"
                });
                return;
            }

            this.setMessage({
                success: true,
                text: "Logging in..."
            });

            this.$store.dispatch("authLogin", {
                username: this.username,
                password: this.password
            });
        },
        guestSubmit: function(event) {
            if (this.displayName.length <= 0) {
                this.setMessage({
                    success: false,
                    text: "Please enter a display name for guest access"
                });
                return;
            }

            this.setMessage({
                success: true,
                text: "Logging in..."
            });

            this.$store.dispatch("authLogin", {
                username: "guest",
                displayName: this.displayName
            });
        }
    },
    data: function() {
        return {
            username: "",
            password: "",
            displayName: ""
        }
    },
    computed: {
        message: function() {
            return this.$store.state.auth.message;
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

