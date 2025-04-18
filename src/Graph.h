
#ifndef GRAPH_H
#define GRAPH_H

#include "HashMap.h"
#include "SoccerPlayer.h"
#include "BasketballPlayer.h"
using namespace std;
class Graph {
private:
    enum Connection {none, height, yearBorn, jerseyNum, teamTime, goals, yellowCards, redCards, maxGoals, nationality, points, college, draftYear, rebounds, gamesPlayed, assists};
    HashMap<HashMap<Connection>> adjList;
public:
    Graph();
    Connection findConnection(SoccerPlayer& p1, SoccerPlayer& p2);
    Connection findConnection(BasketballPlayer& p1, BasketballPlayer& p2);
    bool addEdge(Player& p1, Player& p2, Connection c);
    //TODO: Write the BFS and DFS algorithms for shortest path
    int shortestPathBFS(Player src, Player dest);
    int shortestPathDFS(Player src, Player dest);
};



#endif //GRAPH_H
