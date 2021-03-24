#include "ActorGraph.hpp"

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraph(istream& is) {
    bool readHeader = false;

    // Actor/actress that starred in the movie
    // < movie_title + year, actor/actress set>
    unordered_map<string, set<string>> movies;

    while (is) {
        string s;
        if (!getline(is, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship to build the graph
        // Create actor/actress node and insert into actor map
        if (actors.find(actor) == actors.end()) {
            Node* nd = new Node(actor);
            actors.emplace(actor, nd);
        }

        // Insert starring actor into movie
        string title_year = title + "#@" + record[2];
        auto movie = movies.find(title_year);
        // If movie does not exist, create actor set and insert into movies map
        if (movie == movies.end()) {
            set<string> s;
            s.insert(actor);
            movies.emplace(title_year, s);
        }
        // Found, inset actor/actress into string set
        else {
            movie->second.insert(actor);
        }
    }

    // if failed to read the file, clear the graph and return
    if (!is.eof()) {
        // TODO: delete the graph
        for (auto curr : actors) {
            delete curr.second;
        }
        actors.clear();
        return false;
    }

    // Search and create edges
    for (auto movie : movies) {
        for (set<string>::iterator it1 = movie.second.begin();
             it1 != movie.second.end(); ++it1) {
            for (set<string>::iterator it2 = next(it1);
                 it2 != movie.second.end(); ++it2) {
                actors[*it1]->nodes.emplace(actors[*it2], movie.first);
                actors[*it2]->nodes.emplace(actors[*it1], movie.first);
            }
        }
    }
    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    queue<string> waitlist;
    set<string> visit;
    waitlist.emplace(fromActor);
    visit.emplace(fromActor);

    // Breadth Fisrt Search for path
    bool reached = false;
    while (!waitlist.empty()) {
        string curr_act = waitlist.front();
        waitlist.pop();
        Node* curr = actors[curr_act];
        for (auto path : curr->nodes) {
            if (visit.find(path.first->name) != visit.end()) {
                continue;
            }
            waitlist.emplace(path.first->name);
            visit.emplace(path.first->name);
            path.first->parent = curr;
            path.first->parent_movie = path.second;
            if (path.first->name == toActor) {
                reached = true;
                break;
            }
        }
        if (reached == true) {
            break;
        }
    }

    // Retrieve path and create output string
    if (reached == true) {
        string shortpath = "(" + toActor + ")";
        Node* curr = actors[toActor];
        while (curr->parent != nullptr) {
            Node* parent = curr->parent;
            shortpath = "(" + parent->name + ")--[" + curr->parent_movie +
                        "]-->" + shortpath;
            curr = parent;
        }
        shortestPath = shortpath;
    }

    // Reset length and parent for next search
    for (auto curr : actors) {
        curr.second->parent = nullptr;
        curr.second->parent_movie = "";
    }
}

/* TODO */
ActorGraph::~ActorGraph() {
    for (auto curr : actors) {
        delete curr.second;
    }
    actors.clear();
}