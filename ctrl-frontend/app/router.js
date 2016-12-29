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
        authOnly: false,
        pageTitle: "Home"
    }
},
{
    path: "/login",
    component: Login,
    meta: {
        authOnly: false,
        pageTitle: "Login"
    }
},
{
    path: "/register",
    component: Register,
    meta: {
        authOnly: false,
        pageTitle: "Register"
    }
},
{
    path: "/dash",
    component: Dashboard,
    meta: {
        authOnly: true,
        pageTitle: "Dashboard"
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
    if (to.meta.pageTitle) {
        window.document.title = "VMC - " + to.meta.pageTitle;
    }
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
