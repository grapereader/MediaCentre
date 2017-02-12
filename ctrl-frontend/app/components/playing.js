var axios = require("axios");

var PlayQueue = {
    template: require("../templates/playing.html"),
    data: function() {
        return {
            url: ""
        };
    },
    methods: {
        test1: function() {
            axios.post("/test1");
        },
        test2: function() {
            axios.post("/test2");
        }
    },
    computed: {
    }
}

exports.PlayQueue = PlayQueue;
