#ifndef GRAPH_PROJECT_GRAPH_ITEROS_A_H
#define GRAPH_PROJECT_GRAPH_ITEROS_A_H

#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <cmath>
#include <algorithm>
using namespace std;

template<typename TE>
struct myComp {
    constexpr bool operator()(pair<pair<string, TE>, TE> const& a, pair<pair<string, TE>, TE> const& b)
    const noexcept {return a.second > b.second;}
};

long double toRadians(const long double degree) {
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1, long double lat2, long double long2) {
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
    long double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    long double R = 6371;
    ans = ans * R;

    return ans;
}

template<typename TV, typename TE>
struct Asterisk {
    Graph<TV, TE>* graph;
    string src;
    string dest;
    Asterisk(Graph<TV, TE>* graph, string src, string dest);
    vector<string> apply();
    void print();

    typedef pair<string, TE> p;
};

template<typename TV, typename TE>
Asterisk<TV, TE>::Asterisk(Graph<TV, TE> *graph, string src, string dest) {
    this->graph = graph;
    this->src = src;
    this->dest = dest;
}

template<typename TV, typename TE>
vector<string> Asterisk<TV, TE>::apply() {
    unordered_map<string, TE> h;
    Vertex<TV, TE>* destVertex = graph->vertexes[dest];

    //calculate heuristic of distances from every node to destiny
    for (auto i : graph->vertexes) {
        Vertex<TV, TE>* srcVertex = i.second;
        h[i.first] = distance(srcVertex->latitud, srcVertex->longitud, destVertex->latitud, destVertex->longitud);
    }

    priority_queue<pair<p, TE>, vector<pair<p, TE>>, myComp<TE>> open; //nodes to visit
    vector<string> visited; //visited nodes
    open.push(make_pair(make_pair(src, 0), 0)); //first node to visit is src
    //pair<pair<id, accumulated weight>, accumulatedweight+heuristic>

    TE accWeight = 0; //accumulated weight of taken path

    //while there are nodes to visit and the destiny hasn't been visited
    while (!open.empty() && !(find(visited.begin(), visited.end(), dest) != visited.end())) {
        auto top = open.top();
        open.pop();
        visited.push_back(top.first.first);
        Vertex<TV, TE>* v = graph->vertexes[top.first.first];

        //push adjacent nodes to prority queue
        for (auto i : v->edges) {
            //if node is not visited, add to open priorityqueue
            string id = i->vertexes[1]->key;
            if (!(find(visited.begin(), visited.end(), id) != visited.end())) {
                open.push(make_pair(make_pair(id, i->weight + top.first.second), i->weight + top.first.second + h[id]));
            }
        }
    }

    return visited;
}

template<typename TV, typename TE>
void Asterisk<TV, TE>::print() {
    vector<string> path = apply();

    cout << "Path from " << src << " to " << dest << ": " << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size()-1) cout << " -> ";
    }
    cout << endl;
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_A_H
