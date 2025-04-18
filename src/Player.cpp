

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

string Player::getName() {
    return this->name;
}

int Player::getHeight() {
    return this->height;
}

int Player::getYearBorn() {
    return this->yearBorn;
}

int Player::getJerseyNum() {
    return this->jerseyNum;
}

map<int, string> Player::getTeamTime() {
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
