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

            var router = this.$router;

            this.$store.dispatch("authLogin", {
                username: this.username,
                password: this.password
            }).then(function() {
                router.push("/dash");
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

            var router = this.$router;

            this.$store.dispatch("authLogin", {
                username: "guest",
                displayName: this.displayName
            }).then(function() {
                router.push("/dash");
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

exports.Login = Login;
