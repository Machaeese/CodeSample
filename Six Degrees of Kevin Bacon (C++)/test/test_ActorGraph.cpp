/**
 * File name: test_HCTree.cpp
 * This file includes testers for HCTree class
 * Author: Xinyi Qi; Jialu Xu
 * E-mail: xiq017@ucsd.edu;jix211@ucsd.edu
 * Reference: Thanks the tutors for their help.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

class SimpleAG : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG() {
        // initialization code here
        string actor = "Amy";
        string movie = "HaHa@2010";
        actorGraph.addActor(actor, movie);
        actorGraph.addMovie(actor, movie, 2010);
        actorGraph.generateGraph();
    }
};

TEST_F(SimpleAG, TEST_Simple) {
    string name = actorGraph.allActors->at("Amy")->name;
    int actornode = actorGraph.allActors->at("Amy")->movies.count("HaHa@2010");
    string movie = actorGraph.allMovies->at("HaHa@2010")->name;
    int movienode = actorGraph.allMovies->at("HaHa@2010")->actors.count("Amy");
    ActorNode* actor1 = new ActorNode("Amy");
    ActorNode* actor2 = new ActorNode("Beth");
    ASSERT_EQ("\n", actorGraph.getUnweightedPath(actor1, actor1));
    ASSERT_EQ("\n", actorGraph.getUnweightedPath(actor1, actor2));
    ASSERT_EQ(actornode, 1);
    ASSERT_EQ(movienode, 1);
    ASSERT_EQ(name, "Amy");
    ASSERT_EQ(movie, "HaHa@2010");
}

class SimpleAG2 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG2() {
        // initialization code here
        string actor1 = "Amy";
        string movie1 = "HaHa@2010";
        string actor2 = "Beth";
        string movie2 = "XiXi@2010";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2010);
        actorGraph.addActor(actor2, movie2);
        actorGraph.addMovie(actor2, movie2, 2010);
        actorGraph.generateGraph();
    }
};

TEST_F(SimpleAG2, TEST_Simple1) {
    ActorNode* actor1 = new ActorNode("Amy");
    ActorNode* actor2 = new ActorNode("Beth");
    ASSERT_EQ("\n", actorGraph.getUnweightedPath(actor1, actor1));
    ASSERT_EQ("\n", actorGraph.getUnweightedPath(actor1, actor2));
}

TEST_F(SimpleAG2, TEST_Simple2) {
    string name1 = actorGraph.allActors->at("Amy")->name;
    int actornode1 = actorGraph.allActors->at("Amy")->movies.count("HaHa@2010");
    string movie1 = actorGraph.allMovies->at("HaHa@2010")->name;
    int movienode1 = actorGraph.allMovies->at("HaHa@2010")->actors.count("Amy");
    string name2 = actorGraph.allActors->at("Beth")->name;
    int actornode2 =
        actorGraph.allActors->at("Beth")->movies.count("XiXi@2010");
    string movie2 = actorGraph.allMovies->at("XiXi@2010")->name;
    int movienode2 =
        actorGraph.allMovies->at("XiXi@2010")->actors.count("Beth");
    ASSERT_EQ(actornode1, 1);
    ASSERT_EQ(movienode1, 1);
    ASSERT_EQ(name1, "Amy");
    ASSERT_EQ(movie1, "HaHa@2010");
    ASSERT_EQ(actornode2, 1);
    ASSERT_EQ(movienode2, 1);
    ASSERT_EQ(name2, "Beth");
    ASSERT_EQ(movie2, "XiXi@2010");
}

class SimpleAG3 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG3() {
        // initialization code here
        string actor1 = "Amy";
        string movie1 = "HaHa#@2010";
        string actor2 = "Beth";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2010);
        actorGraph.addActor(actor2, movie1);
        actorGraph.addMovie(actor2, movie1, 2010);
        actorGraph.generateGraph();
    }
};

TEST_F(SimpleAG3, TEST_Simple1) {
    ActorNode* actor1 = actorGraph.allActors->at("Amy");
    ActorNode* actor2 = actorGraph.allActors->at("Beth");
    ASSERT_EQ("(Amy)--[HaHa#@2010]-->(Beth)",
              actorGraph.getUnweightedPath(actor1, actor2));
    ASSERT_EQ("\n", actorGraph.getUnweightedPath(actor1, actor1));
}

class SimpleAG4 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG4() {
        // initialization code here
        string actor1 = "Amy";
        string actor2 = "Beth";
        string movie1 = "HaHa@2010";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2010);
        actorGraph.addActor(actor2, movie1);
        actorGraph.addMovie(actor2, movie1, 2010);
    }
};

TEST_F(SimpleAG4, TEST_Simple4) {
    string name1 = actorGraph.allMovies->at("HaHa@2010")->name;
    int size = actorGraph.allMovies->at("HaHa@2010")->actors.size();
    int actornode1 = actorGraph.allMovies->at("HaHa@2010")->actors.count("Amy");
    int actornode2 =
        actorGraph.allMovies->at("HaHa@2010")->actors.count("Beth");
    ASSERT_EQ(name1, "HaHa@2010");
    ASSERT_EQ(size, 2);
    ASSERT_EQ(actornode1, 1);
    ASSERT_EQ(actornode2, 1);
}

class SimpleAG5 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG5() {
        // initialization code here
        string actor1 = "Clifton Dunn";
        string actor2 = "Stef Dawson";
        string actor3 = "Richard Kind";
        string actor4 = "Penn Badgley";
        string movie1 = "The Paper Store@2016";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2016);
        actorGraph.addActor(actor2, movie1);
        actorGraph.addMovie(actor2, movie1, 2016);
        actorGraph.addActor(actor3, movie1);
        actorGraph.addMovie(actor3, movie1, 2016);
        actorGraph.addActor(actor4, movie1);
        actorGraph.addMovie(actor4, movie1, 2016);
    }
};

TEST_F(SimpleAG5, TEST_Simple5) {
    string name1 = actorGraph.allMovies->at("The Paper Store@2016")->name;
    int size = actorGraph.allMovies->at("The Paper Store@2016")->actors.size();
    int actornode1 = actorGraph.allMovies->at("The Paper Store@2016")
                         ->actors.count("Clifton Dunn");
    int actornode2 = actorGraph.allMovies->at("The Paper Store@2016")
                         ->actors.count("Stef Dawson");
    int actornode3 = actorGraph.allMovies->at("The Paper Store@2016")
                         ->actors.count("Richard Kind");
    int actornode4 = actorGraph.allMovies->at("The Paper Store@2016")
                         ->actors.count("Penn Badgley");
    ASSERT_EQ(name1, "The Paper Store@2016");
    ASSERT_EQ(size, 4);
    ASSERT_EQ(actornode1, 1);
    ASSERT_EQ(actornode2, 1);
    ASSERT_EQ(actornode3, 1);
    ASSERT_EQ(actornode4, 1);
}

// tester for actor not found
class SimpleAG7 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG7() {
        // initialization code here
        string actor1 = "Daryl Sabara";
        string movie1 = "The Browsing Effect@2018";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2018);
    }
};

TEST_F(SimpleAG7, TEST_Simple7) {
    string name1 = actorGraph.allMovies->at("The Browsing Effect@2018")->name;
    int size =
        actorGraph.allMovies->at("The Browsing Effect@2018")->actors.size();
    int actornode1 = actorGraph.allMovies->at("The Browsing Effect@2018")
                         ->actors.count("Brad Dourif");
    ASSERT_EQ(name1, "The Browsing Effect@2018");
    ASSERT_EQ(size, 1);
    ASSERT_EQ(actornode1, 0);
}

// tester for actors in wrong movie
class SimpleAG9 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG9() {
        // initialization code here
        string actor1 = "Daryl Sabara";
        string actor2 = "Kim Basinger";
        string movie1 = "Spy Kids@2001";
        string movie2 = "The Informers@2008";
        actorGraph.addActor(actor1, movie2);
        actorGraph.addMovie(actor1, movie2, 2008);

        actorGraph.addActor(actor2, movie1);
        actorGraph.addMovie(actor2, movie1, 2008);
    }
};

TEST_F(SimpleAG9, TEST_Simple8) {
    string name1 = actorGraph.allMovies->at("Spy Kids@2001")->name;
    int size = actorGraph.allMovies->at("Spy Kids@2001")->actors.size();
    string actor1 =
        *(actorGraph.allMovies->at("Spy Kids@2001")->actors.begin());

    string name2 = actorGraph.allMovies->at("The Informers@2008")->name;
    int size2 = actorGraph.allMovies->at("The Informers@2008")->actors.size();
    string actor2 =
        *(actorGraph.allMovies->at("The Informers@2008")->actors.begin());

    ASSERT_EQ(name1, "Spy Kids@2001");
    ASSERT_NE(actor1, "Daryl Sabara");
    ASSERT_EQ(size, 1);

    ASSERT_EQ(name2, "The Informers@2008");
    ASSERT_NE(actor2, "Kim Basinger");
    ASSERT_EQ(size2, 1);
}

// tester for successful loadFromFile
class SimpleAG10 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;
};

TEST_F(SimpleAG10, TEST_Simple10) {
    const char* list = "./data/imdb_small_sample.tsv";
    bool weighted = false;
    ASSERT_EQ(actorGraph.loadFromFile(list), true);
}

// tester for inserting new movie to existing actor
class SimpleAG12 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG12() {
        // initialization code here
        string actor1 = "Daryl Sabara";
        string movie1 = "Spy Kids@2001";
        string movie2 = "The Informers@2008";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2008);
        actorGraph.addActor(actor1, movie2);
        actorGraph.addMovie(actor1, movie2, 2008);
    }
};

TEST_F(SimpleAG12, TEST_Simple12) {
    string name1 = actorGraph.allMovies->at("Spy Kids@2001")->name;
    int size = actorGraph.allMovies->at("Spy Kids@2001")->actors.size();
    string actor1 =
        *(actorGraph.allMovies->at("Spy Kids@2001")->actors.begin());
    string name2 = actorGraph.allMovies->at("The Informers@2008")->name;
    int movie_size = actorGraph.allActors->at("Daryl Sabara")->movies.size();

    ASSERT_EQ(name1, "Spy Kids@2001");
    ASSERT_EQ(name2, "The Informers@2008");
    ASSERT_EQ(size, 1);
    ASSERT_EQ(movie_size, 2);
}

// tester for inserting new actors to exitsing movie
class SimpleAG13 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG13() {
        // initialization code here
        string actor1 = "Daryl Sabara";
        string actor2 = "Brad Dourif";
        string actor3 = "Harley Jane Kozak";
        string actor4 = "Erik Palladino";
        string movie1 = "Spy Kids@2001";
        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2001);
        actorGraph.addActor(actor2, movie1);
        actorGraph.addMovie(actor2, movie1, 2001);
        actorGraph.addActor(actor3, movie1);
        actorGraph.addMovie(actor3, movie1, 2001);
        actorGraph.addActor(actor4, movie1);
        actorGraph.addMovie(actor4, movie1, 2001);
    }
};

TEST_F(SimpleAG13, TEST_Simple13) {
    string name1 = actorGraph.allMovies->at("Spy Kids@2001")->name;
    int actor_size = actorGraph.allMovies->at("Spy Kids@2001")->actors.size();

    ASSERT_EQ(name1, "Spy Kids@2001");
    ASSERT_EQ(actor_size, 4);
}

// tester for printPath empty file
class SimpleAG14 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;
};

TEST_F(SimpleAG14, TEST_Simple14) {
    char* list = "./data/header.tsv";
    char* output = "./../sample_out.tsv";
    bool weighted = false;
    actorGraph.printPath(list, output, weighted);
    string line;
    ifstream infile("./../sample_out.tsv");
    std::getline(infile, line);
    ASSERT_EQ("(actor)--[movie#@year]-->(actor)--...", line);
}

class SimpleAG16 : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
    SimpleAG16() {
        // initialization code here
        string actor1 = "Kevin Bacon";
        string actor2 = "James McAvoy";
        string actor3 = "Michael Fassbender";
        string actor4 = "Samuel L. Jackson";
        string actor5 = "Robert Downey Jr.";
        string actor6 = "Tom Holland";
        string actor7 = "Katherine Waterston";

        string movie1 = "X-Men: First Class@2011";
        string movie2 = "Glass@2019";
        string movie3 = "Avengers: Endgame@2019";
        string movie4 = "Spider-Man: Homecoming@2017";
        string movie5 = "The Current War@2017";
        string movie6 = "Alien: Covenant@2017";
        string movie7 = "X-Men: Apocalypse@2016";

        actorGraph.addActor(actor1, movie1);
        actorGraph.addMovie(actor1, movie1, 2011);

        actorGraph.addActor(actor2, movie1);
        actorGraph.addMovie(actor2, movie1, 2011);
        actorGraph.addActor(actor2, movie7);
        actorGraph.addMovie(actor2, movie7, 2016);
        actorGraph.addActor(actor2, movie2);
        actorGraph.addMovie(actor2, movie2, 2019);

        actorGraph.addActor(actor3, movie1);
        actorGraph.addMovie(actor3, movie1, 2011);
        actorGraph.addActor(actor3, movie7);
        actorGraph.addMovie(actor3, movie7, 2016);
        actorGraph.addActor(actor3, movie6);
        actorGraph.addMovie(actor3, movie6, 2017);

        actorGraph.addActor(actor4, movie2);
        actorGraph.addMovie(actor4, movie2, 2019);
        actorGraph.addActor(actor4, movie3);
        actorGraph.addMovie(actor4, movie3, 2019);

        actorGraph.addActor(actor5, movie3);
        actorGraph.addMovie(actor5, movie3, 2019);
        actorGraph.addActor(actor5, movie4);
        actorGraph.addMovie(actor5, movie4, 2017);

        actorGraph.addActor(actor6, movie4);
        actorGraph.addMovie(actor6, movie4, 2017);
        actorGraph.addActor(actor6, movie5);
        actorGraph.addMovie(actor6, movie5, 2017);

        actorGraph.addActor(actor7, movie5);
        actorGraph.addMovie(actor7, movie5, 2017);
        actorGraph.addActor(actor7, movie6);
        actorGraph.addMovie(actor7, movie6, 2017);
        actorGraph.generateGraph();
    }
};

TEST_F(SimpleAG16, TEST_Simple16) {
    string queryActor = "Kevin Bacon";
    unordered_set<ActorNode*> actors_one = actorGraph.levelOne(queryActor);
    unordered_set<ActorNode*> actors_two =
        actorGraph.levelTwo(actors_one, queryActor);
    linkQ queue_work = actorGraph.colActors(actors_one, queryActor);
    linkQ queue_un = actorGraph.uncolActors(actors_one, actors_two, queryActor);
    actorGraph.resetPriority();

    const char* file = "./../test_actors.tsv";
    const char* worked = "./work.tsv";
    const char* unworked = "./unworked.tsv";
    actorGraph.prediction(file, worked, unworked);

    // Tester for weighted path
    ActorNode* actor1 = actorGraph.allActors->at("Michael Fassbender");
    ActorNode* actor2 = actorGraph.allActors->at("James McAvoy");
    ActorNode* actor3 = actorGraph.allActors->at("Kevin Bacon");

    ASSERT_EQ("(James McAvoy)--[X-Men: Apocalypse@2016]-->(Michael Fassbender)",
              actorGraph.getWeightedPath(actor2, actor1));
    ASSERT_EQ("(James McAvoy)--[X-Men: First Class@2011]-->(Kevin Bacon)",
              actorGraph.getWeightedPath(actor2, actor3));
    ASSERT_EQ("\n", actorGraph.getWeightedPath(actor1, actor1));

    // find root
    ActorNode* rootNode = actorGraph.findRoot(actor1);
    // combine ?
    actorGraph.combine(actor1, actor2);
    // movie traveler
    const char* output = "./../output.tsv";
    actorGraph.movieTraveler(output);
}
