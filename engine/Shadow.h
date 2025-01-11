#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <GL/freeglut.h>

#include "Lib.h"
#include "Object.h"
#include "Node.h"
#include "Vertex.h"

// Forward declaration per evitare dipendenze circolari
class Mesh;

class LIB_API Shadow : public Node {
public:
    Shadow(Mesh* mesh);
    ~Shadow();

    void addVertex(const glm::vec3& position, const glm::vec3& normal);
    std::vector<Vertex*> getVertices();
    virtual bool render(glm::mat4 transform, void* data); // Rimosso override

private:
    static float getDeepestPoint(const Mesh* meshToShadow);

    Mesh* meshToShadow;
    std::vector<Vertex*> vertices;
};
