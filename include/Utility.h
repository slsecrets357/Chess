#include "Player.h"
#include <string.h> 

bool parseStringInput(std::string stringPos, Position oPos) {
    if (stringPos.length() != 2) {
        throw std::invalid_argument("Invalid input string");
        return false;
    }
    Position pos;
    pos.row = stringPos[0] - '1';
    pos.col = stringPos[1] - 'A';
    oPos = pos;
    return true;
}
std::string getUserInput() {
    std::string input;
    std::cout << "Enter your move: ";
    std::cin >> input;
    return input;
}