

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
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

    vector<SoccerPlayer> fballers;
    unordered_map<string,int> indHolderFBall;
    unordered_map<int,string> playerID;
    unordered_map<int,string> clubID;
    unordered_map<string,vector<SoccerPlayer>> natBucket;
    unordered_map<int,vector<SoccerPlayer>> goalBucket;
    unordered_map<int,vector<SoccerPlayer>> yellowBucket;
    unordered_map<int,vector<SoccerPlayer>> assistBucket;
    map<pair<int,string>,vector<SoccerPlayer>> teamBucket;
    unordered_map<int,vector<SoccerPlayer>> heightBucket;
    vector<SoccerPlayer> hatBucket;
    unordered_map<int,vector<SoccerPlayer>> birthBucket;
    unordered_map<int,vector<SoccerPlayer>> appearBucket;
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
        int height;
        try {
            height = stoi(tokens[14]);
        }
        catch(...) {
            height = -1;
        }
        int yearBorn;
        try {
            yearBorn = stoi(tokens[10].substr(0,tokens[10].find('-')));
        }
        catch(...) {
            yearBorn = -1;
        }
        fballers.emplace_back(tokens[3],tokens[9],height,yearBorn,0,0,0,0,0);
        indHolderFBall[tokens[3]] = fballers.size()-1;
        natBucket[tokens[9]].push_back(fballers[fballers.size()-1]);
        heightBucket[height].push_back(fballers[fballers.size()-1]);
        birthBucket[yearBorn].push_back(fballers[fballers.size()-1]);
    }
    cout << "done" << endl;
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
        if(goals>=3) {
            fballer.hasHatTrick();
        }
        if(!fballer.getTeamTime().count(year) && clubID[cID]!="") {
            fballer.addTeamTime(year,clubID[cID]);
            teamBucket[{year,clubID[cID]}].push_back(fballer);
        }
    }
    for(auto& fballer : fballers) {
        goalBucket[fballer.getGoals()].push_back(fballer);
        assistBucket[fballer.getAssists()].push_back(fballer);
        yellowBucket[fballer.getYellowCards()].push_back(fballer);
        if(fballer.getHatTrick()) {
            hatBucket.push_back(fballer);
        }
        appearBucket[fballer.getAppearances()].push_back(fballer);
    }
    cout << fballers.size() << endl;
    Graph fballGraph = Graph();

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
    cout << "done";
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
    cout << "done";
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
    cout << "done";
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
    /*cout << "done";
    for(int i = 0; i < hatBucket.size(); i++) {
        for(int j = i+1; j < hatBucket.size(); j++) {
            fballGraph.addEdge(hatBucket[i],hatBucket[j],Graph::hatTrick);
        }
    }*/
    cout << "done";
    /*for(auto p: natBucket) {
        if(p.first == "") {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::nationality);
            }
        }
    }*/
    cout << "done";
    for(auto p: appearBucket) {
        if(p.first < 10) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::gamesPlayed);
            }
        }
    }
    cout << "done";
    /*for(auto p : heightBucket) {
        if(p.first == -1) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::height);
            }
        }
    }
    cout << "done";
    for(auto p: birthBucket) {
        if(p.first == -1) {
            continue;
        }
        for(int i = 0; i < p.second.size(); i++) {
            for(int j = i+1; j < p.second.size(); j++) {
                fballGraph.addEdge(p.second[i],p.second[j],Graph::yearBorn);
            }
        }
    }*/
    cout << "complete" << endl;
    for(int i = 0; i < fballers.size(); i++) {
        if(fballGraph.getAdjList().find(fballers[i])==fballGraph.getAdjList().end()) {
            fballers[i]=fballers.back();
            fballers.pop_back();
            i--;
        }
    }
    cout << fballers.size() << endl;
    cout << "done" << endl;
    auto v = fballGraph.shortestPathBFS(fballers[indHolderFBall["Lionel Messi"]], fballers[indHolderFBall["Cristiano Ronaldo"]]);
    for(auto p: v) {
        cout << p.first.getName() << " " << p.second << endl;
    }
    v = fballGraph.shortestPathDijkstra(fballers[indHolderFBall["Lionel Messi"]], fballers[indHolderFBall["Cristiano Ronaldo"]]);
    for(auto p: v) {
        cout << p.first.getName() << " " << p.second << endl;
    }
    cout << "done";
}