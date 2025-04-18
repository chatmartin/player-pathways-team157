
#ifndef BASKETBALLPLAYER_H
#define BASKETBALLPLAYER_H

#include "Player.h"
using namespace std;
class BasketballPlayer:public Player {
private:
  int points;
  string college;
  int draftYear;
  int rebounds;
  int gamesPlayed;
  int assists;
public:
    BasketballPlayer(string name, string college, int height, int yearBorn, int jerseyNum, int points, int draftYear, int rebounds, int assists, int gamesPlayed);
    int getPoints() const;
    string getCollege();
    int getDraftYear() const;
    int getRebounds() const;
    int getAssists() const;
    int getGamesPlayed() const;
};



#endif //BASKETBALLPLAYER_H
