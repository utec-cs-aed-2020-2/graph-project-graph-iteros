#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

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

public:
    UnDirectedGraph();

    bool insertVertex(string id, TV vertex);

    bool createEdge(string id1, string id2, TE w);
    bool deleteVertex(string id) override;
    bool deleteEdge(string start, string end) override;

    TE &operator()(string start, string end);
    float density();
    bool isDense(float threshold = 0.5);
    bool isConnected();

    bool empty();
    void clear();

    void displayVertex(string id);
    bool findById(string id);
    void display();

    priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, compWeight<TV, TE>> getOrderedEdges();
    int getSize();
    bool isCyclic();
    bool edgeExists(string id1, string id2);
};

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::UnDirectedGraph() {this->edges = 0;}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    if (!findById(id)) {
        Vertex<TV, TE> *v = new Vertex<TV, TE>(vertex, id);
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
                // Si esto pasa significa que ya existe una arista de id1 -> id2
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
TE& UnDirectedGraph<TV, TE>::operator()(string start, string end) {
    for (auto i : this->vertexes[start]->edges) {
        if (i->vertexes[1] == this->vertexes[end]) return i->weight;
    }
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

    if (std::all_of(visited.begin(), visited.end(), [](auto x){return x.second;}))
        return true;

    return false;
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
    //TODO
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

#endif