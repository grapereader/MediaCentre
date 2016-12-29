var Register = {
    template: require("../templates/register.html"),
    data: function() {
        return {
            username: "",
            password: "",
            confirmPassword: "",
            email: ""
        }
    },
    methods: {
        registerSubmit: function(event) {
            if (!this.validated) return;
            this.$store.dispatch("authRegister", {
                username: this.username,
                password: this.password,
                email: this.email
            });
        }
    },
    computed: {
        passwordsMatch: function() {
            return this.password == this.confirmPassword;
        },
        validated: function() {
            return this.passwordsMatch && this.username.length >= 4 && this.password.length >= 8 && this.email.length >= 6;
        },
        message: function() {
            return this.$store.state.auth.message;
        }
    }
}

exports.Register = Register;
