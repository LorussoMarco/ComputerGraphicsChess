#include "Object.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>

Object::Object() {}

Object::~Object() {}

void Object::draw(const glm::mat4& parentTransform) {
    Node::draw(parentTransform); // Calcola le trasformazioni globali
    renderCube(); // Disegna il cubo
}

void Object::renderCube() {
    static const float vertices[] = {
        -0.5f, -0.5f,  0.5f,  // Front face
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,  // Back face
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };

    static const unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, // Front face
        4, 5, 6, 6, 7, 4, // Back face
        0, 1, 5, 5, 4, 0, // Bottom face
        3, 2, 6, 6, 7, 3, // Top face
        0, 3, 7, 7, 4, 0, // Left face
        1, 2, 6, 6, 5, 1  // Right face
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}
