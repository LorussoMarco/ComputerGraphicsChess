#pragma once

#include <memory>

#include "Object.h"
#include "Common.h"

/**
 * @class Node
 * @brief Rappresenta un nodo nella gerarchia di una scena 3D.
 *
 * Questo file contiene la definizione della classe Node,
 * che rappresenta un nodo nella gerarchia di una scena 3D.
 */
class LIB_API Node : public Object
{
public:

    Node();
    Node(std::string type);

    // Getter
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
    int getPriority() const;
    glm::mat4 getLocalMatrix() const;
    std::vector<std::shared_ptr<Node>> getChildren() const;
    std::vector<std::shared_ptr<Node>>& getChildren();

    // Setter
    void setPosition(const glm::vec3 newPosition);
    void setRotation(const glm::vec3 newPosition);
    void setScale(const glm::vec3 newPosition);
    void setBaseMatrix(const glm::mat4 newBaseMatrix);
    void setPriority(int p);

    void addChild(const std::shared_ptr<Node> newChild);
    void removeAllChildren();
    // Renderizza un node
    void render(const glm::mat4 viewMatrix) const override;

private:

    int priority; ///< Priorita di rendering
    std::vector<std::shared_ptr<Node>> children; ///< Vettore di nodi figli.

    glm::mat4 _baseMatrix; ///< Posizione/orientamento iniziale dell'oggetto nello spazio.
    glm::vec3 _position;   ///< La posizione del nodo rispetto alla matrice di base.
    glm::vec3 _rotation;   ///< La rotazione del nodo rispetto alla matrice di base.
    glm::vec3 _scale;      ///< La scala del nodo rispetto alla matrice di base.
};
