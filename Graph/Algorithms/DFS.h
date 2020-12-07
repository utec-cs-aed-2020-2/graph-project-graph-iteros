//
// Created by Jorge on 7/12/2020.
//

#ifndef GRAPH_PROJECT_GRAPH_ITEROS_DFS_H
#define GRAPH_PROJECT_GRAPH_ITEROS_DFS_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct DFS {
    UnDirectedGraph<TV, TE> *graph;
    DFS(UnDirectedGraph<TV, TE> *graph);
    UnDirectedGraph<TV, TE> apply();
};


template<typename TV, typename TE>
DFS<TV, TE>::DFS(UnDirectedGraph<TV, TE> *_graph_) {
    this->graph = _graph_;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> DFS<TV, TE>::apply() {
    UnDirectedGraph<TV, TE> g;
    int s = graph->vertexes.size();
    std::stack<EPair<TV, TE>> S;
    std::unordered_map<TV, std::pair<bool, string>> visited;
    for (auto x : graph->vertexes) {
        visited[x.second->key].first = false;          // Visitados
        visited[x.second->key].second = x.first;       // id
        g.insertVertex(x.first , (x.second)->data, x.second->latitud, x.second->latitud);     // Rellenar los vértices
    }

    visited[graph->vertexes.begin()->second->key].first = true;
    S.push(make_pair(nullptr, graph->vertexes.begin()->second));
    // cout << "BEGIN: " << graph->vertexes.begin()->second->data << endl;
    while(!S.empty()) {
        Vertex<TV, TE>* v = S.top().second;
        S.pop();
        priority_queue<EPair<TV, TE>, std::vector<EPair<TV, TE>>, compPairs2<TV, TE>> pq;
        for (auto unions : v->edges) {
            pq.push(make_pair(unions, unions->vertexes[1]));
            // visited[unions->vertexes[1]->key].first = true;
        }

        // cout << "\nVERTICE : " << v->key <<endl;
        while ( !pq.empty() ) {
            if (!visited[pq.top().second->key].first) {
                // cout << "\t" << pq.top().second->key << endl;
                S.push(pq.top());
            }
            pq.pop();
        }
        // cout << endl;

        if ( !S.empty() ) {
            EPair<TV, TE> u = S.top();
            if (!visited[u.first->vertexes[1]->key].first) {
                g.createEdge(u.first->vertexes[0]->key, u.first->vertexes[1]->key, u.first->weight);
                visited[u.first->vertexes[0]->key].first = true;
                visited[u.first->vertexes[1]->key].first = true;
                // cout << "EDGE CREATED: " << u.first->vertexes[0]->key << " <- " << u.first->weight << " -> " << u.first->vertexes[1]->key << endl;
            }
        }
    }
    g.display2();
    return g;
}


#endif //GRAPH_PROJECT_GRAPH_ITEROS_DFS_H
