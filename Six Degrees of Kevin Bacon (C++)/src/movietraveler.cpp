/*
 * movietraveler.cpp
 * Author: Jialu Xu; Xinyi Qi
 * Email: jix211@ucsd.edu; xiq017@ucsd.edu
 * Date: 2019/12/03
 *
 * This file is meant to
 */

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include "ActorGraph.hpp"

#define TWO 2

using namespace std;

int main(int argc, char* argv[]) {
    ActorGraph actorGraph;
    char* movies = argv[1];
    char* output = argv[TWO];
    actorGraph.loadFromFile(movies);
    actorGraph.movieTraveler(output);
    return 0;
}