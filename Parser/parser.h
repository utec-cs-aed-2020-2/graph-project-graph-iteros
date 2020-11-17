#ifndef GRAPH_PROJECT_GRAPH_ITEROS_PARSER_H
#define GRAPH_PROJECT_GRAPH_ITEROS_PARSER_H

#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"

struct Parser {
    void clear(); // Clears parser saved atributes
    void readJSON(); // Parses JSON file and saves data into class
    // NOTE: each derived class has its own read JSON method
    void uGraphMake(UnDirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph
    void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
};

void Parser::clear() {

}

void Parser::readJSON() {

}

void Parser::uGraphMake(UnDirectedGraph<string, double> &tempGraph) {

}

void Parser::dGraphMake(DirectedGraph<string, double> &tempGraph) {

}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_PARSER_H
