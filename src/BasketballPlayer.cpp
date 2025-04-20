

#include "BasketballPlayer.h"

BasketballPlayer::BasketballPlayer():Player() {
  points = 0;
  rebounds = 0;
  gamesPlayed = 0;
  assists = 0;
}

BasketballPlayer::BasketballPlayer(string name, int points, int rebounds, int assists, int gamesPlayed):Player(name){
  this->points = points;
  this->rebounds = rebounds;
  this->assists = assists;
  this->gamesPlayed = gamesPlayed;
}

int BasketballPlayer::getPoints() const {
  return this->points;
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
