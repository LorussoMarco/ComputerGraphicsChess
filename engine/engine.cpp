#include "Engine.h"
#include <GL/freeglut.h>
#include <iostream>
#include <functional>
#include <memory>

// Reserved structure for internal use
struct Eng::Base::Reserved {
    bool initFlag;
    int windowID;

    // Callbacks
    std::function<void()> displayCallback;
    std::function<void(unsigned char, int, int)> keyboardCallback;
    std::function<void(int, int)> reshapeCallback;

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

    // Initialize FreeGLUT
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

    // Configure OpenGL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Mark as initialized
    reserved->initFlag = true;
    running = true;

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
    reserved->windowID = -1;
    reserved->initFlag = false;
    running = false;

    std::cout << "[<] Engine deinitialized." << std::endl;
    return true;
}

// Run main loop
void Eng::Base::run() {
    if (!reserved->initFlag) {
        std::cerr << "ERROR: Engine not initialized!" << std::endl;
        return;
    }
    glutMainLoop();
}

// Set display callback
void Eng::Base::setDisplayCallback(std::function<void()> callback) {
    reserved->displayCallback = std::move(callback);
    glutDisplayFunc([]() {
        Eng::Base::getInstance().reserved->displayCallback();
        });
}

// Set keyboard callback
void Eng::Base::setKeyboardCallback(std::function<void(unsigned char, int, int)> callback) {
    reserved->keyboardCallback = std::move(callback);
    glutKeyboardFunc([](unsigned char key, int x, int y) {
        Eng::Base::getInstance().reserved->keyboardCallback(key, x, y);
        });
}

// Set reshape callback
void Eng::Base::setReshapeCallback(std::function<void(int, int)> callback) {
    reserved->reshapeCallback = std::move(callback);
    glutReshapeFunc([](int width, int height) {
        Eng::Base::getInstance().reserved->reshapeCallback(width, height);
        });
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

// Resize viewport
void Eng::Base::resizeViewport(int width, int height) {
    if (height == 0) height = 1; // Prevent division by zero
    float aspect = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
