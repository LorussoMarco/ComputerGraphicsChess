#include <iostream>
#include "MeshData.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // Per convertire glm::vec3 e vec2 in stringa

// Funzione per stampare i vertici
void printVertices(const std::vector<glm::vec3>& vertices) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << "Vertice " << i << ": " << glm::to_string(vertices[i]) << std::endl;
    }
}

// Funzione per stampare le facce
void printFaces(const std::vector<std::tuple<uint32_t, uint32_t, uint32_t>>& faces) {
    for (size_t i = 0; i < faces.size(); ++i) {
        auto [v1, v2, v3] = faces[i];
        std::cout << "Faccia " << i << ": (" << v1 << ", " << v2 << ", " << v3 << ")" << std::endl;
    }
}

// Funzione per stampare le normali
void printNormals(const std::vector<glm::vec3>& normals) {
    for (size_t i = 0; i < normals.size(); ++i) {
        std::cout << "Normale " << i << ": " << glm::to_string(normals[i]) << std::endl;
    }
}

// Funzione per stampare le coordinate UV
void printUVs(const std::vector<glm::vec2>& uvs) {
    for (size_t i = 0; i < uvs.size(); ++i) {
        std::cout << "UV " << i << ": " << glm::to_string(uvs[i]) << std::endl;
    }
}

void testMeshData() {
    std::cout << "=== Test Classe MeshData ===" << std::endl;

    // Creazione di una MeshData
    MeshData mesh;

    // Creazione di dati di test
    std::vector<glm::vec3> vertices = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };

    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces = {
        {0, 1, 2}
    };

    std::vector<glm::vec3> normals = {
        {0.0f, 0.0f, 1.0f}
    };

    std::vector<glm::vec2> uvs = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {0.5f, 1.0f}
    };

    // Imposta i dati
    mesh.set_mesh_data(vertices, faces, normals, uvs);

    // Verifica i getter
    std::cout << "\n--- Vertici ---" << std::endl;
    printVertices(mesh.getVertices());

    std::cout << "\n--- Facce ---" << std::endl;
    printFaces(mesh.getFaces());

    std::cout << "\n--- Normali ---" << std::endl;
    printNormals(mesh.getNormals());

    std::cout << "\n--- UV ---" << std::endl;
    printUVs(mesh.getUVs());
}
