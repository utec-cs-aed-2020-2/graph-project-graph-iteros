#ifndef GRAPH_PROJECT_GRAPH_ITEROS_A_H
#define GRAPH_PROJECT_GRAPH_ITEROS_A_H

#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"

template<typename TV, typename TE>
struct A {
    Graph<TV, TE>* graph;
    string src;
    string dest;
    A(Graph<TV, TE>* graph, string src, string dest);
    void apply();
};

template<typename TV, typename TE>
A<TV, TE>::A(Graph<TV, TE> *graph, string src, string dest) {
    this->graph = graph;
    this->src = src;
    this->dest = dest;
}

template<typename TV, typename TE>
void A<TV, TE>::apply() {

}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_A_H
