
#ifndef GRAPH_H
#define GRAPH_H

#include "SoccerPlayer.h"
#include "BasketballPlayer.h"
#include <vector>
using namespace std;
class Graph {
public:
    Graph();
    enum Connection {none, teamTime, goals, yellowCards, nationality, points, rebounds, gamesPlayed, assists}; //this is for knowing what connects two players, which will be used in the output
    static Connection findConnection(SoccerPlayer& p1, SoccerPlayer& p2);
    static Connection findConnection(BasketballPlayer& p1, BasketballPlayer& p2);//finds what connects two players with some priority to specific connection types
    bool addEdge(Player& p1, Player& p2, Connection c); //adds an edge between two players with a given connection
    vector<pair<Player,Connection>> shortestPathBFS(Player& src, Player& dest); //finds the shortest path between two players using BFS
    vector<pair<Player,Connection>> shortestPathDijkstra(Player& src, Player& dest); //finds the shortest path between two players using Dijkstra's
    vector<Player> checkConnectivity(const Player& src); //checks if a graph is connected, returns a vector of the non-connected vertices
    unordered_map<Player,unordered_map<Player,Connection>>& getAdjList();
private:
    unordered_map<Player,unordered_map<Player,Connection>> adjList; //an adjacency list of players, first component is a player, second is a map with adjacent players and the thing that connects them
};



#endif //GRAPH_H
