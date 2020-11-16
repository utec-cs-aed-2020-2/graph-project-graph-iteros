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
    UnDirectedGraph<TV, TE> g;
    auto pq = graph->getOrderedEdges();

    while (g.getSize() < graph->getSize() && !pq.empty()) {
        Edge<TV, TE>* e = pq.top();
        pq.pop();

        UnDirectedGraph<TV, TE> temp;
        temp.insertVertex(e->vertexes[0]->key, e->vertexes[0]->data);
        temp.insertVertex(e->vertexes[1]->key, e->vertexes[1]->data);
        temp.createEdge(e->vertexes[0]->key, e->vertexes[1]->key, e->weight);

        if (!temp.isCyclic()) {
            g.insertVertex(e->vertexes[0]->key, e->vertexes[0]->data);
            g.insertVertex(e->vertexes[1]->key, e->vertexes[1]->data);
            g.createEdge(e->vertexes[0]->key, e->vertexes[1]->key, e->weight);
        }
    }

    return g;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H
