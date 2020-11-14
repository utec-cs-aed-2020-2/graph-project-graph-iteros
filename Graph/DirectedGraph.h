#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
private:
    ///TODO: No sé qué quieran agregar al grafo

public:
    DirectedGraph();

    bool insertVertex(string id, TV vertex) override;

    bool createEdge(string id1, string id2, TE w) override;
    bool deleteVertex(string id) override;
    bool deleteEdge(string id) override;

    TE &operator()(string start, string end)= 0;
    float density() = 0;
    bool isDense(float threshold = 0.5) = 0;
    bool isConnected()= 0;
    bool isStronglyConnected() throw();
    bool empty();
    void clear()= 0;

    void displayVertex(string id)= 0;
    bool findById(string id) = 0;
    void display() = 0;
};


template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteVertex(string id) {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteEdge(string id) {

}

template<typename TV, typename TE>
TE& DirectedGraph<TV, TE>::operator()(string start, string end) {

}

template<typename TV, typename TE>
float DirectedGraph<TV, TE>::density() {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isDense(float threshold) {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isConnected() {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isStronglyConnected() throw() {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::empty() {

}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::clear() {

}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::displayVertex(string id) {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::findById(string id) {

}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::display() {

}


#endif