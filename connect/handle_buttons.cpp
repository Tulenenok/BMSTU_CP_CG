#include <iostream>
#include "handle_buttons.h"

int handleButton(cmd_t command) {
    if (command == LOAD)
        std::cout << "LOAD\n";
    else if (command == DRAW)
        std::cout << "DRAW\n";
    else if (command == ADD_LIGHT)
        std::cout << "ADD\n";
    else
        std::cout << "ERROR\n";

    return 0;
}