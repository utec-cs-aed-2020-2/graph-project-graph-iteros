#ifndef GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H
#define GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct Kruskal {
    UnDirectedGraph<TV, TE> *graph;
    Kruskal(UnDirectedGraph<TV, TE> *graph);
    UnDirectedGraph<TV, TE> apply();
};

template<typename TV, typename TE>
Kruskal<TV, TE>::Kruskal(UnDirectedGraph<TV, TE> *_graph_) {
    this->graph = _graph_;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Kruskal<TV, TE>::apply() {
    /*
    UnDirectedGraph<TV, TE> g;
    auto pq = graph->getOrderedEdges();

    while (g.getSize() < graph->getSize() && !pq.empty()) {
        Edge<TV, TE>* e = pq.top();
        pq.pop();

        bool insert1 = g.insertVertex(e->vertexes[0]->key, e->vertexes[0]->data);
        bool insert2 = g.insertVertex(e->vertexes[1]->key, e->vertexes[1]->data);
        g.createEdge(e->vertexes[0]->key, e->vertexes[1]->key, e->weight);

        if (g.isCyclic()) {
            g.deleteEdge(e->vertexes[0]->key, e->vertexes[1]->key);
            if (insert1) g.deleteVertex(e->vertexes[0]->key);
            if (insert2) g.deleteVertex(e->vertexes[1]->key);
        }
    }

    return g;
    */

    std::priority_queue<Edge<TV, TE>*, std::vector<Edge<TV, TE>*>, compWeight<TV, TE>> pq;
     std::unordered_map<TV, std::pair<std::unordered_map<TV, int>, string>> visited;      // Para evitar que las aristas se marquen doble (A<->B == B<->A)
    //std::unordered_map<TV, int> ids;                                                      // Para verificar las conexiones y agregar las aristas
    // Se borró el map de ids por el pair del map visited para que el second sea el id
    UnDirectedGraph<TV, TE> g;                                                              // Grafo para retornar

    for (auto it1 : graph->vertexes) {
        g.insertVertex(it1.first , (it1.second)->data);
        //ids[it1.second->data] = it1.first;
        visited[it1.second->data].second = it1.first;
        for (auto it2 : (it1.second)->edges) {
            if (visited[it1.second->data].first.count(it2->vertexes[1]->data) == 0 && visited[it2->vertexes[1]->data].first.count(it1.second->data) == 0) {
                pq.push(it2);
                (visited[it1.second->data].first)[it2->vertexes[1]->data] = 1;
                (visited[it2->vertexes[1]->data].first)[it1.second->data] = 1;
            }
        }
    }

    while (!pq.empty()) {
        string id1 = visited[pq.top()->vertexes[0]->data].second;
        string id2 = visited[pq.top()->vertexes[1]->data].second;
        if (!g.areConnected(id1, id2)) {
            // std::cout << pq.top().vertexes[0]->data << "<-" << pq.top().weight << "->" << pq.top().vertexes[1]->data << std::endl;
            g.createEdge(id1, id2, pq.top()->weight);
        }
        pq.pop();
    }

    return g;

}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_KRUSKAL_H
