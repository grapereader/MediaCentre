var Vue = require("vue");
var VueRouter = require("vue-router");
var Vuex = require("vuex")

Vue.use(VueRouter);
Vue.use(Vuex);

var store = require("./store.js").store;

var router = require("./router.js").router;

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

