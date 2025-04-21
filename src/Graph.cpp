

#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>

Graph::Graph() : adjList(unordered_map<Player,unordered_map<Player,Connection>>(1000)) {}

bool Graph::addEdge(Player& p1, Player& p2, Connection c) {
    if(c == none) { //if there is no connection, do not add an edge
        return false;
    }
    if(adjList.find(p1)!=adjList.end()) {
        if(adjList[p1].find(p2)!=adjList[p1].end()) {
            return false; //if both vertices are already connected, do not add an edge
        }
        adjList[p1][p2]=c;
    }
    else { //if vertex does not have any edges yet, we need to add the adjacency list
        unordered_map<Player,Connection> edges = unordered_map<Player,Connection>(100);
        adjList[p1] = edges;
        adjList[p1][p2] = c;
    }
    addEdge(p2,p1,c); //since this is an undirected graph, add the edge going the other way too
    return true;
}


Graph::Connection Graph::findConnection(SoccerPlayer& p1, SoccerPlayer& p2) { //checks for connectoins between players
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

Graph::Connection Graph::findConnection(BasketballPlayer& p1, BasketballPlayer& p2) { //checks for connections between players
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

vector<pair<Player,Graph::Connection>> Graph::shortestPathBFS(const Player& src, const Player& dest) {
    queue<pair<Player,Connection>> q; //queue necessary for BFS
    unordered_map<Player,pair<Player,Connection>> prevs = unordered_map<Player,pair<Player,Connection>>(1000); //contains previous nodes, used for finding the overall path
    q.emplace(src,none);
    prevs[src] = q.front();
    Connection last = none; //this variable will be used to hold the connection leading to the last node
    while(!q.empty()) { //mostly standard BFS algorithm
        auto player = q.front();
        q.pop();
        if(player.first == dest) {
            last = player.second;
            break;
        }
        for(pair<Player,Connection> couple : adjList[player.first]) {
            if(prevs.find(couple.first) == prevs.end()) {
                q.push(couple);
                prevs[couple.first] = player; //mark the previous vertex leading to a given node
            }
        }
    }
    if(prevs.find(dest)==prevs.end()) { //if dest was never reached it will not be in prevs
        return {};
    }
    vector<pair<Player,Connection>> shortestPath; //vector we will return
    shortestPath.emplace_back(dest,last);
    pair<Player,Connection> node = prevs[dest];
    while(node.first != src) { //works our way backwards from src to dest
        shortestPath.push_back(node);
        node = prevs[node.first];
    }
    shortestPath.push_back(node); //this is src
    reverse(shortestPath.begin(),shortestPath.end()); //reverse so starts at src and ends at dest
    return shortestPath;
}

vector<pair<Player,Graph::Connection>> Graph::shortestPathDijkstra(const Player& src, const Player& dest) {
    unordered_map<Player,pair<int,pair<Player,Connection>>> paths = unordered_map<Player,pair<int,pair<Player,Connection>>>(1000); //key is a player, for every player the important values are an int (d[v]), a player (p[v]) and the connection between this node and p[v]
    for(auto p : adjList) {
        paths[p.first] = pair<int,pair<Player,Connection>>(INT_MAX,pair<Player,Connection>(Player(),none)); //initializing every path as INT_MAX to allow for eventual relaxing
    }
    paths[src].first = 0; //d[v] for src is 0
    priority_queue<pair<int,Player>, vector<pair<int,Player>>, greater<pair<int,Player>>> pq; //priority queue necessary for Dijkstra's
    pq.emplace(0,src);
    Connection last = none; //this is the dummy connection used for the last node in our path
    while(!pq.empty()) {
        auto dist = pq.top(); //Dijkstra's always goes to the shortest leftover path, which is at pq.top()
        pq.pop();
        if(dist.second == dest) {
            break; //end the loop early once we hit dest since that is the point of this algorithm
        }
        for(auto couple: adjList[dist.second]) {
            if(paths[dist.second].first+1 < paths[couple.first].first) { //relax the path if it's shorter
                paths[couple.first].first = paths[dist.second].first+1;
                paths[couple.first].second.first = dist.second;
                paths[couple.first].second.second = couple.second;
                pq.emplace(paths[couple.first].first,couple.first);
            }
        }
    }
    if(paths[dest].first == INT_MAX) { //if we never got to dest, then d[v] is INT_MAX
        return {};
    }
    vector<pair<Player,Connection>> shortestPath; //this is the vector containing the string of connections
    shortestPath.emplace_back(dest,last);
    pair<Player,Connection> node = paths[dest].second;
    while(node.first != src) { //this works our way backwards from dest to src
        shortestPath.push_back(node);
        node = paths[node.first].second;
    }
    shortestPath.push_back(node); //this is src
    reverse(shortestPath.begin(),shortestPath.end()); //reverse so starts at src and ends at dest
    return shortestPath;
}
//standard BFS algorithm to check if a graph is connected
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
    vector<Player> v; //this is the vector we will return
    for(auto p: adjList) {
        if(visited.find(p.first)==visited.end()) { //if a vertex is in the adjList but not a visited node, add it to the vector
            v.push_back(p.first);
        }
    }
    return v;
}

unordered_map<Player,unordered_map<Player,Graph::Connection>>& Graph::getAdjList() {
    return adjList;
}

json Graph::toJson() {
    json j;
    for(auto p: adjList) {
        for(auto couple: p.second) {
            j["edges"].push_back({
                {"source", p.first.getName()},
                {"adjacent",couple.first.getName()},
                {"connection",couple.second}
            });
        }
    }
    return j;
}