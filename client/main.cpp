/**
 * @file        main.cpp
 * @brief       Client application (that uses the graphics engine)
 */

 // Library headers
#include "engine.h"
#include "Node.h"
#include "Object.h"
#include <iostream>
#include <memory>

int main() {
    auto& engine = Eng::Base::getInstance();

    if (!engine.init("Scene with Cubes", 800, 600)) {
        return -1;
    }

    auto rootNode = std::make_shared<Node>();

    auto cube1 = std::make_shared<Object>();
    cube1->setPosition(0.0f, 0.0f, -5.0f);
    rootNode->addChild(cube1);

    auto cube2 = std::make_shared<Object>();
    cube2->setPosition(-2.0f, 0.0f, -5.0f);
    cube2->setScale(0.8f, 0.8f, 0.8f);
    rootNode->addChild(cube2);

    auto cube3 = std::make_shared<Object>();
    cube3->setPosition(2.0f, 0.0f, -5.0f);
    cube3->setScale(0.5f, 0.5f, 0.5f);
    rootNode->addChild(cube3);

    engine.setDisplayCallback([&engine, rootNode]() {
        engine.clearWindow();
        rootNode->draw(glm::mat4(1.0f));
        engine.swapBuffers();
        });

    engine.run();

    std::cout << "Rendering completed!" << std::endl;
    return 0;
}
