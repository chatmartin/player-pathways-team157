
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>

using namespace std;
class Player {
    string name;
    int height;
    int yearBorn;
    int jerseyNum;
    unordered_map<int,string> teamTime;
public:
    Player(string name, int height, int yearBorn, int jerseyNum);
    Player();
    string getName() const;
    int getHeight() const;
    int getYearBorn() const;
    int getJerseyNum() const;
    unordered_map<int,string> getTeamTime();
    void addTeamTime(int year, string team);
    bool operator==(const Player& other);
    bool operator<(const Player& other) const;
    bool operator>(const Player& other) const;
    bool operator<=(const Player& other) const;
    bool operator>=(const Player& other) const;
};



#endif //PLAYER_H
