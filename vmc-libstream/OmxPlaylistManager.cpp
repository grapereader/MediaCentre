#include "OmxPlaylistManager.h"

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>

#include <vmc-libhttp/String.h>
#include <vmc-libutils/Utils.h>

namespace vmc
{
    namespace stream
    {
        long getTime()
        {
            auto secs = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
            return secs.count();
        }

        void OmxPlaylistManager::addEntry(PlaylistEntry const &entry)
        {
            if (entry.getUrl().length() <= 1) return;
            std::system(std::string("omxd A '").append(entry.getUrl()).append("'").c_str());

            this->entries.push_back({ entry, getTime() });
        }

        void OmxPlaylistManager::addEntryUpNext(PlaylistEntry const &entry)
        {
            if (entry.getUrl().length() <= 1) return;
            std::system(std::string("omxd a '").append(entry.getUrl()).append("'").c_str());

            this->entries.push_back({ entry, getTime() });
        }

        void OmxPlaylistManager::removeEntry(int index)
        {
            std::system(std::string("omxd x ").append(std::to_string(index)).c_str());
        }

        void OmxPlaylistManager::clearAll()
        {
            std::system(std::string("omxd X").c_str());
        }

        void OmxPlaylistManager::next()
        {
            std::system(std::string("omxd n").c_str());
        }

        void OmxPlaylistManager::prev()
        {
            std::system(std::string("omxd N").c_str());
        }

        void OmxPlaylistManager::playAtIndex(int index)
        {
            std::system(std::string("omxd g ").append(std::to_string(index)).c_str());
        }

        Playlist OmxPlaylistManager::getPlaylist() const
        {
            int playing = 0;

            std::string toMatch;
            bool matching = false;

            std::string playerInfo = utils::callProcess("omxd S");
            auto playerParts = string::split(playerInfo, " ");
            if (playerParts.size() >= 3)
            {
                matching = true;
                toMatch = playerParts[2];
            }

            std::vector<PlaylistEntry> entries;

            std::ifstream playlistFile("/var/local/omxplay");
            std::string line;
            int i = 0;
            while (std::getline(playlistFile, line))
            {
                if (matching && string::contains(line, toMatch))
                {
                    playing = i;
                }

                for (auto it = this->entries.begin(); it != this->entries.end(); it++)
                {
                    if (string::contains(it->entry.getUrl(), line))
                    {
                        entries.push_back(PlaylistEntry(it->entry.getUrl(), it->entry.getTitle(), i));
                        break;
                    }
                }

                i++;
            }

            return { playing, entries };
        }

        PositionInfo OmxPlaylistManager::getPositionInfo() const
        {
            std::string playerInfo = utils::callProcess("omxd S");
            if (string::contains(playerInfo, "Stopped")) return { 0, 0 };

            auto parts = string::split(playerInfo, " ");
            if (parts.size() < 2) return {0, 0};

            auto timeParts = string::split(parts[1], "/");
            if (timeParts.size() < 2) return {0, 0};

            std::string posString = timeParts[0];
            std::string lenString = timeParts[1];

            return { std::stoi(posString), std::stoi(lenString) };
        }

        state::PlayState OmxPlaylistManager::getPlayState() const
        {
            std::string playerInfo = utils::callProcess("omxd S");

            if (string::contains(playerInfo, "Stopped")) return state::STOPPED;
            if (string::contains(playerInfo, "Playing")) return state::PLAYING;
            if (string::contains(playerInfo, "Paused")) return state::PAUSED;

            return state::STOPPED;
        }

        void OmxPlaylistManager::setPosition(int seconds)
        {
            auto state = this->getPlayState();
            if (state == state::STOPPED) return;

            auto position = this->getPositionInfo();

            int currPos = position.position;

            int distance = seconds - currPos;
            distance /= 30;

            if (distance == 0) return;

            char const *cmd = "omxd f";

            if (distance < 0)
            {
                distance = -distance;
                cmd = "omxd r";
            }

            for (int i = 0; i < distance; i++)
            {
                std::system(cmd);
            }
        }

        void OmxPlaylistManager::setPlayState(state::PlayState state)
        {
            if (state == state::STOPPED)
            {
                std::system("omxd P");
            }
            else
            {
                auto currentState = this->getPlayState();
                if (currentState != state)
                {
                    std::system("omxd p");
                }
            }
        }
    }
}
