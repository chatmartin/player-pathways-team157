
#include "Player.h"

Player::Player() {
    height=0,yearBorn=0;
}

Player::Player(string name, int height, int yearBorn) {
    this->name = name;
    this->height = height;
    this->yearBorn = yearBorn;
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

unordered_map<int, string> Player::getTeamTime() {
    return teamTime;
}

void Player::addTeamTime(int year, string team) {
    if(teamTime.find(year) == teamTime.end()) {
        teamTime[year] = team;
    }
}

bool Player::operator==(const Player &other) const {
    return this->name == other.name;
}

bool Player::operator==(const string &other) const {
    return this->name == other;
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