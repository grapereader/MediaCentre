var Dashboard = {
    template: require("../templates/dash.html"),
    methods: {
        setInput: function(id) {
            var self = this;
            this.$store.dispatch("inputSet", id);
        }
    },
    computed: {
        availableInputs: function() {
            return this.$store.state.input.available;
        },
        currentInput: function() {
            return this.$store.state.input.currentInput;
        }
    }
}

exports.Dashboard = Dashboard;
