

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int main(){
    vector<BasketballPlayer> bballers;
    unordered_map<string,int> indHolder;
    ifstream file("all_seasons.csv");
    string line;
    getline(file,line);
    BasketballPlayer currPlayer;
    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> tokens;
        while(getline(ss,value,',')) {
            tokens.push_back(value);
        }
        string name = tokens[0];
        string team = tokens[1];
        int age = stoi(tokens[2]);
        int height = stoi(tokens[3]);
        int weight = stoi(tokens[4]);
        string college = tokens[5];
        int gamesPlayed = stoi(tokens[10]);
        int points = stof(tokens[11])*gamesPlayed;
        int rebounds = stof(tokens[12])*gamesPlayed;
        int assists = stof(tokens[13])*gamesPlayed;
        int year = stoi(tokens[20].substr(0,tokens[20].find('-')));
        int draftYear;
        try {
            draftYear = stoi(tokens[7]);
        }
        catch(...) {
            draftYear = year;
        }
        if(!(currPlayer == name)) {
            BasketballPlayer baller = BasketballPlayer(name,college,height,year-age,points,draftYear,rebounds,assists,gamesPlayed,weight);
            baller.addTeamTime(year,team);
            bballers.push_back(baller);
            indHolder[name] = bballers.size()-1;
            currPlayer = baller;
        }
        else {
            bballers[indHolder[name]].addTeamTime(year,team);
            bballers[indHolder[name]].addAssists(assists);
            bballers[indHolder[name]].addGamesPlayed(gamesPlayed);
            bballers[indHolder[name]].addRebounds(rebounds);
            bballers[indHolder[name]].addPoints(points);
        }
    }
    Graph bballGraph = Graph();
    cout << bballers.size() << endl;
    for(int i = 0;i < bballers.size(); i++) {
        for(int j = i+1; j < bballers.size(); j++) {
            bballGraph.addEdge(bballers[i],bballers[j],bballGraph.findConnection(bballers[i],bballers[j]));
        }
    }
}