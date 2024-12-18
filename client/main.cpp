/**
 * @file        main.cpp
 * @brief       Client application (that uses the graphics engine)
 */

 // Library headers
#include "Engine.h"
#include <iostream>
#include <memory>

int main() {
    auto& Engine = Eng::Base::getInstance();

    if (!Engine.init("Scene with Cubes", 800, 600)) {
        return -1;
    }

    std::cout << "Rendering completed!" << std::endl;
    return 0;
}
