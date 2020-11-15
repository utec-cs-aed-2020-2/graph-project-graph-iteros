#include <iostream>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"

//#include "Tester/tester.h"
//#include "Parser/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    
    //Tester::executeExamples();
    //Tester::executeParser();
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

    g->display();
    cout << endl;

    g->displayVertex("3");
    cout << endl;

    //g->deleteVertex("2");
    //g->deleteEdge("1", "2");
    //g->display();

    cout << g->operator()("2", "4") << endl;
    
    return EXIT_SUCCESS;
}