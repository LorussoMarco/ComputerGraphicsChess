#include "Shadow.h"
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"

LIB_API Shadow::Shadow(Mesh* mesh) : Node("ShadowOf" + mesh->getName())
{
    meshToShadow = mesh;

    const auto& vertices = mesh->getMeshData().getVertices();
    const auto& normals = mesh->getMeshData().getNormals();

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        glm::vec3 position = vertices[i];
        glm::vec3 normal = (i < normals.size()) ? normals[i] : glm::vec3(0.0f);
        addVertex(position, normal);
    }
}

LIB_API Shadow::~Shadow() {}

void Shadow::addVertex(const glm::vec3& position, const glm::vec3& normal)
{
    float deepestPoint = getDeepestPoint(meshToShadow);
    glm::vec3 shadowPosition = position;
    shadowPosition.y = deepestPoint + 1.0f;

    Vertex* projectedVertex = new Vertex(shadowPosition, normal);
    vertices.push_back(projectedVertex);
}

std::vector<Vertex*> Shadow::getVertices()
{
    return vertices;
}

bool LIB_API Shadow::render(glm::mat4, void*)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

    glBegin(GL_TRIANGLES);
    for (Vertex* v : vertices)
    {
        glNormal3fv(glm::value_ptr(v->getNormal()));
        glVertex3fv(glm::value_ptr(v->getPosition()));
    }
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    return true;
}

float Shadow::getDeepestPoint(const Mesh* meshToShadow)
{
    const auto& vertices = meshToShadow->getMeshData().getVertices();

    if (vertices.empty())
        return 0.0f;

    float deepestPoint = vertices.front().y;
    for (const auto& vertex : vertices)
    {
        if (vertex.y < deepestPoint)
            deepestPoint = vertex.y;
    }
    return deepestPoint;
}
