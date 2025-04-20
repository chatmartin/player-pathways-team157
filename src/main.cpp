

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    vector<BasketballPlayer> bballers;
    unordered_map<string,int> indHolderBBall;
    ifstream file("all_seasons.csv");
    string line;
    getline(file,line);
    BasketballPlayer currPlayerBBall;
    while(getline(file,line)) {
        istringstream iss(line);
        string value;
        vector<string> tokens;
        while(getline(iss,value,',')) {
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
        if(!(currPlayerBBall == name)) {
            BasketballPlayer baller = BasketballPlayer(name,college,height,year-age,points,draftYear,rebounds,assists,gamesPlayed,weight);
            baller.addTeamTime(year,team);
            bballers.push_back(baller);
            indHolderBBall[name] = bballers.size()-1;
            currPlayerBBall = baller;
        }
        else {
            bballers[indHolderBBall[name]].addTeamTime(year,team);
            bballers[indHolderBBall[name]].addAssists(assists);
            bballers[indHolderBBall[name]].addGamesPlayed(gamesPlayed);
            bballers[indHolderBBall[name]].addRebounds(rebounds);
            bballers[indHolderBBall[name]].addPoints(points);
        }
    }
    file.close();
    Graph bballGraph = Graph();
    cout << bballers.size() << endl;
    for(int i = 0;i < bballers.size(); i++) {
        for(int j = i+1; j < bballers.size(); j++) {
            bballGraph.addEdge(bballers[i],bballers[j],bballGraph.findConnection(bballers[i],bballers[j]));
        }
    }

    vector<BasketballPlayer> fballers;
    unordered_map<string,int> indHolderFBall;
    unordered_map<int,string> playerID;
    unordered_map<int,string> clubID;
    file.open("clubs.csv");
    getline(file,line);
    while(getline(file,line)) {
        istringstream iss(line);
        string value;
        vector<string> tokens;
        while(getline(iss,value,',')) {
            tokens.push_back(value);
        }
        clubID[stoi(tokens[0])] = tokens[2];
    }
    file.close();
    file.open("fballer.csv");
    getline(file,line);
    while(getline(file,line)) {
        istringstream iss(line);
        string value;
        vector<string> tokens;
        while(getline(iss,value,',')) {
            tokens.push_back(value);
        }
        playerID[stoi(tokens[0])] = tokens[3];
    }
    file.close();
    //TODO: Write the code for gathering all the data into SoccerPlayers
}