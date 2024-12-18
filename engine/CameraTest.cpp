#include <iostream>
#include "Camera.h"

void testCameraConstructor() {
    Camera camera("TestNode");
    std::cout << "Test Costruttore: " << std::endl;
    std::cout << "FOV: " << camera.getFov() << " (Expected: 90.0)" << std::endl;
    std::cout << "Near Clipping: " << camera.getNearClipping() << " (Expected: 0.01)" << std::endl;
    std::cout << "Far Clipping: " << camera.getFarClipping() << " (Expected: 1000.0)" << std::endl;
    std::cout << "Window Size: " << camera.getWindowWidth() << " x " << camera.getWindowHeight() << " (Expected: 0 x 0)" << std::endl;
    std::cout << "Is Active: " << camera.isActive() << " (Expected: 0)" << std::endl;
    std::cout << "Priority: " << camera.getPriority() << " (Expected: 2)" << std::endl;
    std::cout << "=========================" << std::endl;
}

void testSettersAndGetters() {
    Camera camera("TestNode");

    camera.setFov(75.0f);
    camera.setNearClipping(0.1f);
    camera.setFarClipping(500.0f);
    camera.setWindowSize(1920, 1080);
    camera.setActive(true);

    std::cout << "Test Setters e Getters: " << std::endl;
    std::cout << "FOV: " << camera.getFov() << " (Expected: 75.0)" << std::endl;
    std::cout << "Near Clipping: " << camera.getNearClipping() << " (Expected: 0.1)" << std::endl;
    std::cout << "Far Clipping: " << camera.getFarClipping() << " (Expected: 500.0)" << std::endl;
    std::cout << "Window Size: " << camera.getWindowWidth() << " x " << camera.getWindowHeight() << " (Expected: 1920 x 1080)" << std::endl;
    std::cout << "Is Active: " << camera.isActive() << " (Expected: 1)" << std::endl;
    std::cout << "=========================" << std::endl;
}

void testInverseMatrix() {
    Camera camera("TestNode");
    glm::mat4 matrix = camera.getInverseMatrix();

    std::cout << "Test Matrice Inversa: " << std::endl;
    std::cout << "Inverse Matrix: " << glm::to_string(matrix) << std::endl;
    std::cout << "=========================" << std::endl;
}

int main() {
    testCameraConstructor();
    testSettersAndGetters();
    testInverseMatrix();

    return 0;
}
