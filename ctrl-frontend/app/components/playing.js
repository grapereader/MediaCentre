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
