

#include "Graph.h"

//TODO: Change this to undordered set by adding hash function for player
#include <queue>
#include <set>
#include <stack>

Graph::Graph()= default;

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
        map<Player,Connection> edges;
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
vector<pair<Player,Graph::Connection>> Graph::shortestPathBFS(Player& src, Player& dest) {
    queue<vector<pair<Player,Connection>>> q;
    set<Player> visited;
    q.push({pair<Player,Connection>(src,none)});
    visited.insert(src);
    while(!q.empty()) {
        auto path = q.front();
        q.pop();
        if(path[path.size()-1].first == dest) {
            return path;
        }
        for(pair<Player,Connection> couple : adjList[path[path.size()-1].first]) {
            if(visited.find(couple.first) == visited.end()) {
                vector<pair<Player,Connection>> newPath = vector<pair<Player,Connection>>(path);
                newPath.push_back(couple);
                q.push(newPath);
                visited.insert(couple.first);
            }
        }
    }
    return {};
}

vector<pair<Player,Graph::Connection>> Graph::shortestPathDijkstra(Player& src, Player& dest) {
    map<Player,pair<int,pair<Player,Connection>>> distances;
    for(auto p : adjList) {
        distances[p.first] = pair<int,pair<Player,Connection>>(INT_MAX,pair<Player,Connection>(Player(),none));
    }
    distances[src].first = 0;
    priority_queue<pair<int,Player>, vector<pair<int,Player>>, greater<pair<int,Player>>> pq;
    pq.emplace(0,src);
    while(!pq.empty()) {
        auto dist = pq.top();
        pq.pop();
        if(dist.second == dest) {
            break;
        }
        for(auto couple: adjList[dist.second]) {
            if(distances[dist.second].first+1 < distances[couple.first].first) {
                distances[couple.first].first = distances[dist.second].first+1;
                distances[couple.first].second.first = dist.second;
                distances[couple.first].second.second = couple.second;
                pq.emplace(distances[couple.first].first,couple.first);
            }
        }
    }
    vector<pair<Player,Connection>> path;
    pair<Player,Connection> node = distances[dest].second;
    while(!(node.first == src)) {
        path.insert(path.begin(),{node.first,node.second});
        node = distances[node.first].second;
    }
    path.insert(path.begin(),{node.first,node.second});
    return path;
}