#include <iostream>
#include <memory>
#include "Node.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp> // Necessario per convertire glm::mat4 in stringa

void testNodeConstructor() {
    std::cout << "=== Test Costruttore Node ===" << std::endl;
    Node node("TestNode");

    std::cout << "Tipo: TestNode" << std::endl;
    std::cout << "Posizione: " << glm::to_string(node.getPosition()) << " (Expected: (0, 0, 0))" << std::endl;
    std::cout << "Rotazione: " << glm::to_string(node.getRotation()) << " (Expected: (0, 0, 0))" << std::endl;
    std::cout << "Scala: " << glm::to_string(node.getScale()) << " (Expected: (1, 1, 1))" << std::endl;
    std::cout << "Priorità: " << node.getPriority() << " (Expected: 0)" << std::endl;
}

void testNodeSettersAndGetters() {
    std::cout << "\n=== Test Setter e Getter Node ===" << std::endl;
    Node node("TestNode");

    node.setPosition(glm::vec3(1.0f, 2.0f, 3.0f));
    node.setRotation(glm::vec3(10.0f, 20.0f, 30.0f));
    node.setScale(glm::vec3(2.0f, 2.0f, 2.0f));
    node.setPriority(5);

    std::cout << "Posizione: " << glm::to_string(node.getPosition()) << " (Expected: (1, 2, 3))" << std::endl;
    std::cout << "Rotazione: " << glm::to_string(node.getRotation()) << " (Expected: (10, 20, 30))" << std::endl;
    std::cout << "Scala: " << glm::to_string(node.getScale()) << " (Expected: (2, 2, 2))" << std::endl;
    std::cout << "Priorità: " << node.getPriority() << " (Expected: 5)" << std::endl;
}

void testLocalMatrix() {
    std::cout << "\n=== Test Matrice Locale ===" << std::endl;
    Node node("TestNode");

    node.setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    node.setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
    node.setScale(glm::vec3(1.0f, 2.0f, 1.0f));

    glm::mat4 localMatrix = node.getLocalMatrix();

    std::cout << "Local Matrix: " << glm::to_string(localMatrix) << std::endl;
}

void testChildrenManagement() {
    std::cout << "\n=== Test Gestione Nodi Figli ===" << std::endl;
    auto parent = std::make_shared<Node>("ParentNode");
    auto child1 = std::make_shared<Node>("ChildNode1");
    auto child2 = std::make_shared<Node>("ChildNode2");

    parent->addChild(child1);
    parent->addChild(child2);

    std::vector<std::shared_ptr<Node>> children = parent->getChildren();
    std::cout << "Numero di figli: " << children.size() << " (Expected: 2)" << std::endl;
    for (size_t i = 0; i < children.size(); i++) {
        std::cout << "Child " << i + 1 << " Type: " << children[i]->getType() << std::endl;
    }
}

void testNode() {
    testNodeConstructor();
    testNodeSettersAndGetters();
    testLocalMatrix();
    testChildrenManagement();

}
