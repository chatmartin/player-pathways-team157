
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
    int weight;
public:
    BasketballPlayer(string name, string college, int height, int yearBorn, int points, int draftYear, int rebounds, int assists, int gamesPlayed, int weight);
    BasketballPlayer();
    int getPoints() const;
    string getCollege();
    int getDraftYear() const;
    int getRebounds() const;
    int getAssists() const;
    int getGamesPlayed() const;
    int getWeight() const;
    void addGamesPlayed(int games);
    void addRebounds(int rebounds);
    void addAssists(int assists);
    void addPoints(int points);
};



#endif //BASKETBALLPLAYER_H
