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


var Home = {
    template: require("./templates/home.html")
};

var Login = require("./loginComponent.js").Login;

var Dashboard = {
    template: require("./templates/dash.html")
}

var routes = [
{
    path: "/",
    component: Home,
    meta: {
        authOnly: false
    }
},
{
    path: "/login",
    component: Login,
    meta: {
        authOnly: false
    }
},
{
    path: "/dash",
    component: Dashboard,
    meta: {
        authOnly: true
    }
}
];

var router = new VueRouter({
    routes: routes
});

router.beforeEach(function(to, from, next) {
    store.commit("authClearMessage");
    store.dispatch("authRefresh").then(function() {
        if (to.meta.authOnly && !store.state.auth.loggedIn) {
            store.commit("authSetMessage", {
                success: false,
                text: "You must be logged in to access this page"
            });
            next("/login");
        } else {
            next();
        }
    });
});

var app = new Vue({
    store: store,
    router: router,
    methods: {
        logout: function() {
            var router = this.$router;
            this.$store.dispatch("authLogout").then(function() {
                router.push("/");
            });
        }
    },
    computed: {
        isLoggedIn: function() {
            return this.$store.state.auth.loggedIn;
        },
        userData: function() {
            return {
                username: this.$store.state.auth.username,
                email: this.$store.state.auth.email,
                privilege: this.$store.state.auth.privilege
            }
        }
    }
}).$mount("#app");

