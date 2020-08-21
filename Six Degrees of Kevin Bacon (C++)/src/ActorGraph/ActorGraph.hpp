/** File name: ActorGraph.hpp
 * This file contains the all the functions of ActorGraph class, including
 * finding the weighted path, unweighted path, the link predictor and the
 * minimum spanning tree.
 * Author: Xinyi Qi; Jialu Xu
 * E-mail: xiq017@ucsd.edu; jix211@ucsd.edu
 * References: Thanks the tutors for their help.s
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "ActorNode.hpp"

// Maybe include some data structures here

using namespace std;

/** A class, instances of which are two unordered maps, one containing all the
 * actors and the other one containing all the movies in an ActorGraph.
 */
class ActorGraph {
  public:
    unordered_map<string, ActorNode*>* allActors;
    unordered_map<string, MovieNode*>* allMovies;

    /**
     * Constuctor of the Actor graph
     */
    ActorGraph();

    /*
     * Destructor of the Actor graph
     */
    ~ActorGraph();

    /**** GRAPH INITIALIZER ****/

    /** Function name: addActor(string actor, string movie
     * This function adds all movies or actors played in input movie and actor
     * as ActorNodes or MovieNodes. All ActorNodes are added to the
     * unordered_set of ActorNodes in MovieNode Create new ActorNode is the
     * MovieNode does not have input actor yet If actor already in movie, add
     * movie to current actor
     */
    void addActor(string actor, string movie);

    /** Function name: addMovie(string actor, string movie, int year)
     * This function adds all movies or actors played in input movie and actor
     * as ActorNodes or MovieNodes. All ActorNodes are added to the
     * unordered_set of ActorNodes in MovieNode Create new ActorNode is the
     * MovieNode does not have input actor yet If actor already in movie, add
     * movie to current actor
     */
    void addMovie(string actor, string movie, int year);

    /** Function name: generateGraph()
     * This functuon generates the actor graph after all ActorNodes and
     * MovieNodes are created and filled.
     */
    void generateGraph();

    /** Function name: loadFromFile
     * This function opens and reads the input file, parse the string actor
     * name, string movie title, and int year from each line of the input file.
     */
    bool loadFromFile(const char* in_filename);

    /** Function name: initializeGraph()
     * Initialize the graph by setting the unordered_set of actor nodes to be
     * nullptrs.
     * Set initial dist for all ActorNodes as infinite
     */
    void initializeGraph();

    /**** PATH FINDER ****/

    /** Function name: getUnweightedPath()
     * Get the path linking two actors using the movies as edges
     * Do bfs on the the actor graph to look for actor nodes linked by edges of
     * movies.
     */
    string getUnweightedPath(ActorNode* actor1, ActorNode* actor2);

    /** Function name: getWeightedPath()
     * Get the path linking two actors using the movies as edges.
     * Use weighted edges, which are decided by how many years apart from the
     * year the movie was produced to 2019. Do ditrajris on the the actor graph
     * to look for actor nodes linked by edges of movies.
     */
    string getWeightedPath(ActorNode* actor1, ActorNode* actor2);

    /** Function name: printPath ()
     * This function prints the path representing the link between one actor to
     *the other actor to the output file. All actors listed in the test_file
     *will be used to find links. The bool use_weighted_edges decides whether to
     *use weighted or unweighted path.
     **/
    void printPath(const char* test_file, const char* out_file,
                   bool use_weighted_edges);

    /**** LINK PREDICTOR ****/

    /** Function name: levelOne()
     * This function returns all direct neighbours of input actor in the actor
     * graph in an unordered_set of ActorNodes
     */
    unordered_set<ActorNode*> levelOne(string queryActor);

    /** Function name: levelTwo ()
     * This function returns all neighbours of the direct neighbours collected
     * by levelOne(). All neighbours should update the same unordered_set of
     * ActorNodes created by levelOne()
     */
    unordered_set<ActorNode*> levelTwo(unordered_set<ActorNode*> levelone,
                                       string queryActor);

    /** Function name: colActors9)
     * This function put all collorated actors of input actor into a pripority
     * queue. The pripority queue uses comparator for pripority of each actor or
     * ascii value of actor name
     */
    linkQ colActors(unordered_set<ActorNode*> levelone, string queryActor);

    /** Function name: uncolActors ()
     * This function update the pripority queue with actors that may be
     * collobrated in the future to the same queue for actors who had already
     * collobrated with the input actor.
     */
    linkQ uncolActors(unordered_set<ActorNode*> levelone,
                      unordered_set<ActorNode*> leveltwo, string queryActor);

    /** Function name: resetPripority ()
     * This function reset pripority for all actor nodes with 0
     */
    void resetPriority();

    /** Function name: prediction ()
     * This function predicts actors listed in the input test file for list of
     * actors they had collorated before and  may collobrate in the future
     */
    void prediction(const char* test, const char* col_file,
                    const char* uncol_file);

    /**** MOVIE TRAVELER ****/

    /** Function name: findRoot()
     * This function find the root actor node of the actor graph with the
     * given input ActorNode.
     * This function is helper function for path compression in movie traveler
     */
    ActorNode* findRoot(ActorNode* actor);

    /** Function name: combine()
     * This function unions two actor nodes for path compression in movie
     * traveler This function uses the actor node with larger size as the new
     * parent node of the two input actor nodes.
     */
    bool combine(ActorNode* actor1, ActorNode* actor2);

    /** Function name: movieTraveler()
     * This function loops through all edges between actors and movies in the
     * actor graph. Then get the pair of actors and moives, push each pair into
     * pripority queue using comparator of weight on edges. Then do path
     * compression on the weighted edges.
     */
    void movieTraveler(const char* output);
};

#endif  // ACTORGRAPH_HPP
