#ifndef GRAPH_PROJECT_GRAPH_ITEROS_PARSER_H
#define GRAPH_PROJECT_GRAPH_ITEROS_PARSER_H

#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"

#include <fstream>
using namespace rapidjson;

struct Parser {
    Document d;
    void clear(); // Clears parser saved atributes
    void readJSON(); // Parses JSON file and saves data into class
    // NOTE: each derived class has its own read JSON method
    void uGraphMake(UnDirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph
    void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
    void printJSON();
};

void Parser::clear() {

}

void Parser::readJSON() {
    std::ifstream is("../partry.json",std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char *json = new char[length];

        // std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read(json, length);

        d.Parse(json);

    }
    is.close();
}
void Parser::printJSON(){
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::cout << buffer.GetString() << std::endl;
}


void Parser::uGraphMake(UnDirectedGraph<string, double> &tempGraph) {

}

void Parser::dGraphMake(DirectedGraph<string, double> &tempGraph) {
    for(auto &x: d.GetArray()){

    }
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_PARSER_H
