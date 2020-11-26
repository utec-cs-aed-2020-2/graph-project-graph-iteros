#ifndef GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
#define GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H

#include "../UndirectedGraph.h"

template<typename TE>
bool compWeightP(pair<string, TE> p1, pair<string, TE> p2) {
    TE temp1 = p1.second;
    TE temp2 = p2.second;
    if (temp1 == -1) {
        temp1 = temp2 + 1;
    }
    else if (temp2 == -1) {
        temp2 = temp1 + 1;
    }
    return temp1 > temp2;
}

template<typename TV, typename TE>
struct Prim {
    UnDirectedGraph<TV, TE> *graph;
    string start;
    Prim(UnDirectedGraph<TV, TE> *graph, const string& start);
    UnDirectedGraph<TV, TE> apply();
};

template<typename TV, typename TE>
Prim<TV, TE>::Prim(UnDirectedGraph<TV, TE> *graph, const string& start) {
    if (!graph->findById(start)) throw invalid_argument("vertex is not on graph");

    this->graph = graph;
    this->start = start;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> Prim<TV, TE>::apply() {
    /*
    UnDirectedGraph<TV, TE> g;
    vector<pair<string, TE>> distance;
    vector<pair<string, string>> parent;
    vector<pair<string, TE>> vertexes;

    for (auto i : graph->vertexes) {
        if (i.first == start) {
            vertexes.push_back(make_pair(i.first, 0)); // distance = 0
            distance.push_back(make_pair(i.first, 0));
        }
        else {
            vertexes.push_back(make_pair(i.first, -1)); // distance = INF
            distance.push_back(make_pair(i.first, -1));
        }
        parent.push_back(make_pair(i.first, "")); // parent = NULL
    }
    cout << "aqui\n";
    sort(vertexes.begin(), vertexes.end(), &compWeightP<TE>);
    cout << "aqui2\n";
    while (!vertexes.empty()) {
        pair<string, TE> elem = vertexes[vertexes.size()-1];
        Vertex<TV, TE>* vertex = graph->vertexes[elem.first];
        vertexes.pop_back();

        g.insertVertex(vertex->key, vertex->data);

        for (auto i : vertex->edges) {
            string adj = i->vertexes[1]->key;

            //check if element is in vertexes and get its index
            bool isVisited = true;
            int idxV;
            for (int j = 0; j < vertexes.size(); ++j) {
                if (vertexes[j].first == adj) {
                    isVisited = false;
                    idxV = j;
                    break;
                }
            }

            //get element index on distance and parent vectors
            int idx;
            for (int j = 0; j < distance.size(); ++j) {
                if (distance[j].first == adj) {
                    idx = j;
                    break;
                }
            }

            //check if distance[idx].second > edge weight
            bool higher;
            if (distance[idx].second == -1) higher = true;
            else higher = (distance[idx].second > i->weight);

            //if conditions met, update vectors
            if (!isVisited && higher) {
                parent[idx].second = vertex->key;
                distance[idx].second = i->weight;
                vertexes[idxV].second = i->weight;
                sort(vertexes.begin(), vertexes.end(), compWeightP<TE>);
            }
        }
    }

    //creating edges from distance and parent vectors
    for (int i = 0; i < distance.size(); ++i) {
        string id1 = parent[i].first;
        string id2 = parent[i].second;
        TE weight = distance[i].second;
        g.createEdge(id1, id2, weight);
    }

    return g;
     */
    UnDirectedGraph<TV, TE> g;
    priority_queue<EPair<TV, TE>, std::vector<EPair<TV, TE>>, compPairs<TV, TE>> pq;
    unordered_map<TV, unordered_map<TV, bool>> visited;


    g.insertVertex(graph->vertexes[start]->key, graph->vertexes[start]->data, graph->vertexes[start]->latitud, graph->vertexes[start]->longitud);
    pq.push(make_pair(nullptr, graph->vertexes[start]));

    for (auto x : graph->vertexes) {
        for (auto y : x.second->edges) {
            if (y->vertexes[1]->key == graph->vertexes[start]->key)
                visited[y->vertexes[1]->data][graph->vertexes[start]->data] = true;
        }
    }

    int i=1;
    while (!pq.empty()) {
        auto u = pq.top();
        pq.pop();
        for (auto x : u.second->edges) {
            if (visited[u.second->data].count(x->vertexes[1]->data) == 0 && visited[x->vertexes[1]->data].count(u.second->data) == 0) {
                pq.push(make_pair(x, x->vertexes[1]));
                visited[u.second->data][x->vertexes[1]->data] = true;
                visited[x->vertexes[1]->data][u.second->data] = true;
                // g.insertVertex(x->vertexes[1]->key, x->vertexes[1]->data, x->vertexes[1]->latitud, x->vertexes[1]->longitud);
                // cout << "vertex " << i++ << ": " << x->vertexes[0]->data << " <- "<< x->weight << " -> " << x->vertexes[1]->data << "\n";
            }
        }

        if (!pq.empty() && !g.areConnected(pq.top().first->vertexes[0]->key, pq.top().first->vertexes[1]->key)) {
            auto v = pq.top();
            g.insertVertex(v.second->key, v.second->data, v.second->latitud, v.second->longitud);
            g.createEdge(v.first->vertexes[0]->key, v.first->vertexes[1]->key, v.first->weight);
            cout << "vertex " << i++ << ": " << v.first->vertexes[0]->key << " <- "<< v.first->weight << " -> " << v.first->vertexes[1]->key << "\n";
        }
    }

    return g;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
