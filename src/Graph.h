
#ifndef GRAPH_H
#define GRAPH_H

#include "HashMap.h"
#include "SoccerPlayer.h"
#include "BasketballPlayer.h"
using namespace std;
class Graph {
private:
    enum Connection {none, height, yearBorn, jerseyNum, teamTime, goals, yellowCards, redCards, maxGoals, nationality, points, college, draftYear, rebounds, gamesPlayed, assists};
    //TODO: Change this to a hash map by adding a hash function for Player
    map<Player,map<Player,Connection>> adjList;
public:
    Graph();
    Connection findConnection(SoccerPlayer& p1, SoccerPlayer& p2);
    Connection findConnection(BasketballPlayer& p1, BasketballPlayer& p2);
    bool addEdge(Player& p1, Player& p2, Connection c);
    //TODO: Write the BFS and DFS algorithms for shortest path
    vector<pair<Player,Connection>> shortestPathBFS(Player& src, Player& dest);
    vector<pair<Player,Connection>> shortestPathDFS(Player& src, Player& dest);
};



#endif //GRAPH_H
