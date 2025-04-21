
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <map>

using namespace std;

class Player {
    string name; //holds the name of a player
    map<int,string> teamTime; //use an ordered map here because it's easier to manage by year, represents the team a player was on during a given year
public:
    Player(string name);
    Player();
    string getName() const;
    map<int,string> getTeamTime() const;
    void addTeamTime(int year, string team);
    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;
    bool operator==(const string& other) const;
    bool operator<(const Player& other) const;
    bool operator>(const Player& other) const;
    bool operator<=(const Player& other) const;
    bool operator>=(const Player& other) const;
    virtual ~Player();
};
//hash for player so it can be used in unordered maps and sets, which are more efficient
namespace std {
    template<>
    struct hash<Player> {
        size_t operator()(const Player &p) const noexcept {
            return hash<string>()(p.getName());
        }
    };
}

#endif //PLAYER_H
