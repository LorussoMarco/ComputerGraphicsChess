#include "engine.h"
#include <GL/freeglut.h>
#include <iostream>

struct Eng::Base::Reserved {
    bool initFlag;
    int windowID;
    Reserved() : initFlag{ false }, windowID{ -1 } {}
};

// Singleton instance
Eng::Base& Eng::Base::getInstance() {
    static Base instance;
    return instance;
}

// Constructor
Eng::Base::Base() : reserved(std::make_unique<Reserved>()), running(false) {}

// Destructor
Eng::Base::~Base() {
    free();
}

// Init function
bool Eng::Base::init(const char* windowTitle, int width, int height) {
    if (reserved->initFlag) {
        std::cerr << "ERROR: Engine already initialized!" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    int argc = 1;
    char* argv[] = { const_cast<char*>("") };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    reserved->windowID = glutCreateWindow(windowTitle);

    if (reserved->windowID < 1) {
        std::cerr << "ERROR: Unable to create window!" << std::endl;
        return false;
    }

    running = true;
    reserved->initFlag = true;
    std::cout << "[>] Engine initialized with window: " << windowTitle << std::endl;
    return true;
}

// Free function
bool Eng::Base::free() {
    if (!reserved->initFlag) {
        std::cerr << "ERROR: Engine not initialized!" << std::endl;
        return false;
    }

    glutDestroyWindow(reserved->windowID);
    reserved->initFlag = false;
    running = false;

    std::cout << "[<] Engine deinitialized" << std::endl;
    return true;
}

// Set callbacks
void Eng::Base::setKeyboardCallback(void (*callback)(unsigned char, int, int)) {
    glutKeyboardFunc(callback);
}

void Eng::Base::setDisplayCallback(void (*callback)()) {
    glutDisplayFunc(callback);
}

void Eng::Base::setReshapeCallback(void (*callback)(int, int)) {
    glutReshapeFunc(callback);
}

// Rendering utilities
void Eng::Base::clearWindow() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Eng::Base::swapBuffers() {
    glutSwapBuffers();
}

void Eng::Base::setBackgroundColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}

// Status
bool Eng::Base::isRunning() const {
    return running;
}
