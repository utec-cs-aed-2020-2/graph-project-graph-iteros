#ifndef GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H
#define GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H

#include "../Graph/Algorithms/Kruskal.h"
#include "../Graph/Algorithms/Prim.h"
#include "../Graph/Algorithms/Dijkstra.h"
#include "../Graph/Algorithms/DFS.h"
#include "../Graph/Algorithms/BFS.h"
#include "../Graph/Algorithms/Floyd.h"
#include "../Graph/Algorithms/BF.h"
#include "../Graph/Algorithms/A.h"
#include "../Graph/Algorithms/SCC.h"
#include "../Parser/parser.h"
#include <string>
#include <iostream>

using namespace rapidjson;
struct Tester {
    static void executeExamples();
    static void executeParserPeru(string);
    static void executeParserMundo(string);
};

void Tester::executeExamples() {
    cout << "Directed Graph: " << endl;

    DirectedGraph<char, int> graph1;
    graph1.insertVertex("1", 'A');
    graph1.insertVertex("2", 'B');
    graph1.insertVertex("3", 'C');
    graph1.insertVertex("4", 'D');
    graph1.insertVertex("5", 'E');

    graph1.createEdge("1", "2", 10);
    graph1.createEdge("1", "3", 5);
    graph1.createEdge("3", "4", 15);
    graph1.createEdge("2", "4", 20);
    graph1.createEdge("1", "4", 12);
    graph1.createEdge("2", "5", 25);
    graph1.createEdge("4", "5", 30);

    graph1.display(); cout << endl;
    cout << "Density: " << graph1.density() << endl;

    cout << "Is the graph dense? ";
    if (graph1.isDense(0.6)) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is the graph connected? ";
    if (graph1.isConnected()) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is vertex 3 on the graph? ";
    if (graph1.findById("3")) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Vertex 3: ";
    graph1.displayVertex("3");

    cout << endl;

    cout << "Undirected Graph: " << endl;

    UnDirectedGraph<char, int> graph2;
    graph2.insertVertex("1", 'A');
    graph2.insertVertex("2", 'B');
    graph2.insertVertex("3", 'C');
    graph2.insertVertex("4", 'D');
    graph2.insertVertex("5", 'E');

    graph2.createEdge("1", "2", 10);
    graph2.createEdge("1", "3", 5);
    graph2.createEdge("3", "4", 15);
    graph2.createEdge("2", "4", 20);
    graph2.createEdge("1", "4", 12);
    graph2.createEdge("2", "5", 25);
    graph2.createEdge("4", "5", 30);

    graph2.display(); cout << endl;
    cout << "Density: " << graph2.density() << endl;

    cout << "Is the graph dense? ";
    if (graph2.isDense(0.6)) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is the graph connected? ";
    if (graph2.isConnected()) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Is vertex 5 on the graph? ";
    if (graph2.findById("5")) cout << "Yes." << endl;
    else cout << "No." << endl;

    cout << "Vertex 5: ";
    graph2.displayVertex("5");

    cout << endl;

    Kruskal<char, int> kruskal(&graph2);
    UnDirectedGraph<char, int> result1 = kruskal.apply();

    Prim<char, int> prim(&graph2, "3");
    UnDirectedGraph<char, int> result2 = prim.apply();

    BFS<char, int> bfs(&graph2);
    auto g2=bfs.apply("4");
    g2.display();

    result1.display();
    cout << endl;
    result2.display();
    cout << endl;

    cout << "\n-----------------StronglyConnectedComponent-------------\n";
    DirectedGraph<int, int> dg;
    dg.insertVertex("1", 1);
    dg.insertVertex("2", 2);
    dg.insertVertex("3", 3);
    dg.insertVertex("4", 4);
    dg.insertVertex("5", 5);

    dg.createEdge("1", "2", 4);
    dg.createEdge("1", "3", 3);
    dg.createEdge("3", "1", 1);
    dg.createEdge("2", "1", 7);
    dg.createEdge("4", "5", 3);
    dg.createEdge("1", "5", 10);
    dg.createEdge("5", "4", 8);

    SCC<int, int> scc(&dg);
    scc.apply();
}

void Tester::executeParserPeru(string path) {
    Parser parser,parser2;
    parser.readJSON(path);
    parser2.readJSON(path);
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

    Kruskal<string, double> kruskal(&u1graph2);
    UnDirectedGraph<string, double> result3 = kruskal.apply();

    //cout<<endl;
    result3.display();

    UnDirectedGraph<string, double> u2graph;
    parser.uGraphMake(u2graph);

    cout << endl <<"Probando Prim" << endl;
    Prim<string, double> prim(&u2graph, "2796");
    UnDirectedGraph<string, double> result4 = prim.apply();
    cout<<endl;
    result4.display();

    cout<<"\nDFS:\n";
    DFS<string, double> dfs(&u2graph, "2806");
    auto m = dfs.apply();
    m.display();

    cout<<"\nBFS:\n";
    BFS<string, double> bfs(&u2graph);
    auto g=bfs.apply("2806");
    g.display();

    cout<<"\nDijkstra:\n";
    Dijkstra<string, double> Djks(&u2graph, "2796");
    Djks.apply();

    cout << "FLOYD TESTS: \n";
    Floyd<string, double> floyd(&u2graph);
    //floyd.print(); //imprime la matriz de adyacencia
    cout<<"Distancia entre 2812 y 2789: "<<floyd.distance("2812","2807");
    cout<<endl;
    cout<<"PATH:   ";
    floyd.showpath("2812","2807");
    cout<<endl;

    cout << "\nBellman-Ford test: \n";
    BF<string, double> bf(&u2graph, "2796");
    bf.print();

    cout << "\nA* test: \n";
    Asterisk<string, double> a(&u2graph, "2812","2807");
    a.print();


}

void Tester::executeParserMundo(string path) {
    Parser parser,parser2;
    parser.readJSON(path);
    parser2.readJSON(path);
    DirectedGraph<string, double> d1graph;
    parser.dGraphMake(d1graph);

    cout<<"Probando Métodos:"<<endl;
    // probando operador ()
    auto A = d1graph("2662","1194");
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

    Kruskal<string, double> kruskal(&u1graph2);
    UnDirectedGraph<string, double> result3 = kruskal.apply();

    //cout<<endl;
    //result3.display();

    UnDirectedGraph<string, double> u2graph;
    parser.uGraphMake(u2graph);

    cout << endl <<"Probando Prim" << endl;
    Prim<string, double> prim(&u2graph, "2662");
    UnDirectedGraph<string, double> result4 = prim.apply();
    cout<<endl;
    //result4.display();

    cout<<"\nDFS:\n";
    DFS<string, double> dfs(&u2graph, "2662");
    auto m = dfs.apply();
    //m.display();

    cout<<"\nBFS:\n";
    BFS<string, double> bfs(&u2graph);
    auto g=bfs.apply("2662");
    //g.display();

    cout<<"\nDijkstra:\n";
    Dijkstra<string, double> Djks(&u2graph, "2662");
    Djks.apply();

    cout << "FLOYD TESTS: (DESCOMENTAR EN tester.h PARA EJECUTAR, 12mins aprox.)\n";
    /*
    Floyd<string, double> floyd(&u2graph);
    cout<<"Distancia entre 2662(Chile-La Florida) y 1194(Bulgaria-Sofia): "<<floyd.distance("2662","1194");
    cout<<endl;
    cout<<"PATH:   ";
    floyd.showpath("2662","1194");
    cout<<endl;
    */

    cout << "\nBellman-Ford test: \n";
    BF<string, double> bf(&u2graph, "2662");
    bf.print();

    cout << "\nA* test: \n";
    Asterisk<string, double> a(&u2graph, "2662","1194");
    a.print();

}


#endif //GRAPH_PROJECT_GRAPH_ITEROS_TESTER_H
