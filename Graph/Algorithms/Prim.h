#ifndef GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
#define GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct Prim {
    UnDirectedGraph<TV, TE> *graph;
    string start;
    Prim(UnDirectedGraph<TV, TE> *graph, const string& start);
    UnDirectedGraph<TV, TE> apply();
};

template<typename TV, typename TE>
Prim<TV, TE>::Prim(UnDirectedGraph<TV, TE> *graph, const string& start) {
    if (!graph->findById(start)) throw invalid_argument("vertex is not on graph");

    this->graph = graph;
    this->start = start;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Prim<TV, TE>::apply() {
    pair<string, TE> distance[graph->getSize()];
    pair<string, string> parent[graph->getSize()];
    int cont = 0;

    for (auto i : graph->vertexes) {
        if (i.first == start) distance[cont] = make_pair(i.first, 0); // distance = 0
        else distance[cont] = make_pair(i.first, -1); // distance = INF
        parent[cont] = make_pair(i.first, ""); // parent = null
        cont++;
    }

    return *graph;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
