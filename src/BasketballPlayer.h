
#ifndef BASKETBALLPLAYER_H
#define BASKETBALLPLAYER_H

#include "Player.h"
using namespace std;
class BasketballPlayer:public Player {
private:
    int points;
    int rebounds;
    int gamesPlayed;
    int assists;
public:
    BasketballPlayer(string name, int points, int rebounds, int assists, int gamesPlayed);
    BasketballPlayer();
    int getPoints() const;
    int getRebounds() const;
    int getAssists() const;
    int getGamesPlayed() const;
    void addGamesPlayed(int games);
    void addRebounds(int rebounds);
    void addAssists(int assists);
    void addPoints(int points);
};



#endif //BASKETBALLPLAYER_H
