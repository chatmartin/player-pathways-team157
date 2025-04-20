
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <map>

using namespace std;

class Player {
    string name;
    map<int,string> teamTime;
public:
    Player(string name);
    Player();
    string getName() const;
    map<int,string> getTeamTime();
    void addTeamTime(int year, string team);
    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;
    bool operator==(const string& other) const;
    bool operator<(const Player& other) const;
    bool operator>(const Player& other) const;
    bool operator<=(const Player& other) const;
    bool operator>=(const Player& other) const;
};

namespace std {
    template<>
    struct hash<Player> {
        size_t operator()(const Player &p) const noexcept {
            return hash<string>()(p.getName());
        }
    };
}

#endif //PLAYER_H
