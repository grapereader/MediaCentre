/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
var axios = require("axios");

var playerState = {
    state: {
        position: 0,
        length: 0,
        currentTrack: undefined,
        playState: "stopped",
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
        playerSetPlaylist: function(state, playlist) {
            state.playlist = playlist;
            state.playlist.sort(function(a, b) {
                if (a.id < b.id) return -1;
                if (a.id > b.id) return 1;
                return 0;
            });
        },
        playerSetCurrentTrack: function(state, track) {
            state.currentTrack = track;
        },
        playerClearPlaylist: function(state) {
            state.playlist = [];
        },
        playerSetPlayState: function(state, playState) {
            state.playState = playState;
        }
    },
    actions: {
        playerRefresh: function(context) {
            return axios.get("/player/state").then(function(response) {
                context.commit("playerSetLength", response.data.length);
                context.commit("playerSetPosition", response.data.position);
                context.commit("playerSetPlayState", response.data.state);
            });
        },
        playerRefreshPlaylist: function(context) {
            return axios.get("/player/getPlaylist").then(function(response) {
                if (response.data.okay) {
                    context.commit("playerSetPlaylist", response.data.playlist);
                    context.commit("playerSetCurrentTrack", context.state.playlist[response.data.playing]);
                }
            });
        },
        playerAddUrl: function(context, url) {
            return axios.post("/player/addUrl", {
                insertType: "back",
                url: url
            }).then(function(response) {
                if (response.data.okay) {
                    context.commit("playerAddToPlaylist", url);
                    context.dispatch("playerRefreshPlaylist");
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
        playerSetState: function(context, state) {
            return axios.post("/player/setPlayState", {
                state: state
            }).then(function(response) {
                if (response.data.okay) {
                    context.commit("playerSetPlayState", response.data.state);
                }
            })
        }
    }
};

exports.playerState = playerState;
