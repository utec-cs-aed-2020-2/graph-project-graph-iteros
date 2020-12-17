
#include "Tester/tester.h"


using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;

    Tester::executeExamples();


    std::cout << "================================================" << std::endl;
    std::cout << "PARSER  PERU" << std::endl;
    std::cout << "================================================" << std::endl;


    Tester::executeParserPeru("../Parser/Data/pe.json");

    std::cout << "================================================" << std::endl;
    std::cout << "PARSER  MUNDO" << std::endl;
    std::cout << "================================================" << std::endl;

    Tester::executeParserMundo("../Parser/Data/airports.json");


    return EXIT_SUCCESS;
}