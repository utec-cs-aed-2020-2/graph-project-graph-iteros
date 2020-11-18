#ifndef GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
#define GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct compWeightPair {
    bool operator()(const pair<string, TE> p1, const pair<string, TE> p2) const
    {
        return p1.second < p2.second;
    }
};

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

    sort(vertexes.begin(), vertexes.end(), compWeightP<TE>);

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
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_PRIM_H
