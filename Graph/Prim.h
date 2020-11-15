#ifndef GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
#define GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H

#include "UndirectedGraph.h"

template<typename TV, typename TE>
struct Prim {
    UnDirectedGraph<TV, TE> *graph;
    string start;
    Prim(UnDirectedGraph<TV, TE> *graph, const string& start);
    UnDirectedGraph<TV, TE> apply();
};

template<typename TV, typename TE>
Prim<TV, TE>::Prim(UnDirectedGraph<TV, TE> *graph, const string& start) {
    this->graph = graph;
    this->start = start;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Prim<TV, TE>::apply() {
    return *graph;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
