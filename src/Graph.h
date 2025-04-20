
#ifndef GRAPH_H
#define GRAPH_H

#include "SoccerPlayer.h"
#include "BasketballPlayer.h"
#include <vector>
using namespace std;
class Graph {
public:
    Graph();
    enum Connection {none, teamTime, goals, yellowCards, hatTrick, nationality, points, rebounds, gamesPlayed, assists};
    static Connection findConnection(SoccerPlayer& p1, SoccerPlayer& p2);
    static Connection findConnection(BasketballPlayer& p1, BasketballPlayer& p2);
    bool addEdge(Player& p1, Player& p2, Connection c);
    vector<pair<Player,Connection>> shortestPathBFS(Player& src, Player& dest);
    vector<pair<Player,Connection>> shortestPathDijkstra(Player& src, Player& dest);
    vector<Player> checkConnectivity(const Player& src);
    unordered_map<Player,unordered_map<Player,Connection>>& getAdjList();
private:
    unordered_map<Player,unordered_map<Player,Connection>> adjList;
};



#endif //GRAPH_H
