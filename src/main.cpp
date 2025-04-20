

#include <algorithm>

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <windows.h>

using namespace std;

int main(){
    //important for maintaining utf-8 in output
    SetConsoleOutputCP(CP_UTF8);
    //vector holding every basketball player, important for the user to know their options and helps with input
    vector<BasketballPlayer> bballers;
    //holds the index of each player in bballers, which is important for knowing where a player is stored in bballers, making access easy
    unordered_map<string,int> indHolderBBall;
    //taking in data from the basketball dataset
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
        string college = tokens[5];
        int gamesPlayed = stoi(tokens[10]);
        int points = stof(tokens[11])*float(gamesPlayed)+0.5;
        int rebounds = stof(tokens[12])*float(gamesPlayed)+0.5;
        int assists = stof(tokens[13])*float(gamesPlayed)+0.5;
        int year = stoi(tokens[20].substr(0,tokens[20].find('-')));
        if(currPlayerBBall != name) { //if we moved on to a different bball player, make sure we are adding the new player to the list and their attributes
            BasketballPlayer baller = BasketballPlayer(name,points,rebounds,assists,gamesPlayed);
            baller.addTeamTime(year,team);
            bballers.push_back(baller);
            indHolderBBall[name] = bballers.size()-1;
            currPlayerBBall = baller;
        }
        else { //we have already visited this player, we are just editing their attributes
            bballers[indHolderBBall[name]].addTeamTime(year,team);
            bballers[indHolderBBall[name]].addAssists(assists);
            bballers[indHolderBBall[name]].addGamesPlayed(gamesPlayed);
            bballers[indHolderBBall[name]].addRebounds(rebounds);
            bballers[indHolderBBall[name]].addPoints(points);
        }
    }
    file.close();
    //create the basketball graph
    Graph bballGraph = Graph();
    for(int i = 0;i < bballers.size(); i++) {
        for(int j = i+1; j < bballers.size(); j++) {
            bballGraph.addEdge(bballers[i],bballers[j],Graph::findConnection(bballers[i],bballers[j]));
        }
    }

    //vector holding all soccer players in the map, important so the user knows what options they have and helps with dealing with input
    vector<SoccerPlayer> fballers;
    //holds the index of each player in fballers, which is important for knowing where a player is stored in fballers, making access easy
    unordered_map<string,int> indHolderFBall;
    //id holders which are important for reading data
    unordered_map<int,string> playerID;
    unordered_map<int,string> clubID;
    //creating buckets for each category to make adding edges much faster later on
    unordered_map<string,vector<SoccerPlayer>> natBucket;
    unordered_map<int,vector<SoccerPlayer>> goalBucket;
    unordered_map<int,vector<SoccerPlayer>> yellowBucket;
    unordered_map<int,vector<SoccerPlayer>> assistBucket;
    map<pair<int,string>,vector<SoccerPlayer>> teamBucket;
    unordered_map<int,vector<SoccerPlayer>> appearBucket;
    //gathering data from each club, specifically storing the id number which is important for later
    ifstream file1("clubs.csv");
    getline(file1,line);
    while(getline(file1,line)) {
        istringstream iss(line);
        string value;
        vector<string> tokens;
        while(getline(iss,value,',')) {
            tokens.push_back(value);
        }
        clubID[stoi(tokens[0])] = tokens[2];
    }
    //gathering data from the players themselves
    ifstream file2("fballer.csv");
    getline(file2,line);
    while(getline(file2,line)) {
        istringstream iss(line);
        string value;
        vector<string> tokens;
        while(getline(iss,value,',')) {
            tokens.push_back(value);
        }
        playerID[stoi(tokens[0])] = tokens[3];
        fballers.emplace_back(tokens[3],tokens[9],0,0,0,0);
        indHolderFBall[tokens[3]] = fballers.size()-1;
        natBucket[tokens[9]].push_back(fballers[fballers.size()-1]);
    }
    //gathering data from each player's appearance in a game
    ifstream file3("appearances.csv");
    getline(file3,line);
    while(getline(file3,line)) {
        istringstream iss(line);
        string value;
        vector<string> tokens;
        while(getline(iss,value,',')) {
            tokens.push_back(value);
        }
        int pID = stoi(tokens[2]);
        int cID = stoi(tokens[3]);
        int year = stoi(tokens[5].substr(0,tokens[5].find('-')));
        int yellowCards = stoi(tokens[8]);
        int goals = stoi(tokens[10]);
        int assists = stoi(tokens[11]);
        SoccerPlayer& fballer = fballers[indHolderFBall[playerID[pID]]];
        fballer.addAssists(assists);
        fballer.addAppearance();
        fballer.addGoals(goals);
        fballer.addYellowCards(yellowCards);
        if(!fballer.getTeamTime().count(year) && clubID[cID]!="") {
            fballer.addTeamTime(year,clubID[cID]);
            teamBucket[{year,clubID[cID]}].push_back(fballer);
        }
    }
    for(auto& fballer : fballers) {
        goalBucket[fballer.getGoals()].push_back(fballer);
        assistBucket[fballer.getAssists()].push_back(fballer);
        yellowBucket[fballer.getYellowCards()].push_back(fballer);
        appearBucket[fballer.getAppearances()].push_back(fballer);
    }

    //create the soccer graph
    Graph fballGraph = Graph();
    //add edges between soccer players using buckets to avoid having to do an O(|V|^2) brute force approach
    for(auto p: teamBucket) {
        if(p.first.second == "") {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::teamTime);
            }
        }
    }
    for(auto p: goalBucket) {
        if(p.first < 5) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::goals);
            }
        }
    }
    for(auto p: assistBucket) {
        if(p.first < 3) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::assists);
            }
        }
    }
    for(auto p: yellowBucket) {
        if(p.first < 5) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::yellowCards);
            }
        }
    }
    for(auto p: appearBucket) {
        if(p.first < 20) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::gamesPlayed);
            }
        }
    }
    //get rid of any vertices with no connection in fballers
    for(int i = 0; i < fballers.size(); i++) {
        if(fballGraph.getAdjList().find(fballers[i])==fballGraph.getAdjList().end()) {
            fballers[i]=fballers.back();
            fballers.pop_back();
            i--;
        }
    }
    //get rid of duplicates in fballers
    sort(fballers.begin(), fballers.end());
    fballers.erase(unique(fballers.begin(), fballers.end()), fballers.end());
    //make sure the graph is fully connected
    vector<Player> nonConnected = fballGraph.checkConnectivity(fballers[0]);
    for(int i = 0; i < nonConnected.size(); i++) {
        fballGraph.getAdjList().erase(nonConnected[i]);
        fballers[i] = fballers.back();
        fballers.pop_back();
    }
    //reconfigure the index table so we don't get any incorrect indices
    for(int i = 0; i < fballers.size(); i++) {
        indHolderFBall[fballers[i].getName()] = i;
    }
}