var VueRouter = require("vue-router");

var Home = require("./components/home.js").Home;
var Login = require("./components/login.js").Login;
var Dashboard = require("./components/dash.js").Dashboard;
var Register = require("./components/register.js").Register;

var store = require("./store.js").store;

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
    path: "/register",
    component: Register,
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
    linkActiveClass: "active",
    routes: routes
});

router.beforeEach(function(to, from, next) {
    store.commit("authClearMessage");
    store.dispatch("configRefresh");
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

exports.router = router;
