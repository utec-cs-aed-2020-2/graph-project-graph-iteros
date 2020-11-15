#ifndef GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H
#define GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H

#include "UndirectedGraph.h"

template<typename TV, typename TE>
struct Kruskal {
    UnDirectedGraph<TV, TE> *graph;
    Kruskal(UnDirectedGraph<TV, TE> *graph);
    UnDirectedGraph<TV, TE> apply();
};

template<typename TV, typename TE>
Kruskal<TV, TE>::Kruskal(UnDirectedGraph<TV, TE> *graph) {
    this->graph = graph;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Kruskal<TV, TE>::apply() {
    return *graph;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H
