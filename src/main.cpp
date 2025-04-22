#include <algorithm>
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#define ASIO_STANDALONE
#include "crow.h"
#include <chrono>
#include <unordered_set>
#include "crow/middlewares/cors.h"
#include "crow/middlewares/session.h"

using namespace std;
using json=nlohmann::json;
//converts basketball players to json to be used in the frontend
void to_json(json& j, const BasketballPlayer& bballer) {
    j = json{
        {"name",bballer.getName()},
        {"points",bballer.getPoints()},
        {"rebounds",bballer.getRebounds()},
        {"assists",bballer.getAssists()},
        {"games",bballer.getGamesPlayed()},
        {"teamTime",bballer.getTeamTime()}
    };
}

//converts soccer players to json to be used in the frontend
void to_json(json& j, const SoccerPlayer& fballer) {
    j = json{
        {"name",fballer.getName()},
        {"goals",fballer.getGoals()},
        {"yellow",fballer.getYellowCards()},
        {"assists",fballer.getAssists()},
        {"games",fballer.getAppearances()},
        {"teamTime",fballer.getTeamTime()}
    };
}

void createBBallGraph(vector<BasketballPlayer>& bballers,unordered_map<string,int>& indHolderBBall,Graph& bballGraph) {
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
        int points = lround(stof(tokens[11])*float(gamesPlayed));
        int rebounds = lround(stof(tokens[12])*float(gamesPlayed));
        int assists = lround(stof(tokens[13])*float(gamesPlayed));
        int year = stoi(tokens[20].substr(0,tokens[20].find('-')));
        if(currPlayerBBall != name) { //if we moved on to a different bball player, make sure we are adding the new player to the list and their attributes
            BasketballPlayer baller = BasketballPlayer(name,points,rebounds,assists,gamesPlayed);
            baller.addTeamTime(year,team);
            bballers.push_back(baller);
            indHolderBBall[name] = int(bballers.size())-1;
            currPlayerBBall = baller;
        }
        else { //we have already visited this player, we are just editing its attributes
            bballers[indHolderBBall[name]].addTeamTime(year,team);
            bballers[indHolderBBall[name]].addAssists(assists);
            bballers[indHolderBBall[name]].addGamesPlayed(gamesPlayed);
            bballers[indHolderBBall[name]].addRebounds(rebounds);
            bballers[indHolderBBall[name]].addPoints(points);
        }
    }
    file.close();
    //create the basketball graph
    for(int i = 0;i < bballers.size(); i++) {
        for(int j = i+1; j < bballers.size(); j++) {
            bballGraph.addEdge(bballers[i],bballers[j],Graph::findConnection(bballers[i],bballers[j]));
        }
    }
}

void createFBallGraph(vector<SoccerPlayer>& fballers,unordered_map<string,int>& indHolderFBall,Graph& fballGraph) {
    string line;
    unordered_set<string> prevPlayers;
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
        if(prevPlayers.find(tokens[3])==prevPlayers.end()) {
            playerID[stoi(tokens[0])] = tokens[3];
            fballers.emplace_back(tokens[3],tokens[9],0,0,0,0);
            indHolderFBall[tokens[3]] = int(fballers.size())-1;
            natBucket[tokens[9]].push_back(fballers[fballers.size()-1]);
            prevPlayers.insert(tokens[3]);
        }
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
        if(!fballer.getTeamTime().count(year) && !clubID[cID].empty()) {
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
    //add edges between soccer players using buckets to avoid having to do an O(|V|^2) brute force approach
    for(auto p: teamBucket) {
        if(p.first.second.empty()) {
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
        if(p.first < 5) {
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
    //reconfigure the index table so we don't get any incorrect indices
    for(int i = 0; i < fballers.size(); i++) {
        indHolderFBall[fballers[i].getName()] = i;
    }
}

int main(){
    //important for maintaining utf-8 in output
    SetConsoleOutputCP(CP_UTF8);

    //vector holding every basketball player, important for the user to know their options and helps with input
    vector<BasketballPlayer> bballers;
    //holds the index of each player in bballers, which is important for knowing where a player is stored in bballers, making access easy
    unordered_map<string,int> indHolderBBall;
    //create the basketball graph
    Graph bballGraph;
    createBBallGraph(bballers,indHolderBBall,bballGraph);

    //vector holding all soccer players in the map, important so the user knows what options they have and helps with dealing with input
    vector<SoccerPlayer> fballers;
    //holds the index of each player in fballers, which is important for knowing where a player is stored in fballers, making access easy
    unordered_map<string,int> indHolderFBall;
    //create the soccer graph
    Graph fballGraph;
    createFBallGraph(fballers,indHolderFBall,fballGraph);

    using json = nlohmann::json;
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type","X-Custom-Header","Upgrade-Insecure-Requests","Accept","Access-Control-Allow-Origin")
        .methods("POST"_method,"GET"_method)
        .origin("http://localhost:5173")
        .max_age(3600);

    CROW_ROUTE(app, "/bball_graph")
    .methods("GET"_method)([&bballGraph,&bballers]() {
        json j;
        j["players"] = bballers;
        return crow::response{j.dump()};
    });

    CROW_ROUTE(app,"/fball_graph")
    .methods("GET"_method)([&fballGraph,&fballers]() {
        json j;
        j["players"] = fballers;
        return crow::response{j.dump()};
    });

    CROW_ROUTE(app, "/bballAlgo")
    .methods("POST"_method)([&bballGraph,&bballers,&indHolderBBall](const crow::request& req) {
        auto body = json::parse(req.body);
        if(!body.contains("from") || !body.contains("to") ||
            indHolderBBall.find(body["from"])==indHolderBBall.end() ||
            indHolderBBall.find(body["to"])==indHolderBBall.end()) {
            return crow::response(400,"Please input valid NBA players from 1992-2022.");
        }
        string from = body["from"];
        string to = body["to"];
        json j;
        const Player& src = bballers[indHolderBBall.at(from)];
        const Player& dest = bballers[indHolderBBall.at(to)];
        auto start = chrono::high_resolution_clock::now();
        auto bfsPath = bballGraph.shortestPathBFS(src,dest);
        auto stop = chrono::high_resolution_clock::now();
        auto bfsTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
        start = chrono::high_resolution_clock::now();
        auto dijkPath = bballGraph.shortestPathDijkstra(src,dest);
        stop = chrono::high_resolution_clock::now();
        auto dijkTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
        vector<pair<BasketballPlayer,string>> trueBfsPath;
        for(int i = 0; i < bfsPath.size()-1; i++) {
            BasketballPlayer b = (bballers[indHolderBBall.at(bfsPath[i].first.getName())]);
            Graph::Connection c = bfsPath[i+1].second;
            string reason;
            auto b2 = (bballers[indHolderBBall.at(bfsPath[i+1].first.getName())]);
            if(c == 1) {
                auto tt = b2.getTeamTime();
                for(const auto& p: b.getTeamTime()) {
                    if(tt.find(p.first) != tt.end()) {
                        if(tt[p.first] == p.second) {
                            reason = " was in the team " + p.second + " in the year " + to_string(p.first) + " with ";
                            break;
                        }
                    }
                }
            }
            else if(c == 5) {
                reason = " got " + to_string(b.getPoints()) + " points like ";
            }
            else if(c == 6) {
                reason = " got " + to_string(b.getRebounds()) + " rebounds like ";
            }
            else if(c == 7) {
                reason = " played " + to_string(b.getGamesPlayed()) + " games like ";
            }
            else if(c == 8) {
                reason = " got " + to_string(b.getAssists()) + " assists like ";
            }
            reason.insert(0,b.getName());
            reason.append(b2.getName());
            reason.append(".");
            trueBfsPath.emplace_back(b,reason);
        }
        trueBfsPath.emplace_back(bballers[indHolderBBall.at(bfsPath[bfsPath.size()-1].first.getName())],"");
        vector<pair<BasketballPlayer,string>> trueDijkPath;
        for(int i = 0; i < dijkPath.size()-1; i++) {
            BasketballPlayer b = (bballers[indHolderBBall.at(dijkPath[i].first.getName())]);
            Graph::Connection c = dijkPath[i].second;
            string reason;
            auto b2 = (bballers[indHolderBBall.at(dijkPath[i+1].first.getName())]);
            if(c == 1) {
                auto tt = b2.getTeamTime();
                for(const auto& p: b.getTeamTime()) {
                    if(tt.find(p.first) != tt.end()) {
                        if(tt[p.first] == p.second) {
                            reason = " was in the team " + p.second + " in the year " + to_string(p.first) + " with ";
                            break;
                        }
                    }
                }
            }
            else if(c == 5) {
                reason = " got " + to_string(b.getPoints()) + " points like ";
            }
            else if(c == 6) {
                reason = " got " + to_string(b.getRebounds()) + " rebounds like ";
            }
            else if(c == 7) {
                reason = " played " + to_string(b.getGamesPlayed()) + " games like ";
            }
            else if(c == 8) {
                reason = " got " + to_string(b.getAssists()) + " assists like ";
            }
            reason.insert(0,b.getName());
            reason.append(b2.getName());
            reason.append(".");
            trueDijkPath.emplace_back(b,reason);
        }
        trueDijkPath.emplace_back(bballers[indHolderBBall.at(dijkPath[dijkPath.size()-1].first.getName())],"");
        j["bfsPath"] = trueBfsPath;
        double b = int(bfsTime.count())/1000.0;
        j["bfsTime"] = b;
        j["dijkPath"] = trueDijkPath;
        double d = int(dijkTime.count())/1000.0;
        j["dijkTime"] = d;
        return crow::response{j.dump()};
    });

    CROW_ROUTE(app, "/fballAlgo")
    .methods("POST"_method)
    ([&fballGraph,&fballers,&indHolderFBall](const crow::request& req) {
        auto body = json::parse(req.body);
        if(!body.contains("from") || !body.contains("to") ||
            indHolderFBall.find(body["from"])==indHolderFBall.end() ||
            indHolderFBall.find(body["to"])==indHolderFBall.end()) {
            return crow::response(400,"Please input valid soccer players.");
        }
        string from = body["from"];
        string to = body["to"];
        json j;
        const Player& src = fballers[indHolderFBall.at(from)];
        const Player& dest = fballers[indHolderFBall.at(to)];
        auto start = chrono::high_resolution_clock::now();
        auto bfsPath = fballGraph.shortestPathBFS(src,dest);
        auto stop = chrono::high_resolution_clock::now();
        auto bfsTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
        start = chrono::high_resolution_clock::now();
        auto dijkPath = fballGraph.shortestPathDijkstra(src,dest);
        stop = chrono::high_resolution_clock::now();
        auto dijkTime = chrono::duration_cast<chrono::milliseconds>(stop - start);
        vector<pair<SoccerPlayer,string>> trueBfsPath;
        for(int i = 0; i < bfsPath.size()-1; i++) {
            SoccerPlayer f = (fballers[indHolderFBall.at(bfsPath[i].first.getName())]);
            Graph::Connection c = bfsPath[i+1].second;
            string reason;
            auto f2 = (fballers[indHolderFBall.at(bfsPath[i+1].first.getName())]);
            if(c == 1) {
                auto nextTT = f2.getTeamTime();
                for(const auto& p: f.getTeamTime()) {
                    if(nextTT.find(p.first) != nextTT.end()) {
                        if(nextTT[p.first] == p.second) {
                            reason = " was in the team " + p.second + " in the year " + to_string(p.first) + " with ";
                            break;
                        }
                    }
                }
            }
            else if(c == 2) {
                reason = " got " + to_string(f.getGoals()) + " goals like ";
            }
            else if(c == 3) {
                reason = " got " + to_string(f.getYellowCards()) + " yellow cards like ";
            }
            else if(c == 7) {
                reason = " played " + to_string(f.getAppearances()) + " games like ";
            }
            else if(c == 8) {
                reason = " got " + to_string(f.getAssists()) + " assists like ";
            }
            reason.insert(0,f.getName());
            reason.append(f2.getName());
            reason.append(".");
            trueBfsPath.emplace_back(f,reason);
        }
        if(!bfsPath.empty()){
            trueBfsPath.emplace_back(fballers[indHolderFBall.at(bfsPath[bfsPath.size()-1].first.getName())],"");
        }
        else{
            string reason = "There is no connection between " + src.getName() + " and " + dest.getName();
            trueBfsPath.emplace_back(fballers[indHolderFBall[from]],reason);
            trueBfsPath.emplace_back(fballers[indHolderFBall[to]],"");
        }
        vector<pair<SoccerPlayer,string>> trueDijkPath;
        for(int i = 0; i < dijkPath.size()-1; i++) {
            SoccerPlayer f = (fballers[indHolderFBall.at(dijkPath[i].first.getName())]);
            Graph::Connection c = dijkPath[i].second;
            string reason;
            auto f2 = (fballers[indHolderFBall.at(dijkPath[i+1].first.getName())]);
            if(c == 1) {
                auto nextTT = f2.getTeamTime();
                for(const auto& p: f.getTeamTime()) {
                    if(nextTT.find(p.first) != nextTT.end()) {
                        if(nextTT[p.first] == p.second) {
                            reason = " was in the team " + p.second + " in the year " + to_string(p.first) + " with ";
                            break;
                        }
                    }
                }
            }
            else if(c == 2) {
                reason = " got " + to_string(f.getGoals()) + " goals like ";
            }
            else if(c == 3) {
                reason = " got " + to_string(f.getYellowCards()) + " yellow cards like ";
            }
            else if(c == 7) {
                reason = " played " + to_string(f.getAppearances()) + " games like ";
            }
            else if(c == 8) {
                reason = " got " + to_string(f.getAssists()) + " assists like ";
            }
            reason.insert(0,f.getName());
            reason.append(f2.getName());
            reason.append(".");
            trueDijkPath.emplace_back(f,reason);
        }
        if(!bfsPath.empty()){
            trueDijkPath.emplace_back(fballers[indHolderFBall.at(dijkPath[dijkPath.size()-1].first.getName())],"");
        }
        else{
            string reason = "There is no connection between " + src.getName() + " and " + dest.getName();
            trueDijkPath.emplace_back(fballers[indHolderFBall[from]],reason);
            trueDijkPath.emplace_back(fballers[indHolderFBall[to]],"");
        }
        j["bfsPath"] = trueBfsPath;
        double b = int(bfsTime.count())/1000.0;
        j["bfsTime"] = b;
        j["dijkPath"] = trueDijkPath;
        double d = int(dijkTime.count())/1000.0;
        j["dijkTime"] = d;
        return crow::response{j.dump()};
    });

    app.port(18080).multithreaded().run();

    //below is used for testing, comment it out for actual use
    /*cout << "enter input" << endl;
    string ball;
    getline(cin,ball);
    cout<<endl;
    string player1;
    getline(cin,player1);
    cout<<endl;
    string player2;
    getline(cin,player2);
    if(stoi(ball)) {
        auto v = bballGraph.shortestPathBFS(bballers[indHolderBBall[player1]],bballers[indHolderBBall[player2]]);
        for(auto p: v) {
            cout << p.first.getName() << " " << p.second << endl;
        }
    }
    else {
        auto v = fballGraph.shortestPathBFS(fballers[indHolderFBall[player1]],fballers[indHolderFBall[player2]]);
        for(auto p: v) {
            cout << p.first.getName() << " " << p.second << endl;
        }
    }*/
}