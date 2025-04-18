

#include "BasketballPlayer.h"

BasketballPlayer::BasketballPlayer(string name, string college, int height, int yearBorn, int jerseyNum, int points, int draftYear, int rebounds, int assists, int gamesPlayed):Player(name,height,yearBorn,jerseyNum){
  this->college = college;
  this->points = points;
  this->draftYear = draftYear;
  this->rebounds = rebounds;
  this->assists = assists;
  this->gamesPlayed = gamesPlayed;
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
