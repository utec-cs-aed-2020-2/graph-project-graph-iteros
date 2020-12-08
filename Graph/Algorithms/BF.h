#ifndef GRAPH_PROJECT_GRAPH_ITEROS_BF_H
#define GRAPH_PROJECT_GRAPH_ITEROS_BF_H

#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"

template<typename TV, typename TE>
struct BF {
    Graph<TV, TE>* graph;
    BF(Graph<TV, TE>* graph);
    void apply();
};

template<typename TV, typename TE>
BF<TV, TE>::BF(Graph<TV, TE> *graph) {
    this->graph = graph;
}

template<typename TV, typename TE>
void BF<TV, TE>::apply() {

}


#endif //GRAPH_PROJECT_GRAPH_ITEROS_BF_H
