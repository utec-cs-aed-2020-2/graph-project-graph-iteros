#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <limits>

#define INF numeric_limits<int>::max()

template<typename TV, typename TE>
struct compWeight {
    bool operator()(const Edge<TV, TE>* e1, const Edge<TV, TE>* e2) const
    {
        return e1->weight > e2->weight;
    }
};

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
private:
    ///TODO: No sé qué quieran agregar al grafo
    char* name;
    int airportID;
    //vector<int> destinos;

public:
    UnDirectedGraph();

    bool insertVertex(string id, TV vertex, double latitud = 0, double longitud= 0);

    bool createEdge(string id1, string id2, TE w);
    bool deleteVertex(string id) override;
    bool deleteEdge(string start, string end) override;

    TE operator()(string start, string end);
    float density();
    bool isDense(float threshold = 0.5);
    bool isConnected();

    bool empty();
    void clear();

    void displayVertex(string id);
    bool findById(string id);
    void display();
    void display2();

    priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, compWeight<TV, TE>> getOrderedEdges();
    int getSize();
    bool isCyclic();
    bool isCyclicUtil(string id, pair<string, bool> visited[], string parent);
    bool edgeExists(string id1, string id2);

    pair<double,double> getPositionById(string id);

    UnDirectedGraph<TV, TE> execKruskal();
    UnDirectedGraph<TV, TE> exePrim(string start);
    bool areConnected(string id1, string id2);

    unordered_map<string, TE> ExeDijkstra(string src);
};

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::UnDirectedGraph() {this->edges = 0;}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex, double latitud, double longitud) {
    if (!findById(id)) {
        Vertex<TV, TE> *v = new Vertex<TV, TE>(vertex, id, latitud, longitud);
        this->vertexes[id] = v;
        return true;
    }

    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    if (findById(id1) && findById(id2)) {
        for (auto it : this->vertexes[id1]->edges) {
            if (it->vertexes[1]->data == this->vertexes[id2]->data)
                // Si esto pasa significa que ya existe una arista de id1 <-> id2
                return false;
        }

        Edge<TV, TE> *e1 = new Edge<TV, TE>(this->vertexes[id1], this->vertexes[id2], w);
        this->vertexes[id1]->edges.push_back(e1);
        Edge<TV, TE> *e2 = new Edge<TV, TE>(this->vertexes[id2], this->vertexes[id1], w);
        this->vertexes[id2]->edges.push_back(e2);
        this->edges++;
        return true;
    }

    return false;
    // Creo que faltaría verificar algunas cosas antes de insertar una arista
    /*
    // Para verificar que los vértices existan
    if ( this->vertexes.count(id1) + this->vertexes.count(id2) == 2  ) {

        // Para recorrer las aristas que tenga un vértice, como es no dirigido solo hace falta recorrer el de 1 ya que si está, estará en el otro y si no está, lo mismo
        for (auto it : this->vertexes[id1]->edges) {
            if (it->vertexes[1]->data == this->vertexes[id2]->data)
                // Si esto pasa significa que ya existe una arista de id1 -> id2
                return false;
        }

        // Si existen los vértices y no existe una arista entre estos, se crea
        this->vertexes[id1]->edges.push_back(new Edge<TV, TE>(this->vertexes[id1], this->vertexes[id2], w));
        this->vertexes[id2]->edges.push_back(new Edge<TV, TE>(this->vertexes[id2], this->vertexes[id1], w));
        this->edges++;
        return true;
    }

    //Si no existen los vértices no se puede crear una arista
    return false;
     */
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id) {
    if (findById(id)) {
        for (auto i : this->vertexes) {
            deleteEdge(i.first, id);
        }
        this->vertexes.erase(id);
        return true;
    }
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(string start, string end) {
    if (findById(start) && findById(end)) {
        for (auto i = this->vertexes[start]->edges.begin(); i != this->vertexes[start]->edges.end();) {
            if ((*i)->vertexes[1] == this->vertexes[end]) {
                this->vertexes[start]->edges.erase(i++);
                this->edges--;
            }
            else i++;
        }
        for (auto j = this->vertexes[end]->edges.begin(); j != this->vertexes[end]->edges.end();) {
            if ((*j)->vertexes[1] == this->vertexes[start]) {
                this->vertexes[end]->edges.erase(j++);
            }
            else j++;
        }
        return true;
    }
    return false;
}

template<typename TV, typename TE>
TE UnDirectedGraph<TV, TE>::operator()(string start, string end) {
    if(this->vertexes.count(start) == 0 || this->vertexes.count(end) == 0) return numeric_limits<TE>::min();
    for (auto i : this->vertexes[start]->edges) {
        if (i->vertexes[1] == this->vertexes[end]) return i->weight;
    }
    return numeric_limits<TE>::min();
}

template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {
    return (2.0*this->edges)/(this->vertexes.size()*(this->vertexes.size()-1));
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {
    return density() >= threshold;
}


template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected() {
    //TODO
    auto id = this->vertexes.begin()->first;
    std::unordered_map<TV, bool> visited;
    std::queue<Vertex<TV, TE>*> q;
    for (auto it : this->vertexes)
        visited[(it.second)->data] = false;

    visited[this->vertexes[id]->data] = true;

    q.push(this->vertexes[id]);
    auto u = q.front();
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto it : u->edges) {
            if (visited[(it->vertexes)[1]->data] == false) {
                q.push((it->vertexes)[1]);
                visited[(it->vertexes)[1]->data] = true;
                //std::cout <<  u->data << "<->" << (it->vertexes)[1]->data << " ";
            }
        }
    }

    return std::all_of(visited.begin(), visited.end(), [](auto x) { return x.second; });

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() {
    return this->vertexes.size() != 0;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear() {
    this->vertexes.clear();
    this->edges = 0;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id) {
    cout << this->vertexes[id]->data << "-> ";
    for (auto const& j : this->vertexes[id]->edges) {
        cout << j->vertexes[1]->data << "(" << j->weight << ")" << " ";
    }
    cout << endl;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id) {
    if (this->vertexes.find(id) == this->vertexes.end()) return false;
    return true;
}

template<typename TV, typename TE>
pair<double,double> UnDirectedGraph<TV, TE>::getPositionById(string id) {
    if (this->vertexes.find(id) == this->vertexes.end())
        return make_pair(0,0);
    //std::cout <<this-> vertexes[id]->latitud<<" "<<this-> vertexes[id]->longitud<<std::endl;
    return make_pair(this-> vertexes[id]->latitud,this-> vertexes[id]->longitud);
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display() {
    for (auto i : this->vertexes) {
        cout << i.second->data << "-> ";
        for (auto j : i.second->edges) {
            cout << j->vertexes[1]->data << "(" << j->weight << ")" << " ";
        }
        cout << endl;
    }
}

template<typename TV, typename TE>
priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, compWeight<TV, TE>> UnDirectedGraph<TV, TE>::getOrderedEdges() {
    priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, compWeight<TV, TE>> pq;
    vector<Vertex<TV, TE>*> visited;
    for (auto i : this->vertexes) {
        visited.push_back(i.second);
        for (auto j : i.second->edges) {
            if (find(visited.begin(), visited.end(), j->vertexes[1]) == visited.end())
                pq.push(j);
        }
    }
    return pq;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isCyclic() {
    pair<string, bool>* visited = new pair<string, bool>[getSize()];
    int cont = 0;
    for (auto i : this->vertexes) {
        visited[cont++] = make_pair(i.first, false);
    }

    for (int i = 0; i < getSize(); ++i) {
        if (!visited[i].second) {
            if (isCyclicUtil(visited[i].first, visited, ""))
                return true;
        }
    }

    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isCyclicUtil(string id, pair<string, bool> *visited, string parent) {
    for (int i = 0; i < getSize(); i++) {
        if (visited[i].first == id)
            visited[i].second = true;
    }

    for (auto i : this->vertexes[id]->edges) {
        Vertex<TV, TE>* vertex = i->vertexes[1];
        bool isVisited;
        for (int j = 0; j < getSize(); ++j) {
            if (visited[j].first == vertex->key)
                isVisited = visited[j].second;
        }

        if (!isVisited) {
            if (isCyclicUtil(vertex->key, visited, id))
                return true;
        }

        else if (vertex->key != parent)
            return true;
    }

    return false;
}

template<typename TV, typename TE>
int UnDirectedGraph<TV, TE>::getSize() {
    return this->vertexes.size();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::edgeExists(string id1, string id2) {
    if (findById(id2) && findById(id2)) {
        for (auto i : this->vertexes[id1]->edges) {
            if (i->vertexes[1] == this->vertexes[id2])
                return true;
        }
    }
    return false;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display2() {
    // Recorrer Vertices
    for (auto it : this->vertexes) {
        std::cout << it.first << " :\n";
        // Recorrer sus vecinos
        for (auto it2 : it.second->edges) {
            std::cout << "\t" << it2->vertexes[0]->data;
            std::cout << " <-" << it2->weight << "-> ";
            std::cout << it2->vertexes[1]->data << "(" << it2->vertexes[1]->key << ")" << "\n";
        }
    }
}

template<typename TV, typename TE>
bool operator<(const Edge<TV, TE>& edge1, const Edge<TV, TE>& edge2) {
    return edge1.weight > edge2.weight;
}


template<typename TV, typename TE>
UnDirectedGraph<TV, TE> UnDirectedGraph<TV, TE>::execKruskal() {
    std::priority_queue<Edge<TV, TE>*, std::vector<Edge<TV, TE>*>, compWeight<TV, TE>> pq;
    std::unordered_map<TV, std::pair<std::unordered_map<TV, int>, string>> visited;    // Para evitar que las aristas se marquen doble (A<->B == B<->A)
    //std::unordered_map<TV, int> ids;                                              // Para verificar las conexiones y agregar las aristas
    // Se borró el map de ids porque se usa el pair del map visited para que el second sea el id
    UnDirectedGraph<TV, TE> g;                                                      // Grafo para retornar

    for (auto it1 : this->vertexes) {
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
            g.createEdge(id1, id2, pq.top()->weight);
        }
        pq.pop();
    }

    return g;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::areConnected(string id1, string id2) {
    if (this->edges == 0 || this->vertexes.count(id1)==0 || this->vertexes.count(id2)==0)
        return false;

    auto temp = this->vertexes[id2]->data;
    std::queue<Vertex<TV, TE>*> q;
    std::unordered_map<TV, bool> visited;
    for (auto it : this->vertexes)
        visited[(it.second)->data] = false;

    visited[this->vertexes[id1]->data] = true;
    q.push(this->vertexes[id1]);
    auto u = q.front();
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto it : u->edges) {
            if ((it->vertexes)[1]->data == temp)
                return true;
            if (visited[(it->vertexes)[1]->data] == false) {
                q.push((it->vertexes)[1]);
                visited[(it->vertexes)[1]->data] = true;
            }
        }
    }

    return false;
}

template <typename TV, typename TE>
using EPair = pair<Edge<TV, TE>*, Vertex<TV, TE>*>;

template<typename TV, typename TE>
struct compPairs{
    bool operator()(const EPair<TV, TE> p1, const EPair<TV, TE> p2) const {
        return p1.first->weight > p2.first->weight;
    }
};

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> UnDirectedGraph<TV, TE>::exePrim(string start) {
    UnDirectedGraph<TV, TE> g;
    priority_queue<EPair<TV, TE>, std::vector<EPair<TV, TE>>, compPairs<TV, TE>> pq;
    unordered_map<TV, unordered_map<TV, bool>> visited;


    g.insertVertex(this->vertexes[start]->key, this->vertexes[start]->data, this->vertexes[start]->latitud, this->vertexes[start]->longitud);
    pq.push(make_pair(nullptr, this->vertexes[start]));

    for (auto x : this->vertexes) {
        for (auto y : x.second->edges) {
            if (y->vertexes[1]->key == this->vertexes[start]->key)
                visited[y->vertexes[1]->data][this->vertexes[start]->data] = true;
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
            //cout << "vertex " << i++ << ": " << v.first->vertexes[0]->key << " <- "<< v.first->weight << " -> " << v.first->vertexes[1]->key << "\n";
        }
    }

    return g;
}


template<typename TV, typename TE>
unordered_map<string, TE> UnDirectedGraph<TV, TE>::ExeDijkstra(string src) {
    /// TODO: Falta crear la tabla de parents y el grafo (si es necesario)
    // UnDirectedGraph<TV, TE> g;
    priority_queue<EPair<TV, TE>, std::vector<EPair<TV, TE>>, compPairs<TV, TE>> pq;
    unordered_map<string, TE> dist;

    for (auto it : this->vertexes) {
        dist[it.first] = INF;
    }

    dist[src] = 0;
    pq.push(make_pair(nullptr, this->vertexes[src]));

    while ( !pq.empty() ) {
        string u = pq.top().second->key;
        pq.pop();
        for (auto it : this->vertexes[u]->edges) {
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
        cout << this->vertexes[x.first]->data << ": " << x.second << endl;
    }

    return dist;
}

#endif
