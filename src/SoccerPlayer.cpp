

#include "SoccerPlayer.h"

SoccerPlayer::SoccerPlayer(string name, string nationality, int height, int yearBorn, int jerseyNum, int goals, int yellowCards, int redCards, int maxGoals) : Player(name,height,yearBorn,jerseyNum) {
    this->nationality = nationality;
    this->goals = goals;
    this->yellowCards = yellowCards;
    this->redCards = redCards;
    this->maxGoals = maxGoals;
}

int SoccerPlayer::getGoals() const {
    return this->goals;
}

int SoccerPlayer::getYellowCards() const {
    return this->yellowCards;
}

int SoccerPlayer::getRedCards() const {
    return this->redCards;
}

int SoccerPlayer::getMaxGoals() const {
    return this->maxGoals;
}

string SoccerPlayer::getNationality() {
    return this->nationality;
}
