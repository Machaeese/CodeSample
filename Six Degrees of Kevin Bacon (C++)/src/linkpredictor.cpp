/** File name: linkpredictor.cpp
 * This file contains the main fuction executing the linkpredictor program.
 * Author: Xinyi Qi; Jialu Xu
 * E-mail: xiq017@ucsd.edu; jix211@ucsd.edu
 * References: Thanks the tutors for their help.
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "ActorGraph.hpp"

using namespace std;

#define TWO 2
#define THREE 3
#define FOUR 4

/*Function name: main(int argc, char* argv[])
 * This function is the Main program that runs the linkprediction, which takes
 * in the big data set, test actors and output the first four actor who would
 * likely to collaborate with the given actor both in collaborated actors and
 * uncollaborated actors.
 */
int main(int argc, char* argv[]) {
    ActorGraph actorGraph;
    char* movies = argv[1];
    char* test = argv[TWO];
    char* collaborated = argv[THREE];
    char* uncollaborated = argv[FOUR];
    // load for the file
    actorGraph.loadFromFile(movies);
    // call prediction to output two files
    actorGraph.prediction(test, collaborated, uncollaborated);
    return 0;
}
