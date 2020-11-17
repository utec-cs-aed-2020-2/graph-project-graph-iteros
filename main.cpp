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

    Prim<char, int> prim(&graph, "1");
    UnDirectedGraph<char, int> result2 = prim.apply();

    //result1.display();
    //cout << endl;
    result2.display();
    cout << endl;

    /*
     * TODO:
     * - isConnected, isStronglyConnected on DirectedGraph
     * - Prim
     * - Parser
     * - Tester
     */
    
    return EXIT_SUCCESS;
}