/** File name: ActorNode.hpp
 * This file contains the class of ActorNode, which contains an unordered_set
 * with all his/her movies.
 * Author: Xinyi Qi; Jialu Xu
 * E-mail: xiq017@ucsd.edu; jix211@ucsd.edu
 * References: Thanks the tutors for their help.
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/** A class, which will be defined later. */
class ActorNode;

/** A class, instances of which are the name of the edge(movie), the weight of
 * the movie(2019-YEAR+1), the ActorNode before it, and the ActorNode after it
 * in an Edge.
 */
class Edge {
  public:
    string name;
    int weight;
    ActorNode* prev;
    ActorNode* next;

    /* Constructor that initialize a (Movie)Edge */
    Edge(string name, int weight, ActorNode* actor1, ActorNode* actor2)
        : name(name), weight(weight), prev(actor1), next(actor2) {}

    /* Destructor of the (Movie)Edge*/
    ~Edge() {}
};

/** A class, instances of which are name of the actor, the distance from the
 * source node, the priority for linkpredictor, bool indicating if the node as
 * been visited or not for movietraveler, the ActorNode pointer for the parent,
 * the size for movie traveler, the pair of previous ActorNode and the name of
 * the common movie, the unordered set of edges(movies) of the actor, the
 * unorder set of all movies acted by this actor, the map of the ActorNode and
 * the number of common movies in an ActorNode.
 */
class ActorNode {
  public:
    string name;   // the name of the actor
    int dist;      // the distance from the source
    int priority;  // the priority for the actorNode when predicting the link
    bool done;  // the flag indicating that if the actor node has been visited
                // or not
    ActorNode* parent;  // the parent node of the currect node
    int size;           // the set size for movie traveler
    pair<ActorNode*, string>
        prev;  // the previous node in the path and the movie name
    unordered_set<Edge*>
        edges;  // the edges relate two actornodes (usd as neighbors)
    unordered_set<string>
        movies;  // a vector storing all the movies of this actor
    unordered_map<ActorNode*, int>
        common;  // the map containing the how many times two actors cast the
                 // same movie

    /* Constructor that initialize a ActorNode */
    ActorNode(string name) : name(name) {
        dist = INT_MAX;
        priority = 0;
        parent = nullptr;
        size = 1;
        prev.first = nullptr;
        prev.second = "";
    }

    /*Destructor for ActorNode*/
    ~ActorNode() {}
};

/** A class, instances of which are the name of the movie, the year of the
 * movie, the set of actors who played in a MovieNode.
 */
class MovieNode {
  public:
    string name;
    int year;
    unordered_set<string> actors;

    /* Constructor that initialize a MovieEdge */
    MovieNode(string name, int year) : name(name), year(year) {}

    /* Destructor of MovieNode */
    ~MovieNode() {}
};

// comparator for priority queue for link predictor, which compares the priority
// of ActorNode
struct ActorComp {
  public:
    bool operator()(ActorNode* first, ActorNode* second) {
        // if there is a tie, check alphabet
        if (first->priority == second->priority) {
            return first->name > second->name;
        }
        // check pripority based on number of connections
        return first->priority < second->priority;
    }
};

// comparator for priority queue for link predictor, which compares the weight
// of ActorNode
struct WeightComp {
  public:
    bool operator()(pair<ActorNode*, int> first, pair<ActorNode*, int> second) {
        // if there is a tie, check alphabet
        if (first.second == second.second) {
            return first.first->name > second.first->name;
        }
        // check pripority based on number of connections
        return first.second > second.second;
    }
};

// comparator for priority queue for edges, which compares the weight of edges
struct EdgeComp {
  public:
    bool operator()(Edge* first, Edge* second) {
        // if there is a tie, check alphabet
        if (first->weight == second->weight) {
            return first->name < second->name;
        }
        // check the weight of two edges
        return first->weight > second->weight;
    }
};

// define a priority queue comparing ActorNode* using ActorComp
typedef priority_queue<ActorNode*, std::vector<ActorNode*>, ActorComp> linkQ;

// define a priority queue comparing pair<ActorNode*, int> using WeightComp
typedef priority_queue<pair<ActorNode*, int>,
                       std::vector<pair<ActorNode*, int>>, WeightComp>
    linkW;

// define a priority queue comparing Edge* using EdgeComp
typedef priority_queue<Edge*, std::vector<Edge*>, EdgeComp> linkE;

#endif  // ACTORNODE_HPP
