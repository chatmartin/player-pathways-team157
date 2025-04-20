

#ifndef SOCCERPLAYER_H
#define SOCCERPLAYER_H

#include "Player.h"

class SoccerPlayer: public Player {
private:
    int goals;
    int yellowCards;
    string nationality;
    int assists;
    int appearances;

public:
    SoccerPlayer(string name, string nationality, int goals, int yellowCards, int assists, int appearances);
    int getGoals() const;
    int getYellowCards() const;
    string getNationality();
    int getAssists() const;
    int getAppearances() const;
    void addGoals(int goals);
    void addYellowCards(int yellowCards);
    void addAppearance();
    void addAssists(int assists);
};



#endif //SOCCERPLAYER_H
