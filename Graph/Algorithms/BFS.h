//
// Created by Jorge on 7/12/2020.
//

#ifndef GRAPH_PROJECT_GRAPH_ITEROS_BFS_H
#define GRAPH_PROJECT_GRAPH_ITEROS_BFS_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct BFS {
    UnDirectedGraph<TV, TE> *graph;
    BFS(UnDirectedGraph<TV, TE> *graph);
    UnDirectedGraph<TV, TE> apply(string src);
};


template<typename TV, typename TE>
BFS<TV, TE>::BFS(UnDirectedGraph<TV, TE> *_graph_) {
    this->graph = _graph_;

}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> BFS<TV, TE>::apply(string src) {
    UnDirectedGraph<TV, TE> g;
    int s = this->graph->vertexes.size();
    std::queue<Vertex<TV, TE>*> S;
    std::unordered_map<TV, std::pair<bool, string>> visited;
    //std::unordered_map<TV, int> ids;
    for (auto x : this->graph->vertexes) {
        visited[x.second->data].first = false;          // Mapa de Visitados
        visited[x.second->data].second = x.first;       // id
        g.insertVertex(x.first , (x.second)->data);     // Rellenar los vértices
    }

    visited[this->graph->vertexes.begin()->second->data].first = true;
    if(this->graph->findById(src)){
        S.push(this->graph->vertexes[src]);}
    //S.push(this->vertexes.begin()->second);

    cout << "BEGIN: " << this->graph->vertexes[src]->data << endl;
    while(!S.empty()) {
        auto v = S.front();
        S.pop();
//        std::priority_queue<Vertex<TV, TE>*, std::vector<Vertex<TV, TE>*>, std::greater<typename std::vector<Vertex<TV, TE>*>::value_type>> pq;

        for (auto unions : v->edges) {
            if (visited[unions->vertexes[1]->data].first == false) {
                S.push(unions->vertexes[1]);
                visited[unions->vertexes[1]->data].first = true;
                g.createEdge(visited[unions->vertexes[0]->data].second, visited[unions->vertexes[1]->data].second, unions->weight);
            }
        }
    }

    return g;
}


#endif //GRAPH_PROJECT_GRAPH_ITEROS_BFS_H
