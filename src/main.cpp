#include <SFML/Graphics.hpp>
#include "Controller.h"
#include <iostream>

int main()
{
    Controller controller;
    try {
        controller.run();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    return EXIT_SUCCESS;
}
