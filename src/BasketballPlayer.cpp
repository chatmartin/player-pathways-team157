

#include "BasketballPlayer.h"

BasketballPlayer::BasketballPlayer():Player() {
  points = 0;
  draftYear = 0;
  rebounds = 0;
  gamesPlayed = 0;
  assists = 0;
}

BasketballPlayer::BasketballPlayer(string name, string college, int height, int yearBorn, int points, int draftYear, int rebounds, int assists, int gamesPlayed, int weight):Player(name,height,yearBorn){
  this->college = college;
  this->points = points;
  this->draftYear = draftYear;
  this->rebounds = rebounds;
  this->assists = assists;
  this->gamesPlayed = gamesPlayed;
  this->weight = weight;
}

int BasketballPlayer::getPoints() const {
  return this->points;
}

int BasketballPlayer::getDraftYear() const {
  return this->draftYear;
}

int BasketballPlayer::getRebounds() const {
  return this->rebounds;
}

int BasketballPlayer::getAssists() const {
  return this->assists;
}

int BasketballPlayer::getGamesPlayed() const {
  return this->gamesPlayed;
}

string BasketballPlayer::getCollege() {
  return this->college;
}

int BasketballPlayer::getWeight() const {
  return weight;
}


void BasketballPlayer::addAssists(int assists) {
  this->assists += assists;
}

void BasketballPlayer::addPoints(int points) {
  this->points += points;
}

void BasketballPlayer::addRebounds(int rebounds) {
  this->rebounds += rebounds;
}

void BasketballPlayer::addGamesPlayed(int games) {
  gamesPlayed += games;
}
