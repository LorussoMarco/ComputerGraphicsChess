#include <iostream>
#include <memory>
#include "List.h"
#include "Node.h"

// Classe fittizia per il test che estende Node
class TestNode : public Node {
public:
    TestNode(const std::string& type, int priority) : Node(type) {
        setPriority(priority);
    }

    // Implementazione del metodo virtuale render
    void render(const glm::mat4 viewMatrix) const override {
        std::cout << "Render del Nodo: " << getType() << " | Priorità: " << getPriority() << std::endl;
    }
};

void testPassFunction() {
    std::cout << "\n=== Test pass() ===" << std::endl;

    // Creazione del nodo radice e dei nodi figli
    auto root = std::make_shared<TestNode>("Root", 1);
    auto child1 = std::make_shared<TestNode>("Child1", 3);
    auto child2 = std::make_shared<TestNode>("Child2", 2);

    root->addChild(child1);
    root->addChild(child2);

    // Chiamata a pass per ottenere la lista
    glm::mat4 identityMatrix(1.0f);
    auto renderList = List::pass(root, identityMatrix);

    std::cout << "Elementi nella lista di rendering: " << renderList.size() << " (Expected: 3)" << std::endl;
    for (const auto& pair : renderList) {
        std::cout << "Nodo: " << pair.first->getType() << " | Priorità: " << pair.first->getPriority() << std::endl;
    }
}

void testSortListRendering() {
    std::cout << "\n=== Test sortListRendering() ===" << std::endl;

    List renderListManager;

    // Creazione di nodi con diverse priorità
    auto node1 = std::make_shared<TestNode>("Node1", 1);
    auto node2 = std::make_shared<TestNode>("Node2", 3);
    auto node3 = std::make_shared<TestNode>("Node3", 2);

    // Aggiunta di nodi alla lista
    std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> renderList = {
        {node1, glm::mat4(1.0f)},
        {node2, glm::mat4(1.0f)},
        {node3, glm::mat4(1.0f)}
    };

    renderListManager.setListRendering(renderList);

    // Ordinamento della lista
    renderListManager.sortListRendering();

    // Stampa della lista ordinata
    auto sortedList = renderListManager.getListRendering();
    for (const auto& pair : sortedList) {
        std::cout << "Nodo: " << pair.first->getType() << " | Priorità: " << pair.first->getPriority() << std::endl;
    }
}

void testRenderFunction() {
    std::cout << "\n=== Test render() ===" << std::endl;

    List renderListManager;

    // Creazione di nodi con priorità
    auto node1 = std::make_shared<TestNode>("Node1", 2);
    auto node2 = std::make_shared<TestNode>("Node2", 1);

    // Creazione della lista di rendering
    std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> renderList = {
        {node1, glm::mat4(1.0f)},
        {node2, glm::mat4(1.0f)}
    };
    renderListManager.setListRendering(renderList);

    // Rendering della lista con matrice inversa della camera
    glm::mat4 inversaCamera(1.0f); // Matrice identità per il test
    renderListManager.render(inversaCamera);
}

int main() {
    testPassFunction();
    testSortListRendering();
    testRenderFunction();
    return 0;
}
