

#include "BasketballPlayer.h"

BasketballPlayer::BasketballPlayer(string name, string college, int height, int yearBorn, int jerseyNum, int points, int draftYear, int rebounds, int assists, int gamesPlayed):Player(name,height,yearBorn,jerseyNum){
  this->college = college;
  this->points = points;
  this->draftYear = draftYear;
  this->rebounds = rebounds;
  this->assists = assists;
  this->gamesPlayed = gamesPlayed;
}