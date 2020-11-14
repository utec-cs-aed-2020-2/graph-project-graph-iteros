#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
private:
    ///TODO: No sé qué quieran agregar al grafo

public:
    UnDirectedGraph();

    bool insertVertex(string id, TV vertex) override;

    bool createEdge(string id1, string id2, TE w) override;
    bool deleteVertex(string id) override;
    bool deleteEdge(string id) override;

    TE &operator()(string start, string end)= 0;
    float density() = 0;
    bool isDense(float threshold = 0.5) = 0;
    bool isConnected()= 0;

    bool empty();
    void clear()= 0;

    void displayVertex(string id)= 0;
    bool findById(string id) = 0;
    void display() = 0;

};

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::UnDirectedGraph() {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id) {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(string id) {

}

template<typename TV, typename TE>
TE& UnDirectedGraph<TV, TE>::operator()(string start, string end) {

}

template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {

}


template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected() {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() {

}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear() {

}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id) {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id) {

}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display() {

}


#endif