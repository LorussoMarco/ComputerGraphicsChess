#include "Node.h"

#include "GL/freeglut.h"
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Costruttore della classe Node.
 *
 * Il costruttore inizializza un oggetto `Node` impostando un ID univoco e un nome.
 * Configura inoltre la matrice di base, la posizione, la rotazione e lo scale dell'oggetto:
 * - Matrice di base (`baseMatrix`): matrice di identità.
 * - Posizione (`position`): (0.0f, 0.0f, 0.0f).
 * - Rotazione (`rotation`): (0.0f, 0.0f, 0.0f).
 * - Scala (`scale`): (1.0f, 1.0f, 1.0f).
 */
Node::Node()
    : Object("Node")
{
    this->setBaseMatrix(glm::mat4(1.0f));
    this->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    this->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    this->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    this->setPriority(0);
}

/**
 * @brief Costruttore della classe Node con tipo personalizzato.
 *
 * Il costruttore inizializza un oggetto `Node` con un tipo specifico e valori di default.
 *
 * @param type Il tipo dell'oggetto `Node`.
 */
Node::Node(std::string type)
    : Object(type)
{
    this->setBaseMatrix(glm::mat4(1.0f));
    this->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    this->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    this->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    this->setPriority(0);
}

///// Getter

glm::vec3 LIB_API Node::getPosition() const { return this->_position; }
glm::vec3 LIB_API Node::getRotation() const { return this->_rotation; }
glm::vec3 LIB_API Node::getScale() const { return this->_scale; }
int LIB_API Node::getPriority() const { return priority; }

glm::mat4 LIB_API Node::getLocalMatrix() const {
    const glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->_position);
    const glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), this->_scale);
    const glm::mat4 offsetMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    return offsetMatrix * this->_baseMatrix;
}

glm::mat4 Node::getWorldMatrix(const glm::mat4& parentMatrix) const {
    return parentMatrix * getLocalMatrix();
}

glm::mat4 Node::getTransform() const {
    return getLocalMatrix();
}

std::shared_ptr<Node> Node::getParent() const {
    return this->parent.lock();
}

std::vector<std::shared_ptr<Node>> LIB_API Node::getChildren() const {
    return this->children;
}

std::vector<std::shared_ptr<Node>>& Node::getChildren() {
    return this->children;
}

///// Setter

void LIB_API Node::setScale(const glm::vec3 newScale) { this->_scale = newScale; }
void LIB_API Node::setBaseMatrix(const glm::mat4 newBaseMatrix) { this->_baseMatrix = newBaseMatrix; }
void LIB_API Node::setPosition(const glm::vec3 newPosition) { this->_position = newPosition; }
void LIB_API Node::setRotation(const glm::vec3 newRotation) { this->_rotation = newRotation; }
void LIB_API Node::setPriority(int p) { priority = p; }

///// Altri metodi

void LIB_API Node::addChild(const std::shared_ptr<Node> newChild) {
    if (newChild) {
        newChild->parent = shared_from_this();
        this->children.push_back(newChild);
    }
}

void LIB_API Node::removeAllChildren() {
    this->children.clear();
    std::cout << "All children nodes have been removed from: " << this->getName() << std::endl;
}

void LIB_API Node::render(const glm::mat4 viewMatrix) const {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(viewMatrix));
}
