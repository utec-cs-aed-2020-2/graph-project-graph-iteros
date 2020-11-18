#include "Graph/Algorithms/Kruskal.h"
#include "Graph/Algorithms/Prim.h"
#include "Tester/tester.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    
    Tester::executeExamples();
    Tester::executeParser();

    /*Graph<char, int>* g = new DirectedGraph<char, int>();
    g->insertVertex("1", 'A');
    g->insertVertex("2", 'B');
    g->insertVertex("3", 'C');
    g->insertVertex("4", 'D');

    g->createEdge("1", "2", 10);
    g->createEdge("1", "2", 12);
    g->createEdge("1", "3", 5);
    g->createEdge("3", "4", 15);
    g->createEdge("2", "4", 20);*/

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

    /*
     * TODO:
     * - Parser
     * - Tester
     */

    /*
    DirectedGraph<int, int> g;
    g.insertVertex("a", 1);
    g.insertVertex("b", 2);
    g.insertVertex("c", 3);
    //g.insertVertex("d", 4);
    //g.insertVertex("e", 5);

    g.createEdge("a", "b", 5);
    g.createEdge("b", "c", 4);
    g.createEdge("a", "c", 10);
    g.createEdge("b", "a", 9);
    g.createEdge("c", "a", 12);
    g.createEdge("c", "b", 14);

    //g.createEdge("c", "d", 3);
    //g.createEdge("d", "e", 6);

    g.display();

    cout << endl << endl;

    if (g.isConnected()) {
        cout << "is connected" << endl;
    } else {
        cout << "is not connected" << endl;
    }

    cout << endl;

    if (g.isStronglyConnected()) {
        cout << "is strongly connected" << endl;
    } else {
        cout << "is not strongly connected" << endl;
    }

     */
    return EXIT_SUCCESS;
}