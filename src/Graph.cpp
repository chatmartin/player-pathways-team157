

#include "Graph.h"

Graph::Graph(){
    adjList = HashMap<HashMap<Connection>>(100000);
}

bool Graph::addEdge(Player& p1, Player& p2, Connection c) {
    if(c == none) {
        return false;
    }
    if(adjList.find(p1)) {
        if(adjList[p1].find(p2)) {
            return false;
        }
        adjList[p1].insert(p2,c);
    }
    else {
        HashMap<Connection> edges;
        adjList.insert(p1,edges);
        adjList[p1].insert(p2,c);
    }
    addEdge(p2,p1,c);
    return true;
}


Graph::Connection Graph::findConnection(SoccerPlayer& p1, SoccerPlayer& p2) {
    if(p1 == p2) return none;
    map<int,string> tt1 = p1.getTeamTime();
    map<int,string> tt2 = p2.getTeamTime();
    map<int,string>::iterator it1 = tt1.begin();
    map<int,string>::iterator it2 = tt2.begin();
    while(it1 != tt1.end() && it1->first < it2->first) {
        it1++;
    }
    while(it2 != tt2.end() && it2->first < it1->first) {
        it2++;
    }
    while(it1 != tt1.end() && it2 != tt2.end() && it1->first == it2->first) {
        if(it1->second == it2->second) {
            return teamTime;
        }
    }
    if(p1.getHeight() == p2.getHeight()) {
        return height;
    }
    if(p1.getJerseyNum() == p2.getJerseyNum()) {
        return jerseyNum;
    }
    if(p1.getGoals()==p2.getGoals()) {
        return goals;
    }
    if(p1.getNationality()==p2.getNationality()) {
        return nationality;
    }
    if(p1.getRedCards() == p2.getRedCards()) {
        return redCards;
    }
    if(p1.getYellowCards() == p2.getYellowCards()) {
        return yellowCards;
    }
    if(p1.getMaxGoals()>=3 && p2.getMaxGoals()>=3) {
        return maxGoals;
    }
    if(p1.getYearBorn() == p2.getYearBorn()) {
        return yearBorn;
    }
    return none;
}


Graph::Connection Graph::findConnection(BasketballPlayer& p1, BasketballPlayer& p2) {
    if(p1 == p2) return none;
    map<int,string> tt1 = p1.getTeamTime();
    map<int,string> tt2 = p2.getTeamTime();
    map<int,string>::iterator it1 = tt1.begin();
    map<int,string>::iterator it2 = tt2.begin();
    while(it1 != tt1.end() && it1->first < it2->first) {
        it1++;
    }
    while(it2 != tt2.end() && it2->first < it1->first) {
        it2++;
    }
    while(it1 != tt1.end() && it2 != tt2.end() && it1->first == it2->first) {
        if(it1->second == it2->second) {
            return teamTime;
        }
    }
    if(p1.getHeight() == p2.getHeight()) {
        return height;
    }
    if(p1.getJerseyNum() == p2.getJerseyNum()) {
        return jerseyNum;
    }
    if(p1.getPoints() == p2.getPoints()) {
        return points;
    }
    if(p1.getRebounds() == p2.getRebounds()) {
        return rebounds;
    }
    if(p1.getAssists()==p2.getAssists()) {
        return assists;
    }
    if(p1.getGamesPlayed() == p2.getGamesPlayed()) {
        return gamesPlayed;
    }
    if(p1.getDraftYear()==p2.getDraftYear()) {
        return draftYear;
    }
    if(p1.getYearBorn() == p2.getYearBorn()) {
        return yearBorn;
    }
    if(p1.getCollege() == p2.getCollege()) {
        return college;
    }
    return none;
}

//TODO: write the bodies for these algorithms
int Graph::shortestPathBFS(Player src, Player dest) {

    return -1;
}

int Graph::shortestPathDFS(Player src, Player dest) {

    return -1;
}