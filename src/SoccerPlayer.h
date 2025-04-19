

#ifndef SOCCERPLAYER_H
#define SOCCERPLAYER_H

#include "Player.h"

class SoccerPlayer: public Player {
private:
    int goals;
    int yellowCards;
    int redCards;
    string nationality;
    int maxGoals;
public:
    SoccerPlayer(string name, string nationality, int height, int yearBorn, int goals, int yellowCards, int redCards, int maxGoals);
    int getGoals() const;
    int getYellowCards() const;
    int getRedCards() const;
    string getNationality();
    int getMaxGoals() const;
};



#endif //SOCCERPLAYER_H
