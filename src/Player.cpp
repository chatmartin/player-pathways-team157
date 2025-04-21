
#include "Player.h"

Player::Player() = default;

Player::Player(string name) {
    this->name = name;
}

string Player::getName() const {
    return this->name;
}

map<int, string> Player::getTeamTime() const {
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

bool Player::operator!=(const Player &other) const {
    return this->name != other.name;
}

bool Player::operator==(const string &other) const {
    return this->name == other;
}

bool Player::operator<(const Player &other) const {
    return this->name < other.name;
}

bool Player::operator>(const Player &other) const {
    return this->name > other.name;
}

bool Player::operator<=(const Player &other) const {
    return this->name <= other.name;
}

bool Player::operator>=(const Player &other) const {
    return this->name >= other.name;
}

Player::~Player()=default;