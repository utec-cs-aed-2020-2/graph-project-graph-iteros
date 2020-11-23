#ifndef GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H
#define GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H

#include "../Graph/Algorithms/Kruskal.h"
#include "../Graph/Algorithms/Prim.h"
#include "../Parser/parser.h"
#include <string>
#include <iostream>

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
    Parser parser;
    parser.readJSON();
    //parser.printJSON();
    UnDirectedGraph<string, double> u1graph;
    parser.uGraphMake(u1graph);

    Kruskal<string, double> dkruskal(&u1graph);
    UnDirectedGraph<string, double> result3 = dkruskal.apply();
    cout<<endl;
    result3.display();

    UnDirectedGraph<string, double> u2graph;
    parser.uGraphMake(u2graph);

    Prim<string, double> prim2(&u2graph, "2796");
    UnDirectedGraph<string, double> result4 = prim2.apply();
    cout<<endl;
    result4.display();
}

#endif //GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H
