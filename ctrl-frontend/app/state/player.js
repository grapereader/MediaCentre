var axios = require("axios");

var playerState = {
    state: {
        position: 0,
        length: 0,
        currentTrack: "Nothing",
        playing: false,
        playlist: []
    },
    mutations: {
        playerSetPosition: function(state, position) {
            state.position = position;
        },
        playerSetLength: function(state, length) {
            state.length = length;
        },
        playerAddToPlaylist: function(state, item) {
            state.playlist.push(item);
        },
        playerClearPlaylist: function(state) {
            state.playlist = [];
        },
        playerSetPlaying: function(state, playing) {
            state.playing = playing;
        }
    },
    actions: {
        playerRefresh: function(context) {
            return axios.get("/player/state").then(function(response) {
                context.commit("playerSetLength", response.data.length);
            });
        },
        playerAddUrl: function(context, url) {
            return axios.post("/player/addUrl", {
                insertType: "back",
                url: url
            }).then(function(response) {
                if (response.data.okay) {
                    context.commit("playerAddToPlaylist", url);
                }
            });
        },
        playerClearAll: function(context) {
            return axios.post("/player/clear").then(function(response) {
                if (response.data.okay) {
                    context.commit("playerClearPlaylist");
                }
            });
        },
        playerNext: function(context) {
            return axios.post("/player/next").then(function(response) {
                if (response.data.okay) {
                    console.log("TODO: Frontend player next");
                }
            })
        },
        playerBack: function(context) {
            return axios.post("/player/back").then(function(response) {
                if (response.data.okay) {
                    console.log("TODO: Frontend player back");
                }
            })
        },
        playerPause: function(context) {
            return axios.post("/player/pause").then(function(response) {
                if (response.data.okay) {
                    context.commit("playerSetPlaying", false);
                }
            })
        },
        playerPlay: function(context) {
            return axios.post("/player/play").then(function(response) {
                if (response.data.okay) {
                    context.commit("playerSetPlaying", true);
                }
            })
        }
    }
};

exports.playerState = playerState;
