#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

/**
 * @brief Classe che rappresenta un vertice di una mesh 3D.
 */
class Vertex {
private:
    glm::vec3 position; ///< La posizione del vertice nello spazio 3D.
    glm::vec3 normal; ///< La normale del vertice.
    glm::vec2 textureCoordinates; ///< Le coordinate texture del vertice.

public:
    /**
     * @brief Costruttore della classe Vertex.
     * @param position La posizione del vertice.
     * @param normal La normale del vertice.
     */
    Vertex(glm::vec3 position, glm::vec3 normal);

    /**
     * @brief Distruttore della classe Vertex.
     */
    ~Vertex();

    /**
     * @brief Restituisce la posizione del vertice.
     * @return Un oggetto `glm::vec3` che rappresenta la posizione del vertice.
     */
    glm::vec3 getPosition();

    /**
     * @brief Restituisce la normale del vertice.
     * @return Un oggetto `glm::vec3` che rappresenta la normale del vertice.
     */
    glm::vec3 getNormal();

    /**
     * @brief Restituisce le coordinate texture del vertice.
     * @return Un oggetto `glm::vec2` che rappresenta le coordinate texture.
     */
    glm::vec2 getTextureCoordinates();

    /**
     * @brief Imposta le coordinate texture del vertice.
     * @param textCoord Le nuove coordinate texture.
     */
    void setTextureCoordinates(glm::vec2 textCoord);
};

#endif // VERTEX_H
