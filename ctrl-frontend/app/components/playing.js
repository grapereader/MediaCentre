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
        setTrack: function(id) {
        },
        pause: function(event) {
            this.$store.dispatch("playerSetState", "paused");
        },
        play: function(event) {
            this.$store.dispatch("playerSetState", "playing");
        }
    },
    computed: {
        currentId: function() {
            if (this.$store.state.player.currentTrack == undefined) return 0;
            return this.$store.state.player.currentTrack.id;
        },
        playlist: function() {
            return this.$store.state.player.playlist;
        }
    }
}

exports.PlayQueue = PlayQueue;
