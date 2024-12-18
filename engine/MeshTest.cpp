#include <iostream>
#include <memory>
#include "Mesh.h"
#include "Material.h"
#include "MeshData.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // Per la stampa di glm::vec3

void testMeshConstructor() {
    std::cout << "=== Test Costruttore Mesh ===" << std::endl;

    Mesh mesh;

    std::cout << "Mesh creata con materiale di default e ombre abilitate." << std::endl;
    std::cout << "Ombre: " << (mesh.getShadows() ? "Abilitate" : "Disabilitate") << " (Expected: Abilitate)" << std::endl;
    std::cout << "Materiale assegnato: " << (mesh.getMaterial() ? "Esistente" : "Nessun materiale") << std::endl;
}

void testMeshSetters() {
    std::cout << "\n=== Test Setters Mesh ===" << std::endl;

    Mesh mesh;

    // Imposta un materiale personalizzato
    auto material = std::make_shared<Material>();
    material->setEmissionColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Rosso
    mesh.setMaterial(material);

    // Imposta le ombre
    mesh.setShadows(false);

    std::cout << "Materiale emission color: " << glm::to_string(material->getEmissionColor()) << " (Expected: (1, 0, 0))" << std::endl;
    std::cout << "Ombre: " << (mesh.getShadows() ? "Abilitate" : "Disabilitate") << " (Expected: Disabilitate)" << std::endl;
}

void testMeshDataAndRender() {
    std::cout << "\n=== Test MeshData e Render ===" << std::endl;

    Mesh mesh;

    // Creazione di MeshData
    MeshData meshData;
    std::vector<glm::vec3> vertices = {
        {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}
    };

    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces = {
        {0, 1, 2}
    };

    std::vector<glm::vec3> normals = {
        {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}
    };

    std::vector<glm::vec2> uvs = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {0.5f, 1.0f}
    };

    meshData.set_mesh_data(vertices, faces, normals, uvs);
    mesh.setMeshData(meshData);

    std::cout << "MeshData impostata con 3 vertici, 1 faccia, e normali." << std::endl;

    // Simulazione del render in modalità normale
    std::cout << "\nRender in modalità normale:" << std::endl;
    glm::mat4 viewMatrix(1.0f); // Matrice identità come esempio
    mesh.render(viewMatrix);

    // Simulazione del render in modalità color picking
    std::cout << "\nRender in modalità color picking:" << std::endl;
    Mesh::isColorPickingMode = true;
    mesh.render(viewMatrix);
}

void testMesh() {
    testMeshConstructor();
    testMeshSetters();
    testMeshDataAndRender();

}
