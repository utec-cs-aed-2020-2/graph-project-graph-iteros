#ifndef GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H
#define GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H

#include "../Graph/Algorithms/Kruskal.h"
#include "../Graph/Algorithms/Prim.h"
#include "../Parser/parser.h"
#include <string>
#include <iostream>

using namespace rapidjson;
struct Tester {
    static void executeExamples();
    static void executeParser();
};

void Tester::executeExamples() {
    Graph<char, int>* g = new DirectedGraph<char, int>();
    g->insertVertex("1", 'A');
    g->insertVertex("2", 'B');
    g->insertVertex("3", 'C');
    g->insertVertex("4", 'D');

    g->createEdge("1", "2", 10);
    g->createEdge("1", "2", 12);
    g->createEdge("1", "3", 5);
    g->createEdge("3", "4", 15);
    g->createEdge("2", "4", 20);

    UnDirectedGraph<char, int> graph;
    graph.insertVertex("1", 'A');
    graph.insertVertex("2", 'B');
    graph.insertVertex("3", 'C');
    graph.insertVertex("4", 'D');

    graph.createEdge("1", "2", 10);
    graph.createEdge("1", "2", 12);
    graph.createEdge("1", "3", 5);
    graph.createEdge("3", "4", 15);
    graph.createEdge("2", "4", 20);
    graph.createEdge("2", "3", 14);

    graph.display();
    cout << endl;

    Kruskal<char, int> kruskal(&graph);
    UnDirectedGraph<char, int> result1 = kruskal.apply();

    Prim<char, int> prim(&graph, "3");
    UnDirectedGraph<char, int> result2 = prim.apply();

    result1.display();
    cout << endl;
    result2.display();
    cout << endl;
}

void Tester::executeParser() {
    Parser parser,parser2;
    parser.readJSON();
    parser2.readJSON();
    //parser.printJSON();
    DirectedGraph<string, double> d1graph;
    parser.dGraphMake(d1graph);

    cout<<"Probando Métodos:"<<endl;
    // probando operador ()
    auto A = d1graph("2808","2812");
    cout<<"Operador (): "<<A<<endl;

    // probando densidad
    float D = d1graph.density();
    cout<<"Densidad: "<<D<<endl;


    // probando isDense, isConnected, empty
    bool dense = d1graph.isDense();
    if(dense) {cout << "Dense!" << endl;} else {cout << "No Dense!" << endl;}
    bool connected = d1graph.isConnected();
    if(connected) {cout << "Connected!" << endl;} else {cout << "No Connected!" << endl;}
    bool stronglyConnected = d1graph.isStronglyConnected();
    if(stronglyConnected) {cout << "Is Strongly Connected!" << endl;} else {cout << "No Connected!" << endl;}
    bool empty = d1graph.empty();
    if(empty) {cout << "Empty !" << endl;} else {cout << "No Empty!" << endl;}

    cout<<endl;cout<<endl;
    cout<<"Probando Kruskal: "<<endl;
    UnDirectedGraph<string, double> u1graph2;
    parser2.uGraphMake(u1graph2);

    //Kruskal<string, double> kruskal(&u1graph2);
    //UnDirectedGraph<string, double> result3 = kruskal.apply();

    //d1graph.clear();
    //d1graph.display();

    //cout<<endl;
    //result3.display();

    UnDirectedGraph<string, double> u2graph;
    parser.uGraphMake(u2graph);

    cout << endl <<"Probando Prim" << endl;
    // Prim<string, double> prim(&u2graph, "2796");
    // UnDirectedGraph<string, double> result4 = prim.apply();
    cout<<endl;
    // result4.display();

    u2graph.ExeDijkstra("2796");
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H
