#ifndef GRAPH_PROJECT_GRAPH_ITEROS_BF_H
#define GRAPH_PROJECT_GRAPH_ITEROS_BF_H

#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <limits>

template<typename TV, typename TE>
struct BF {
    Graph<TV, TE>* graph;
    string src;
    BF(Graph<TV, TE>* graph, string src);
    void apply();
};

template<typename TV, typename TE>
BF<TV, TE>::BF(Graph<TV, TE> *graph, string src) {
    this->graph = graph;
    this->src = src;
}

template<typename TV, typename TE>
void BF<TV, TE>::apply() {
    unordered_map<TV, TE> dist;
    int v = graph->vertexes.size();
    int e = graph->edges;
    TV srcData;
    TE infinite;

    //infinite representation
    if (std::numeric_limits<TE>::has_infinity) infinite = std::numeric_limits<TE>::infinity();
    else infinite = std::numeric_limits<TE>::max();

    //initialize distance from src to all vertexes
    for (auto i : graph->vertexes) {
        dist[i.second->data] = infinite;
        if (i.first == src) srcData = i.second->data;
    }
    dist[srcData] = 0;

    //calculate shortest distances
    for (int k = 0; k < v - 1; ++k) {
        for (auto i : graph->vertexes) {
            TV edgeSrc = i.second->data;
            for (auto j : i.second->edges) {
                TV edgeDest = j->vertexes[1]->data;
                TE edgeWeight = j->weight;

                if (dist[edgeSrc] != infinite && dist[edgeSrc] + edgeWeight < dist[edgeDest])
                    dist[edgeDest] = dist[edgeSrc] + edgeWeight;
            }
        }
    }

    //detect cycles formed by negative weights
    for (auto i : graph->vertexes) {
        TV edgeSrc = i.second->data;
        for (auto j : i.second->edges) {
            TV edgeDest = j->vertexes[1]->data;
            TE edgeWeight = j->weight;

            if (dist[edgeSrc] != infinite && dist[edgeSrc] + edgeWeight < dist[edgeDest]) {
                cout << "Negative weight cycle detected";
                return;
            }
        }
    }

    //print result
    cout << "Shortest distance from " << srcData << ": " << endl;
    cout << "Vertex\tDistance" << endl;
    for (auto i : dist) {
        cout << i.first << "\t" << i.second << endl;
    }
}


#endif //GRAPH_PROJECT_GRAPH_ITEROS_BF_H
