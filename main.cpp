
#include "Tester/tester.h"


using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;

    Tester::executeExamples();


    std::cout << "================================================" << std::endl;
    std::cout << "PARSER" << std::endl;
    std::cout << "================================================" << std::endl;


    Tester::executeParser();

    return EXIT_SUCCESS;
}