//
// Created by jlr on 12/16/20.
//

#ifndef GRAPH_PROJECT_GRAPH_ITEROS_SCC_H
#define GRAPH_PROJECT_GRAPH_ITEROS_SCC_H

#include "../DirectedGraph.h"

template<typename TV, typename TE>
struct SCC {
    DirectedGraph<TV, TE> *graph;
    SCC(DirectedGraph<TV, TE> *graph);
    bool apply();
};


template<typename TV, typename TE>
SCC<TV, TE>::SCC(DirectedGraph<TV, TE> *_graph_) {
    this->graph = _graph_;
}

template<typename TV, typename TE>
bool SCC<TV, TE>::apply() {
    // Para que sea fuertemente conectado debe tener camino entre cualquier par de vértices
    int comp = 0;
    for(auto iter : this->graph->vertexes) {
        auto id = iter.first;
        std::unordered_map<TV, bool> visited;
        std::queue<Vertex<TV, TE>*> q;
        for (auto it : this->graph->vertexes)
            visited[(it.second)->data] = false;
        visited[this->graph->vertexes[id]->data] = true;
        q.push(this->graph->vertexes[id]);
        auto u = q.front();
        q.push(u);
        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (auto it : u->edges) {
                if (visited[(it->vertexes)[1]->data] == false) {
                    q.push((it->vertexes)[1]);
                    visited[(it->vertexes)[1]->data] = true;
                }
            }
        }

        for (auto x : visited) {
            if (!x.second)
                return false;
        }

        comp++;
    }

    return comp == this->graph->vertexes.size();
}



#endif //GRAPH_PROJECT_GRAPH_ITEROS_SCC_H
