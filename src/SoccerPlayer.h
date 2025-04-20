

#ifndef SOCCERPLAYER_H
#define SOCCERPLAYER_H

#include "Player.h"
//TODO: get rid of unnecessary fields
class SoccerPlayer: public Player {
private:
    int goals;
    int yellowCards;
    string nationality;
    int maxGoals;
    int assists;
    int appearances;

public:
    SoccerPlayer(string name, string nationality, int height, int yearBorn, int goals, int yellowCards, int maxGoals, int assists, int appearances);
    int getGoals() const;
    int getYellowCards() const;
    string getNationality();
    int getMaxGoals() const;
    int getAssists() const;
    int getAppearances() const;
};



#endif //SOCCERPLAYER_H
