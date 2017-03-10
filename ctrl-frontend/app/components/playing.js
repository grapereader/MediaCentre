var axios = require("axios");

var PlayQueue = {
    template: require("../templates/playing.html"),
    data: function() {
        return {
            url: ""
        };
    },
    methods: {
        addUrl: function(event) {
            var self = this;
            this.$store.dispatch("playerAddUrl", this.url).then(function() {
                self.url = "";
            });
        },
        clearPlaylist: function(event) {
            this.$store.dispatch("playerClearAll");
        },
        nextTrack: function(event) {
            this.$store.dispatch("playerNext");
        },
        prevTrack: function(event) {
            this.$store.dispatch("playerBack");
        },
        pause: function(event) {
            this.$store.dispatch("playerPause");
        },
        play: function(event) {
            this.$store.dispatch("playerPlay");
        }
    },
    computed: {
    }
}

exports.PlayQueue = PlayQueue;
