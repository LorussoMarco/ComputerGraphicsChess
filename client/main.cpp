/**
 * @file        main.cpp
 * @brief       Client application (that uses the graphics engine)
 *
 * @author
 */

 //////////////
 // #INCLUDE //
 //////////////

 // Library header:
#include "engine.h"

// C/C++:
#include <iostream>

//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
#include "engine.h"

int main() {
    auto& engine = Eng::Base::getInstance();

    if (!engine.init("My Engine Window", 800, 600)) {
        return -1;
    }

    // Corretto: cattura `engine` per riferimento [&]
    engine.setDisplayCallback([&engine]() {
        engine.clearWindow();
        // Logica di rendering
        engine.swapBuffers();
        });

    // Corretto: cattura `engine` per riferimento [&]
    engine.setKeyboardCallback([&engine](unsigned char key, int, int) {
        if (key == 27) { // ESC per uscire
            engine.free();
        }
        });

    // Corretto: cattura `engine` per riferimento [&]
    engine.setReshapeCallback([&engine](int width, int height) {
        engine.resizeViewport(width, height);
        });

    engine.run();
    return 0;
}
