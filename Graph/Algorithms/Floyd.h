#ifndef GRAPH_PROJECT_GRAPH_ITEROS_FLOYD_H
#define GRAPH_PROJECT_GRAPH_ITEROS_FLOYD_H

#include "../UndirectedGraph.h"

template<typename TV, typename TE>
struct Floyd {
    UnDirectedGraph<TV, TE> *graph;
    std::unordered_map<TV, int> indexes;
    vector<vector<TE>> adjMatrix;
    int size;

    Floyd(UnDirectedGraph<TV, TE> *graph);
    void apply();
    void print();
    TE distance(TV, TV);
};

template<typename TV, typename TE>
Floyd<TV, TE>::Floyd(UnDirectedGraph<TV, TE> *graph){
    this->size = graph->vertexes.size();
    int pos = 0;
    // mapeando posiciones de nodos para adjMatrix
    for(auto v : graph->vertexes){
        this->indexes[v.first] = pos;
        //indexes[id] = pos
        pos++;
    }
    // inicializar size e infs
    for(int i = 0; i < this->size; i++){
        vector<TE> temp;
        adjMatrix.push_back(temp);
        for(int j = 0; j < this->size; j++){
            adjMatrix[i].push_back(numeric_limits<double>::max());
        }
    }

    // llenando adjMatrix
    for(auto v : graph->vertexes){
        // posición de v1 y v2 (vértices conectados)
        int p1 = this->indexes[v.first]; // vértice actual
        for(auto e : v.second->edges){
            int p2 = this->indexes[e->vertexes[1]->key]; // vertex de llegada
            this->adjMatrix[p1][p2] = e->weight;
            this->adjMatrix[p2][p1] = e->weight;
        }
    }

    this->apply();
}

template<typename TV, typename TE>
void Floyd<TV, TE>::print(){
    for(auto v:this->indexes){cout<<v.first<<" "<<v.second<<" ____ ";}
    cout<<endl;
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            std::cout << this->adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename TV, typename TE>
void Floyd<TV, TE>::apply() {
 for (int i = 0; i < this->size; i++)
        this->adjMatrix[i][i] = 0;

    for (int k = 0; k < this->size; k++)
        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++) {
                TE dt = this->adjMatrix[i][k] + this->adjMatrix[k][j];
                if (this->adjMatrix[i][j] > dt)
                    this->adjMatrix[i][j] = dt;
            }
}

//distancia entre dos vértices cualesquiera
template <typename  TV, typename  TE>
TE Floyd<TV, TE>::distance(TV v1, TV v2){
    int p1 = this->indexes[v1];
    int p2 = this->indexes[v2];

    return this->adjMatrix[p1][p2];
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_FLOYD_H
