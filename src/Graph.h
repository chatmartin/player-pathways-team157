
#ifndef GRAPH_H
#define GRAPH_H

#include "SoccerPlayer.h"
#include "BasketballPlayer.h"
#include <vector>
using namespace std;
class Graph {
public:
    Graph();
    enum Connection {none, height, yearBorn, teamTime, goals, yellowCards, maxGoals, nationality, points, college, draftYear, rebounds, gamesPlayed, assists, weight};
    static Connection findConnection(SoccerPlayer& p1, SoccerPlayer& p2);
    Connection findConnection(BasketballPlayer& p1, BasketballPlayer& p2);
    bool addEdge(Player& p1, Player& p2, Connection c);
    vector<pair<Player,Connection>> shortestPathBFS(Player& src, Player& dest);
    vector<pair<Player,Connection>> shortestPathDijkstra(Player& src, Player& dest);
    bool checkConnectivity(Player& src);
private:
    unordered_map<Player,unordered_map<Player,Connection>> adjList;
};



#endif //GRAPH_H
