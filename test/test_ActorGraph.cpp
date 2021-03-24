#include <gtest/gtest.h>

#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

TEST(ActorGraphTests, TwoActorsOneMovie) {
    string from = "Actor 1";
    string to = "Actor 2";
    string through = "Awesome Movie\t2020";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << from << "\t" << through << endl;
    ss << to << "\t" << through << endl;

    ActorGraph graph;
    bool isBuilt = graph.buildGraph(ss);
    ASSERT_TRUE(isBuilt);
}

// TODO: add more tests for actor graph
TEST(ActorGraphBFSTests1, TwoActorsOneMovie) {
    string from = "Actor 1";
    string to = "Actor 2";
    string through = "Awesome Movie\t2020";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << from << "\t" << through << endl;
    ss << to << "\t" << through << endl;

    ActorGraph graph;
    graph.buildGraph(ss);
    string ans = "(Actor 1)--[Awesome Movie#@2020]-->(Actor 2)";
    string bfs;
    graph.BFS(from, to, bfs);
    ASSERT_EQ(ans, bfs);
}

TEST(ActorGraphBFSTests2, ThreeActorsOneMovie) {
    string from = "Actor 1";
    string to = "Actor 3";

    string through = "Awesome Movie\t2020";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << from << "\t" << through << endl;
    ss << "Actor 2\t" << through << endl;
    ss << to << "\t" << through << endl;

    ActorGraph graph;
    graph.buildGraph(ss);
    string ans = "(Actor 1)--[Awesome Movie#@2020]-->(Actor 3)";
    string bfs;
    graph.BFS(from, to, bfs);
    ASSERT_EQ(ans, bfs);
}

TEST(ActorGraphBFSTests2, SmallActorGraph) {
    string from = "Samuel L. Jackson";
    string to = "Tom Holland";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << "Kevin Bacon\tX-Men: First Class\t2011" << endl;
    ss << "James McAvoy\tX-Men: First Class\t2011" << endl;
    ss << "James McAvoy\tX-Men: Apocalypse\t2016" << endl;
    ss << "James McAvoy\tGlass\t2019" << endl;
    ss << "Michael Fassbender\tX-Men: First Class\t2011" << endl;
    ss << "Michael Fassbender\tX-Men: Apocalypse\t2016" << endl;
    ss << "Michael Fassbender\tAlien: Covenant\t2017" << endl;
    ss << "Samuel L. Jackson\tGlass\t2019" << endl;
    ss << "Samuel L. Jackson\tAvengers: Endgame\t2019" << endl;
    ss << "Robert Downey Jr.\tAvengers: Endgame\t2019" << endl;
    ss << "Robert Downey Jr.\tSpider-Man: Homecoming\t2017" << endl;
    ss << "Tom Holland\tAvengers: Endgame\t2019" << endl;
    ss << "Tom Holland\tSpider-Man: Homecoming\t2017" << endl;
    ss << "Tom Holland\tThe Current War\t2017" << endl;
    ss << "Katherine Waterston\tAlien: Covenant\t2017" << endl;
    ss << "Katherine Waterston\tThe Current War\t2017" << endl;

    ActorGraph graph;
    graph.buildGraph(ss);
    string ans =
        "(Samuel L. Jackson)--[Avengers: Endgame#@2019]-->(Tom Holland)";
    string bfs;
    graph.BFS(from, to, bfs);
    ASSERT_EQ(ans, bfs);
}