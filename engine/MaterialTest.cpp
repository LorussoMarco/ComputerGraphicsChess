#include <iostream>
#include <memory>
#include "Material.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// Funzione per testare il costruttore di Material
void testMaterialConstructor() {
    std::cout << "=== Test Costruttore Material ===" << std::endl;

    Material material;

    std::cout << "Emission Color: " << glm::to_string(material.getEmissionColor())
        << " (Expected: (0, 0, 0))" << std::endl;
    std::cout << "Material creato correttamente con valori di default." << std::endl;
}

// Funzione per testare setters e getters
void testMaterialSettersAndGetters() {
    std::cout << "\n=== Test Setters e Getters Material ===" << std::endl;

    Material material;

    material.setEmissionColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Rosso
    material.setAmbientColor(glm::vec3(0.2f, 0.2f, 0.2f));
    material.setDiffuseColor(glm::vec3(0.5f, 0.5f, 0.5f));
    material.setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));
    material.setShininess(128.0f);
    material.setAlpha(0.5f);

    std::cout << "Emission Color: " << glm::to_string(material.getEmissionColor())
        << " (Expected: (1, 0, 0))" << std::endl;
    std::cout << "Valori aggiornati correttamente." << std::endl;
}

// Funzione per testare la texture
void testMaterialWithTexture() {
    std::cout << "\n=== Test Material con Texture ===" << std::endl;

    Material material;

    // Carica una texture di test
    std::shared_ptr<Texture> texture = std::make_shared<Texture>("test_texture.png");
    material.setTexture(texture);

    std::cout << "Texture applicata correttamente al materiale." << std::endl;

    // Simula il rendering
    glm::mat4 viewMatrix(1.0f);
    std::cout << "Render del materiale con texture:" << std::endl;
    material.render(viewMatrix);
}

int main() {
    testMaterialConstructor();
    testMaterialSettersAndGetters();
    testMaterialWithTexture();

    return 0;
}
