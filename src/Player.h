
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

using namespace std;
class Player {
    string name;
    int height;
    int yearBorn;
    int jerseyNum;
    //TODO: Create a hashmap class for data structure 2
    map<int,string> teamTime;
public:
    Player(string name, int height, int yearBorn, int jerseyNum);
    string getName();
    int getHeight();
    int getYearBorn();
    int getJerseyNum();
    map<int,string> getTeamTime();
    void addTeamTime(int year, string team);
    bool operator==(const Player& other);
    bool operator<(const Player& other) const;
    bool operator>(const Player& other) const;
    bool operator<=(const Player& other) const;
    bool operator>=(const Player& other) const;
};



#endif //PLAYER_H
