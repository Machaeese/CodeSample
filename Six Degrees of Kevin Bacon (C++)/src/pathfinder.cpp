/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include "ActorGraph.hpp"

#define TWO 2
#define THREE 3
#define FOUR 4

using namespace std;

int main(int argc, char* argv[]) {
    bool weighted = false;
    // check if user would like to build up the graph with weighted or
    // unweighted edge
    if (*argv[TWO] == 'w') {
        weighted = true;
    }

    ActorGraph actorGraph;
    char* movies = argv[1];
    char* test = argv[THREE];
    char* output = argv[FOUR];

    actorGraph.loadFromFile(movies);
    actorGraph.printPath(test, output, weighted);
    return 0;
}