

#include "SoccerPlayer.h"

SoccerPlayer::SoccerPlayer(string name, string nationality, int height, int yearBorn, int goals, int yellowCards, int maxGoals, int assists, int appearances) : Player(name, height, yearBorn) {
    this->nationality = nationality;
    this->goals = goals;
    this->yellowCards = yellowCards;
    this->maxGoals = maxGoals;
    this->assists = assists;
    this->appearances = appearances;
}

int SoccerPlayer::getGoals() const {
    return this->goals;
}

int SoccerPlayer::getYellowCards() const {
    return this->yellowCards;
}

int SoccerPlayer::getMaxGoals() const {
    return this->maxGoals;
}

string SoccerPlayer::getNationality() {
    return this->nationality;
}

int SoccerPlayer::getAppearances() const {
    return this->appearances;
}

int SoccerPlayer::getAssists() const {
    return this->assists;
}
