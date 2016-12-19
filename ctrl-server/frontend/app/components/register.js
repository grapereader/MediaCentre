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
            alert("Register placeholder (" + this.username + "," + this.email + ")");
        }
    },
    computed: {
        passwordsMatch: function() {
            return this.password == this.confirmPassword;
        },
        validated: function() {
            return this.passwordsMatch && this.username.length > 4 && this.password.length > 4 && this.email.length > 4;
        }
    }
}

exports.Register = Register;
