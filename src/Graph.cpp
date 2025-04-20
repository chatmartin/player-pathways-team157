

#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>

Graph::Graph() : adjList(unordered_map<Player,unordered_map<Player,Connection>>(1000)) {}

bool Graph::addEdge(Player& p1, Player& p2, Connection c) {
    if(c == none) {
        return false;
    }
    if(adjList.find(p1)!=adjList.end()) {
        if(adjList[p1].find(p2)!=adjList[p1].end()) {
            return false;
        }
        adjList[p1][p2]=c;
    }
    else {
        unordered_map<Player,Connection> edges = unordered_map<Player,Connection>(100);
        adjList[p1] = edges;
        adjList[p1][p2] = c;
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
        ++it1;
    }
    while(it2 != tt2.end() && it2->first < it1->first) {
        ++it2;
    }
    while(it1 != tt1.end() && it2 != tt2.end() && it1->first == it2->first) {
        if(it1->second == it2->second && it1->second != "") {
            return teamTime;
        }
        ++it1;
        ++it2;
    }
    if(p1.getGoals()==p2.getGoals()) {
        return goals;
    }
    if(p1.getNationality()==p2.getNationality()) {
        return nationality;
    }
    if(p1.getYellowCards() == p2.getYellowCards()) {
        return yellowCards;
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
        ++it1;
    }
    while(it1 != tt1.end() && it2 != tt2.end() && it2->first < it1->first) {
        ++it2;
    }
    while(it1 != tt1.end() && it2 != tt2.end() && it1->first == it2->first) {
        if(it1->second == it2->second) {
            return teamTime;
        }
        ++it1;
        ++it2;
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
    return none;
}

vector<pair<Player,Graph::Connection>> Graph::shortestPathBFS(Player& src, Player& dest) {
    queue<pair<Player,Connection>> q;
    unordered_map<Player,pair<Player,Connection>> prevs = unordered_map<Player,pair<Player,Connection>>(1000);
    q.emplace(src,none);
    prevs[src] = q.front();
    Connection last = none;
    while(!q.empty()) {
        auto player = q.front();
        q.pop();
        if(player.first == dest) {
            last = player.second;
            break;
        }
        for(pair<Player,Connection> couple : adjList[player.first]) {
            if(prevs.find(couple.first) == prevs.end()) {
                q.push(couple);
                prevs[couple.first] = player;
            }
        }
    }
    if(prevs.find(dest)==prevs.end()) {
        return {};
    }
    vector<pair<Player,Connection>> shortestPath;
    shortestPath.emplace_back(dest,last);
    pair<Player,Connection> node = prevs[dest];
    while(node.first != src) {
        shortestPath.push_back(node);
        node = prevs[node.first];
    }
    shortestPath.push_back(node);
    reverse(shortestPath.begin(),shortestPath.end());
    return shortestPath;
}

vector<pair<Player,Graph::Connection>> Graph::shortestPathDijkstra(Player& src, Player& dest) {
    unordered_map<Player,pair<int,pair<Player,Connection>>> paths = unordered_map<Player,pair<int,pair<Player,Connection>>>(1000);
    for(auto p : adjList) {
        paths[p.first] = pair<int,pair<Player,Connection>>(INT_MAX,pair<Player,Connection>(Player(),none));
    }
    paths[src].first = 0;
    priority_queue<pair<int,Player>, vector<pair<int,Player>>, greater<pair<int,Player>>> pq;
    pq.emplace(0,src);
    Connection last = none;
    while(!pq.empty()) {
        auto dist = pq.top();
        pq.pop();
        if(dist.second == dest) {
            break;
        }
        for(auto couple: adjList[dist.second]) {
            if(paths[dist.second].first+1 < paths[couple.first].first) {
                paths[couple.first].first = paths[dist.second].first+1;
                paths[couple.first].second.first = dist.second;
                paths[couple.first].second.second = couple.second;
                pq.emplace(paths[couple.first].first,couple.first);
            }
        }
    }
    if(paths[dest].first == INT_MAX) {
        return {};
    }
    vector<pair<Player,Connection>> shortestPath;
    shortestPath.emplace_back(dest,last);
    pair<Player,Connection> node = paths[dest].second;
    while(node.first != src) {
        shortestPath.push_back(node);
        node = paths[node.first].second;
    }
    shortestPath.push_back(node);
    reverse(shortestPath.begin(),shortestPath.end());
    return shortestPath;
}

vector<Player> Graph::checkConnectivity(const Player &src) {
    unordered_set<Player> visited;
    queue<Player> q;
    q.push(src);
    visited.insert(src);
    while(!q.empty()) {
        Player curr = q.front();
        q.pop();
        for(auto couple: adjList[curr]) {
            if(visited.find(couple.first) == visited.end()) {
                q.push(couple.first);
                visited.insert(couple.first);
            }
        }
    }
    vector<Player> v;
    for(auto p: adjList) {
        if(visited.find(p.first)==visited.end()) {
            v.push_back(p.first);
        }
    }
    return v;
}

unordered_map<Player,unordered_map<Player,Graph::Connection>>& Graph::getAdjList() {
    return adjList;
}