

#include "Player.h"

Player::Player() {
    height=0,yearBorn=0,jerseyNum=-1;
}

Player::Player(string name, int height, int yearBorn, int jerseyNum) {
    this->name = name;
    this->height = height;
    this->yearBorn = yearBorn;
    this->jerseyNum = jerseyNum;
}

string Player::getName() const {
    return this->name;
}

int Player::getHeight() const {
    return this->height;
}

int Player::getYearBorn() const {
    return this->yearBorn;
}

int Player::getJerseyNum() const {
    return this->jerseyNum;
}

unordered_map<int, string> Player::getTeamTime() {
    return teamTime;
}

void Player::addTeamTime(int year, string team) {
    if(teamTime.find(year) == teamTime.end()) {
        teamTime[year] = team;
    }
}

bool Player::operator==(const Player &other) {
    return this->name == other.name;
}

bool Player::operator<(const Player &other) const {
    return this->yearBorn < other.yearBorn;
}

bool Player::operator>(const Player &other) const {
    return this->yearBorn > other.yearBorn;
}

bool Player::operator<=(const Player &other) const {
    return this->yearBorn <= other.yearBorn;
}

bool Player::operator>=(const Player &other) const {
    return this->yearBorn >= other.yearBorn;
}

namespace std {
    template<>
    struct hash<Player> {
        size_t operator()(const Player &p) const {
            string name = p.getName();
            size_t hash = 0;
            for(size_t i =0; i < name.length(); i++) {
                hash += name[i]*(i+1);
            }
            return hash;
        }
    };
}