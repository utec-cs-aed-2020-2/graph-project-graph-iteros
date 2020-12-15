//
// Created by Jorge on 7/12/2020.
//

#ifndef GRAPH_PROJECT_GRAPH_ITEROS_DIJKSTRA_H
#define GRAPH_PROJECT_GRAPH_ITEROS_DIJKSTRA_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct Dijkstra {
    string src;
    UnDirectedGraph<TV, TE> *graph;
    Dijkstra(UnDirectedGraph<TV, TE> *graph, string src);
    unordered_map<string, TE> apply();
};

template<typename TV, typename TE>
Dijkstra<TV, TE>::Dijkstra(UnDirectedGraph<TV, TE> *_graph_, string _src_) {
    this->graph = _graph_;
    this->src = _src_;
}

template<typename TV, typename TE>
unordered_map<string, TE> Dijkstra<TV, TE>::apply() {
    priority_queue<EPair<TV, TE>, std::vector<EPair<TV, TE>>, compPairs<TV, TE>> pq;
    unordered_map<string, TE> dist;

    for (auto it : graph->vertexes) {
        dist[it.first] = INF;
    }

    dist[src] = 0;
    pq.push(make_pair(nullptr, graph->vertexes[src]));

    while ( !pq.empty() ) {
        string u = pq.top().second->key;
        pq.pop();
        for (auto it : graph->vertexes[u]->edges) {
            string v = it->vertexes[1]->key;
            TE weight = it->weight;
            if ( dist.count(v) && dist[v] > dist[u] + weight ) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(it, it->vertexes[1]));
            }
        }
    }

    cout << "\nPrint Dijkstra:\n";
    for (auto x : dist) {
        cout << graph->vertexes[x.first]->data << ": " << x.second << endl;
    }

    return dist;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_DIJKSTRA_H
