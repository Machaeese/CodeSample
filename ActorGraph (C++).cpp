
/** File name: ActorGraph.cpp
 * This file contains the class of ActorGraph, which builds the graph consists
 * of actor nodes as veterx and movies as edges.
 * Author: Xinyi Qi; Jialu Xu
 * E-mail: xiq017@ucsd.edu; jix211@ucsd.edu
 * Date: 2019/12/03
 * References: Thanks the tutors for their help.
 */

#include "ActorGraph.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"

using namespace std;

#define TWO 2
#define THREE 3
#define FOUR 4
#define YEAR 2019

/**
 * Constructor of the ActorGraph
 */
ActorGraph::ActorGraph(void) {
    allActors = new unordered_map<string, ActorNode*>;
    allMovies = new unordered_map<string, MovieNode*>;
}

/**
 * Destructor of the ActorGraph
 */
ActorGraph::~ActorGraph() {
    // iterate through the map of all actors and delete the ActorNode
    for (auto itActor = allActors->begin(); itActor != allActors->end();
         ++itActor) {
        for (auto itEdge = (*itActor).second->edges.begin();
             itEdge != (*itActor).second->edges.end(); ++itEdge) {
            delete *itEdge;
        }
        delete (*itActor).second;
    }
    // iterate through the map of all actors and delete the MovieNode
    for (auto itMovie = allMovies->begin(); itMovie != allMovies->end();
         ++itMovie) {
        delete (*itMovie).second;
    }
    delete allActors;
    delete allMovies;
}

/* Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
 * movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */

/** Function name: addActor(string actor, string movie
 * This function adds all movies or actors played in input movie and actor as
 * ActorNodes or MovieNodes.
 * All ActorNodes are added to the unordered_set of ActorNodes in MovieNode
 * Create new ActorNode is the MovieNode does not have input actor yet
 * If actor already in movie, add movie to current actor
 */
void ActorGraph::addActor(string actor, string movie) {
    // if the actor is a new actor, insert the pair of actor and a ActorNode
    // containing all of his/her movies
    if (allActors->count(actor) == 0) {
        allActors->insert(
            pair<string, ActorNode*>(actor, new ActorNode(actor)));
        allActors->at(actor)->movies.insert(movie);
    }
    // otherwise, find the actor in our map and insert the new movie
    else {
        allActors->at(actor)->movies.insert(movie);
    }
}

/** Function name: addMovie(string actor, string movie, int year)
 * This function adds all movies or actors played in input movie and actor as
 * ActorNodes or MovieNodes.
 * All ActorNodes are added to the unordered_set of ActorNodes in MovieNode
 * Create new ActorNode is the MovieNode does not have input actor yet
 * If actor already in movie, add movie to current actor
 */
void ActorGraph::addMovie(string actor, string movie, int year) {
    // if the movie is a new actor, insert the pair of movie and a MovieNode
    // containing all of its actor/actress
    if (allMovies->count(movie) == 0) {
        allMovies->insert(
            pair<string, MovieNode*>(movie, new MovieNode(movie, year)));
        allMovies->at(movie)->actors.insert(actor);
    }
    // otherwise, find the movie in our map and insert the new
    // actor/actress
    else {
        allMovies->at(movie)->actors.insert(actor);
    }
}

/** Function name: generateGraph()
 * This functuon generates the actor graph after all ActorNodes and  MovieNodes
 * are created and filled.
 */
void ActorGraph::generateGraph() {
    // iterate through the allActors(map) create the node and edge
    for (unordered_map<string, ActorNode*>::iterator it = allActors->begin();
         it != allActors->end(); ++it) {
        // get the actor node
        ActorNode* currActor = it->second;
        // get the set of movies cast by currActor
        unordered_set<string> movieSet = it->second->movies;
        // iterate through the actornode's movies (set) for further actor
        // finding
        for (auto setIt = movieSet.begin(); setIt != movieSet.end(); ++setIt) {
            // get the name of each movie
            string currMovie = *setIt;
            // go to all Movies and find currMovie in allMovies(map) to get
            // actors who played in this movie
            unordered_set<string> relatedActors =
                allMovies->find(currMovie)->second->actors;
            // iterate through the movieNode's actor set and create the
            // edges
            for (auto actorIt = relatedActors.begin();
                 actorIt != relatedActors.end(); ++actorIt) {
                // add the edge if and only if the actor is not the same as
                // currActor
                if (*actorIt != currActor->name) {
                    int weight =
                        YEAR - allMovies->find(currMovie)->second->year + 1;
                    currActor->edges.insert(
                        new Edge(currMovie, weight, currActor,
                                 allActors->find(*actorIt)->second));
                    // if currActor is not inside the set, we add the count by 1
                    if (currActor->common.count(allActors->at(*actorIt)) != 0) {
                        currActor->common.at(allActors->at(*actorIt)) += 1;
                    } else {
                        currActor->common.insert(
                            pair<ActorNode*, int>(allActors->at(*actorIt), 1));
                    }
                }
            }
        }
    }
}

/** Function name: printPath ()
 * This function prints the path representing the link between one actor to the
 * other actor to the output file.
 * All actors listed in the test_file will be used to find links.
 * The bool use_weighted_edges decides whether to use weighted or unweighted
 * path.
 **/
void ActorGraph::printPath(const char* test_file, const char* out_file,
                           bool use_weighted_edges) {
    // open the input file and ouput file
    ifstream tester;
    tester.open(test_file);
    ofstream outputFile;
    outputFile.open(out_file);
    // print out the first fixed line
    outputFile << "(actor)--[movie#@year]-->(actor)--..." << endl;

    bool have_header = false;
    // keep reading lines until the end of file is reached
    while (tester) {
        string s;
        // get the next line
        if (!getline(tester, s)) break;
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string second;
            // get the next string before hitting a tab character and put it
            // in 'str'
            if (!getline(ss, second, '\t')) break;
            record.push_back(second);
        }
        if (record.size() != TWO) {
            // we should have exactly 2 columns
            continue;
        }
        string actor1(record[0]);
        string actor2(record[1]);
        // check if these two actors exist
        if ((allActors->count(actor1) != 0) &&
            (allActors->count(actor2) != 0)) {
            // get the current first two actor nodes
            ActorNode* first = allActors->at(actor1);
            ActorNode* second = allActors->at(actor2);
            if (use_weighted_edges) {
                outputFile << getWeightedPath(first, second) << endl;
            } else {
                outputFile << getUnweightedPath(first, second) << endl;
            }
        }
        // otherwise print out a new empty line
        else {
            outputFile << endl;
        }
    }
    // if there still have some remaining, return
    if (!tester.eof()) {
        cerr << "Failed to read " << test_file << "!\n";
        return;
    }
    // open input and output files
    tester.close();
    outputFile.close();
    return;
}

/** Function name: initializeGraph()
 * Initialize the graph by setting the unordered_set of actor nodes to be
 * nullptrs.
 * Set initial dist for all ActorNodes as infinite
 */
void ActorGraph::initializeGraph() {
    // iterate through the map of actors to reset all the variables
    for (auto itActor = allActors->begin(); itActor != allActors->end();
         ++itActor) {
        itActor->second->dist = INT_MAX;
        itActor->second->prev.first = nullptr;
        itActor->second->prev.second = "";
        itActor->second->done = false;
    }
}

/** Function name: getUnweightedPath()
 * Get the path linking two actors using the movies as edges
 * Do bfs on the the actor graph to look for actor nodes linked by edges of
 * movies.
 */
string ActorGraph::getUnweightedPath(ActorNode* actor1, ActorNode* actor2) {
    string wholePath;
    // if these two actors are the same or either one of them not in the map, or
    // actor1 has no edge, print out a newline
    if (actor1->name == actor2->name || actor1->edges.size() == 0) {
        return "\n";
    }
    // call initializeGraph() to set all variables in nodes as initial
    // values
    initializeGraph();
    // initialize the a queue for using BFS algorithm
    queue<ActorNode*> queue;
    // initialize the source node as the actor1
    ActorNode* start = allActors->at(actor1->name);
    start->dist = 0;
    queue.push(start);
    // while the queue is not empty
    while (!queue.empty()) {
        ActorNode* curr = queue.front();
        queue.pop();
        // if we already meet our goal actor, return
        if (curr->name == actor2->name) {
            break;
        }
        // iterate through the neighbors of the current ActorNode
        for (auto it = curr->edges.begin(); it != curr->edges.end(); ++it) {
            ActorNode* neighbor = (*it)->next;
            // if neighbor's dist is INT_MAX, which means it has not been
            // visited, update the dist and prev
            if (neighbor->dist == INT_MAX) {
                neighbor->dist = curr->dist + 1;
                neighbor->prev.first = curr;
                neighbor->prev.second = (*it)->name;
                queue.push(neighbor);
            }
        }
    }
    // formate the path for actors and movies
    vector<string> path;
    ActorNode* currActor = actor2;
    while (currActor->prev.first != nullptr) {
        path.push_back("(" + currActor->prev.first->name + ")--[" +
                       currActor->prev.second + "]-->");
        currActor = currActor->prev.first;
    }
    for (int i = path.size() - 1; i >= 0; i--) {
        wholePath += path[i];
    }
    wholePath = wholePath + "(" + actor2->name + ")";
    // output the formated path string
    return wholePath;
}

/** Function name: getWeightedPath()
 * Get the path linking two actors using the movies as edges.
 * Use weighted edges, which are decided by how many years apart from the year
 * the movie was produced to 2019.
 * Do ditrajris on the the actor graph to look for actor nodes linked by edges
 * of movies.
 */
string ActorGraph::getWeightedPath(ActorNode* actor1, ActorNode* actor2) {
    string wholePath;
    // if these two actors are the same or either one of them not in the map, or
    // actor1 has no edge, print out a newline
    if (actor1->name == actor2->name || actor1->edges.size() == 0) {
        return "\n";
    }
    // call initializeGraph() to set all variables in nodes as initial
    // values
    initializeGraph();
    linkW q;
    // initialize the source node as the actor1
    ActorNode* start = allActors->at(actor1->name);
    start->dist = 0;
    // push the actor1 and the path cost 0 into the queue
    q.push(pair<ActorNode*, int>(start, 0));

    // while the queue is not empty
    while (!q.empty()) {
        // dequeue the first element in the queue
        pair<ActorNode*, int> curr = q.top();
        q.pop();
        // if we already meet our goal actor, return
        if (curr.first->name.compare(actor2->name) == 0) {
            break;
        }
        // if this node has not been visited, set it as been visited and explore
        // its neighbors
        if (curr.first->done == false) {
            curr.first->done = true;
            // iterate through the neighbors of the current ActorNode
            for (auto it = curr.first->edges.begin();
                 it != curr.first->edges.end(); ++it) {
                ActorNode* neighbor = (*it)->next;
                // calculate the distance to neighbor from curr
                int total = curr.first->dist + (*it)->weight;
                // if the distance is less than neighbors' distance, update the
                // neighbors' distance to be the closer one
                if (total < neighbor->dist) {
                    neighbor->prev.first = curr.first;
                    neighbor->prev.second = (*it)->name;
                    neighbor->dist = total;
                    // push the neighbor back to the queue
                    q.push(pair<ActorNode*, int>(neighbor, total));
                }
            }
        }
    }
    // formate the output string path
    vector<string> path;
    ActorNode* currActor = actor2;
    while (currActor->prev.first != nullptr) {
        path.push_back("(" + currActor->prev.first->name + ")--[" +
                       currActor->prev.second + "]-->");
        currActor = currActor->prev.first;
    }
    for (int i = path.size() - 1; i >= 0; i--) {
        wholePath += path[i];
    }
    wholePath = wholePath + "(" + actor2->name + ")";
    // return the output path string
    return wholePath;
}

/** Function name: findRoot()
 * This function find the root actor node of the actor graph with the
 * given input ActorNode.
 * This function is helper function for path compression in movie traveler
 */
ActorNode* ActorGraph::findRoot(ActorNode* actor) {
    ActorNode* curr = actor;
    // if the input actor has no parent, return
    if (actor->parent == nullptr) return curr;
    vector<ActorNode*> path;
    // loop through the path to find the
    while (curr->parent != nullptr) {
        path.push_back(curr);
        curr = curr->parent;
    }
    // iterate through the path to connect the every node directly to the root
    for (auto actorIt = path.begin(); actorIt != path.end(); ++actorIt) {
        (*actorIt)->parent = curr;
    }
    return curr;
}

/** Function name: combine()
 * This function unions two actor nodes for path compression in movie traveler
 * This function uses the actor node with larger size as the new parent node of
 * the two input actor nodes.
 */
bool ActorGraph::combine(ActorNode* actor1, ActorNode* actor2) {
    // find the root node of two actor nodes to check if they belong to same set
    ActorNode* parent1 = findRoot(actor1);
    ActorNode* parent2 = findRoot(actor2);
    // if parent1 differs from parent2
    if (parent1->name.compare(parent2->name) != 0) {
        // if the set size of parent1 is larger than that of parent2, let
        // parent1 be the parent of parent2 and update the size of parent1
        if (parent1->size > parent2->size) {
            parent2->parent = parent1;
            parent1->size += parent2->size;
        }
        // if the set size of parent2 is larger than that of parent1, let
        // parent2 be the parent of parent1 and update the size of parent2
        else if (parent1->size < parent2->size) {
            parent1->parent = parent2;
            parent2->size += parent1->size;
        }
        // if the set size of parent1 and parent2 are the same, let
        // parent1 be the parent of parent2 and update the size of parent1
        else {
            parent2->parent = parent1;
            parent1->size += parent2->size;
        }
        return true;
    }
    return false;
}

/** Function name: movieTraveler()
 * This function loops through all edges between actors and movies in the actor
 * graph. Then get the pair of actors and moives, push each pair into pripority
 * queue using comparator of weight on edges. Then do path compression on the
 * weighted edges.
 */
void ActorGraph::movieTraveler(const char* output) {
    // Initialize the file stream
    ofstream outputFile;
    outputFile.open(output);
    // print out the first fixed line
    outputFile << "(actor)<--[movie#@year]-->(actor)" << endl;
    linkE q;
    // iterate through all movies and create edges with two actors
    for (auto movieIt = allMovies->begin(); movieIt != allMovies->end();
         ++movieIt) {
        // iterate through all actors in the movie
        for (auto actor1 = (*movieIt).second->actors.begin();
             actor1 != (*movieIt).second->actors.end(); ++actor1) {
            // iterate through all actors in the movie
            for (auto actor2 = actor1;
                 // get pairs and create edges
                 actor2 != (*movieIt).second->actors.end(); ++actor2) {
                if ((*actor1).compare(*actor2) != 0) {
                    Edge* edge = new Edge((*movieIt).first,
                                          YEAR - (*movieIt).second->year + 1,
                                          allActors->find(*actor1)->second,
                                          allActors->find(*actor2)->second);
                    q.push(edge);
                }
            }
        }
    }
    int numEdge = 0;
    int totalWeight = 0;
    // while the queue is empty,
    while (!q.empty()) {
        Edge* e = q.top();
        q.pop();
        // print path if two actors can be unioned
        if (combine(e->prev, e->next)) {
            string path = "(" + e->prev->name + ")<--[" + e->name + "]-->(" +
                          e->next->name + ")";
            outputFile << path << endl;
            // update weight on edge
            totalWeight += e->weight;
            numEdge += 1;
        }
        delete e;
    }
    outputFile << "#NODE CONNECTED: " << allActors->size() << endl;
    outputFile << "#EDGE CHOSEN: " << numEdge << endl;
    outputFile << "TOTAL EDGE WEIGHTS: " << totalWeight << endl;

    // close the output files
    outputFile.close();
    return;
}

/** Function name: loadFromFile
 * This function opens and reads the input file, parse the string actor name,
 * string movie title, and int year from each line of the input file.
 */
bool ActorGraph::loadFromFile(const char* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
        // get the next line
        if (!getline(infile, s)) break;
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }
        if (record.size() != THREE) {
            // we should have exactly 3 columns
            continue;
        }
        // parse actor, movie, year from each line of input file
        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[TWO]);
        // concate movie title with movie year
        string movie = movie_title + "#@" + to_string(year);
        // add actor and add movie to actor graph
        addActor(actor, movie);
        addMovie(actor, movie, year);
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    generateGraph();
    infile.close();
    return true;
}

/****   LINK PREDICTOR ****/

/** Function name: levelOne()
 * This function returns all direct neighbours of input actor in the actor graph
 * in an unordered_set of ActorNodes
 */
unordered_set<ActorNode*> ActorGraph::levelOne(string queryActor) {
    unordered_set<ActorNode*> levelone;
    // check if the queryActor is inside the actor map
    if (allActors->count(queryActor) == 0) return levelone;
    // first find the queryActor in the map
    ActorNode* actorNode = allActors->at(queryActor);
    // iterate through the edges of the given actor and collect all its
    // direct neighbors
    for (auto itEdge = actorNode->edges.begin();
         itEdge != actorNode->edges.end(); ++itEdge) {
        levelone.insert((*itEdge)->next);
    }
    return levelone;
}

/** Function name: levelTwo ()
 * This function returns all neighbours of the direct neighbours collected by
 * levelOne().
 * All neighbours should update the same unordered_set of ActorNodes created by
 * levelOne()
 */
unordered_set<ActorNode*> ActorGraph::levelTwo(
    unordered_set<ActorNode*> levelone, string queryActor) {
    unordered_set<ActorNode*> leveltwo;
    // check if first level is empty or not
    if (levelone.size() == 0) return leveltwo;
    // iterate through the actornoes inside the firstSet to explore
    // their neighbors
    for (auto neighbor = levelone.begin(); neighbor != levelone.end();
         ++neighbor) {
        // iterate through the edges of the actor and collect all its
        // direct neighbors that is not in the given set firstSet
        for (auto itEdge = (*neighbor)->edges.begin();
             itEdge != (*neighbor)->edges.end(); ++itEdge) {
            // if the neighbor is not inside the direct neighbor set, add it
            // to the secondNeighbor
            if (levelone.count((*itEdge)->next) == 0 &&
                ((*itEdge)->next->name).compare(queryActor) != 0) {
                leveltwo.insert((*itEdge)->next);
            }
        }
    }
    return leveltwo;
}

/** Function name: colActors9)
 * This function put all collorated actors of input actor into a pripority
 * queue. The pripority queue uses comparator for pripority of each actor or
 * ascii value of actor name
 */
linkQ ActorGraph::colActors(unordered_set<ActorNode*> levelone,
                            string queryActor) {
    linkQ q;
    // iterate through the the levelone set, find all its neighbors
    for (auto firstNe = levelone.begin(); firstNe != levelone.end();
         ++firstNe) {
        unordered_set<ActorNode*> neighbors = levelOne((*firstNe)->name);
        // get rid of the queryActor
        neighbors.erase(allActors->at(queryActor));
        // find common ActorNode
        for (auto upper = neighbors.begin(); upper != neighbors.end();
             ++upper) {
            if (levelone.count(*upper) != 0) {
                (*firstNe)->priority +=
                    (*upper)->common.at(allActors->at(queryActor)) *
                    (*upper)->common.at(*firstNe);
            }
        }
        q.push((*firstNe));
    }
    return q;
}

/** Function name: uncolActors ()
 * This function update the pripority queue with actors that may be collobrated
 * in the future to the same queue for actors who had already collobrated with
 * the input actor.
 */
linkQ ActorGraph::uncolActors(unordered_set<ActorNode*> levelone,
                              unordered_set<ActorNode*> leveltwo,
                              string queryActor) {
    linkQ q;
    // iterate through the the levelone set, find all its neighbors
    for (auto secondNe = leveltwo.begin(); secondNe != leveltwo.end();
         ++secondNe) {
        unordered_set<ActorNode*> neigbors = levelOne((*secondNe)->name);
        // check if level two's neighbor has any common neigbors with level
        // one
        for (auto below = neigbors.begin(); below != neigbors.end(); ++below) {
            if (levelone.count(*below) != 0) {
                (*secondNe)->priority +=
                    (*below)->common.at(allActors->at(queryActor)) *
                    (*below)->common.at(*secondNe);
            }
        }
        q.push((*secondNe));
    }
    return q;
}

/** Function name: resetPripority ()
 * This function reset pripority for all actor nodes with 0
 */
void ActorGraph::resetPriority() {
    for (auto itAct = allActors->begin(); itAct != allActors->end(); itAct++) {
        (*itAct).second->priority = 0;
    }
}

/** Function name: prediction ()
 * This function predicts actors listed in the input test file for list of
 * actors they had collorated before and  may collobrate in the future
 */
void ActorGraph::prediction(const char* test, const char* col_file,
                            const char* uncol_file) {
    // open the input file and ouput file
    ifstream tester;
    tester.open(test);
    ofstream colFile;
    ofstream uncolFile;
    colFile.open(col_file);
    uncolFile.open(uncol_file);

    // print out the first fixed line
    colFile << "Actor1,Actor2,Actor3,Actor4" << endl;
    uncolFile << "Actor1,Actor2,Actor3,Actor4" << endl;

    bool have_header = false;
    // keep reading lines until the end of file is reached
    while (tester) {
        string s;
        // get the next line
        if (!getline(tester, s)) break;
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        istringstream ss(s);
        string second;
        if (!getline(ss, second, '\n')) break;
        string actor(second);
        // check if this actors exist
        if (allActors->count(actor) != 0) {
            // find direct neighbours of input actor
            unordered_set<ActorNode*> firstLevel = levelOne(actor);
            // find possible future collobrators of input actor
            unordered_set<ActorNode*> secondLevel = levelTwo(firstLevel, actor);
            linkQ col = colActors(firstLevel, actor);
            linkQ uncol = uncolActors(firstLevel, secondLevel, actor);
            // output actor names to output file
            for (int i = 0; i < FOUR; i++) {
                if (col.size() != 0) {
                    colFile << col.top()->name << "\t";
                    col.pop();
                }
                if (uncol.size() != 0) {
                    uncolFile << uncol.top()->name << "\t";
                    uncol.pop();
                }
            }
        }
        // reset all actors pripority as 0
        resetPriority();
        colFile << endl;
        uncolFile << endl;
    }
    // if there still have some remaining, return
    if (!tester.eof()) {
        cerr << "Failed to read " << test << "!\n";
        return;
    }
    // open input and output files
    tester.close();
    colFile.close();
    uncolFile.close();
    return;
}