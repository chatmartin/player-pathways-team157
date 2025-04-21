

#include "SoccerPlayer.h"

SoccerPlayer::SoccerPlayer(string name, string nationality, int goals, int yellowCards, int assists, int appearances) : Player(name) {
    this->nationality = nationality;
    this->goals = goals;
    this->yellowCards = yellowCards;
    this->assists = assists;
    this->appearances = appearances;
}

int SoccerPlayer::getGoals() const {
    return this->goals;
}

int SoccerPlayer::getYellowCards() const {
    return this->yellowCards;
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

void SoccerPlayer::addAppearance() {
    appearances++;
}

void SoccerPlayer::addAssists(int assists) {
    this->assists += assists;
}

void SoccerPlayer::addYellowCards(int yellowCards) {
    this->yellowCards += yellowCards;
}

void SoccerPlayer::addGoals(int goals) {
    this->goals += goals;
}
