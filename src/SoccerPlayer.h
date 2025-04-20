

#ifndef SOCCERPLAYER_H
#define SOCCERPLAYER_H

#include "Player.h"
//TODO: get rid of unnecessary fields
class SoccerPlayer: public Player {
private:
    int goals;
    int yellowCards;
    string nationality;
    bool hatTrick;
    int assists;
    int appearances;

public:
    SoccerPlayer(string name, string nationality, int height, int yearBorn, int goals, int yellowCards, int assists, int appearances, bool hatTrick);
    int getGoals() const;
    int getYellowCards() const;
    string getNationality();
    bool getHatTrick() const;
    int getAssists() const;
    int getAppearances() const;
    void addGoals(int goals);
    void addYellowCards(int yellowCards);
    void addAppearance();
    void addAssists(int assists);
    void hasHatTrick();
};



#endif //SOCCERPLAYER_H
