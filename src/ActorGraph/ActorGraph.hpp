#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph
    class Node {
        // Node class, store actor/actress name and movie list
      public:
        // Actor/actress name
        string name;
        // <Actor/actress node, movie title>
        unordered_map<Node*, string> nodes;

        /* Variables for BFS */
        // Parent node for BFS
        Node* parent;
        // The movie which worked together with parent
        string parent_movie;

        Node(const string& str) : name(str), parent(nullptr){};
    };

  private:
    // Connection between actor/actress
    // < actor/actress name, actor/actress node>
    unordered_map<string, Node*> actors;

  public:
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraph(istream& is);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
