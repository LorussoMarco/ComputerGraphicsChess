#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // Per la stampa di glm::vec3
#include "Light.h"

// Funzione per testare la creazione della luce
void testLightConstructor() {
    std::cout << "=== Test Costruttore Light ===" << std::endl;

    // Reset dell'ID della luce
    Light::resetNextLightId();

    // Creazione di una luce
    Light light("PointLight");

    std::cout << "Luce creata con ID: " << light.getCurrentLight(0) << " (Expected: GL_LIGHT0)" << std::endl;
}

// Funzione per testare i setter
void testLightSetters() {
    std::cout << "\n=== Test Setters della Luce ===" << std::endl;

    Light light("DirectionalLight");

    // Imposta i colori
    light.setAmbientColor(glm::vec3(0.2f, 0.2f, 0.2f));
    light.setDiffuseColor(glm::vec3(0.8f, 0.8f, 0.8f));
    light.setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));

    // Stampa i colori impostati
    std::cout << "Colore Ambient: " << glm::to_string(light._ambientColor) << " (Expected: (0.2, 0.2, 0.2))" << std::endl;
    std::cout << "Colore Diffuse: " << glm::to_string(light._diffuseColor) << " (Expected: (0.8, 0.8, 0.8))" << std::endl;
    std::cout << "Colore Specular: " << glm::to_string(light._specularColor) << " (Expected: (1.0, 1.0, 1.0))" << std::endl;
}

// Funzione per testare il reset dell'ID
void testLightResetId() {
    std::cout << "\n=== Test Reset Light ID ===" << std::endl;

    Light::resetNextLightId();

    Light light1("PointLight");
    Light light2("SpotLight");

    std::cout << "ID della prima luce: " << light1.getCurrentLight(0) << " (Expected: GL_LIGHT0)" << std::endl;
    std::cout << "ID della seconda luce: " << light2.getCurrentLight(1) << " (Expected: GL_LIGHT1)" << std::endl;

    // Reset ID
    Light::resetNextLightId();

    Light light3("NewLight");
    std::cout << "ID dopo il reset: " << light3.getCurrentLight(0) << " (Expected: GL_LIGHT0)" << std::endl;
}

int main() {
    testLightConstructor();
    testLightSetters();
    testLightResetId();

    return 0;
}
