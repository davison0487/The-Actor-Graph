#  The Actor Graph
"Six Degrees of Kevin Bacon" is a parlor game based on the "six degrees of separation" concept, which proposes that any two people on Earth are six or fewer acquaintance-links apart. This idea eventually morphed into a parlor game where movie buffs challenge each other to find the shortest path between some arbitrary actors and Hollywood actor Kevin Bacon. It rests on the assumption that anyone involved in the Hollywood film industry can be linked through their film roles to Bacon in six or fewer steps. The game requires a group of players to try to connect any such individual to Kevin Bacon as quickly and in as few links as possible. In this project, will implement a generalized version of the Kevin Bacon game.

- Design and build the actor graph.
- Implement functions in ActorGraph.cpp so that the compiled pathfinder.cpp can output the shortest unweighted path between two given actors.

## Design and Build the Actor Graph 

The actor graph is defined as an undirected graph: each unique actor represents a single vertex, and two vertices (actors) are connected by an undirected edge if these two actors have worked in the same movie. Multiple undirected edges can exist between the two actor vertices, which means these two actors worked in multiple movies before.
For example, for the small dataset given as follows:
 
Actor/Actress (TAB) Movie (TAB) Year
Orlando Bloom (TAB) Pirates of the Caribbean (TAB) 2003
    
Orlando Bloom (TAB) Pirates of the Caribbean (TAB) 2006
    
Keira Knightley (TAB) Pirates of the Caribbean (TAB) 2003
    
Keira Knightley (TAB) Pirates of the Caribbean (TAB) 2006
    
Keira Knightley (TAB) Atonement (TAB) 2007
    
James McAvoy (TAB) Atonement (TAB)2007
 

The corresponding actor graph should look like the following (note again that if two movies have the same title, they can still be different movies if their year is different) :
 
![image](https://github.com/davison0487/The-Actor-Graph/blob/main/images/graph.png)


## Unweighted Shortest Path in Actor Graph

In this part, we will implement a pathfinder program that outputs the unweighted shortest path between a given pair of actors in the actor graph. After compiling, the command below will run the program:
 
`./build/src/pathfinder.exe data/pathfinder1_graph.tsv data/pathfinder1_pairs.tsv data/unweighted_paths.tsv`
 
- data/pathfinder1_graph.tsv: the dataset that defines the graph use imdb_2019.tsv in this position to run with the complete dataset

- pathfinder1_pairs.tsv: each line has a pair of actors for which the shortest path will be found

- unweighted_paths.tsv: the shortest path between the corresponding pair of actors will be output on each line
 
Example of pathfinder1_pairs.tsv: 

- Actor1/Actress1 (TAB) Actor2/Actress2
    
- Robert Downey Jr. (TAB) Chris Evans

- Amy Adams (TAB) Nicole Kidman

 
Example of unweighted_paths.tsv:
- (actor)--[movie#@year]-->(actor)--...

- (Robert Downey Jr.)--[Avengers: Age of Ultron#@2015]-->(Chris Evans)

- (Amy Adams)--[Leap Year#@2010]-->(Matthew Goode)--[Stoker#@2013]-->(Nicole Kidman)

 
In this part, we implemented the BFS() function that pathfinder.cpp calls in the ActorGraph class. Given a pair of different actor names, this function will find the unweighted shortest path from fromActor to toActor in the actor graph using BFS. 
