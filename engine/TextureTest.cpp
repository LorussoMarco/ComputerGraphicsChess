#include <iostream>
#include <memory>
#include "Texture.h"
#include <glm/glm.hpp>

// Funzione di test per il costruttore di Texture
void testTextureConstructor() {
    std::cout << "=== Test Costruttore Texture ===" << std::endl;

    const std::string texturePath = "test_texture.png";

    try {
        // Creazione della texture
        Texture texture(texturePath);
        std::cout << "Texture caricata correttamente dal percorso: " << texturePath << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Errore durante il caricamento della texture: " << e.what() << std::endl;
    }
}

// Funzione di test per il metodo render()
void testRenderTexture() {
    std::cout << "\n=== Test Metodo render() ===" << std::endl;

    const std::string texturePath = "test_texture.png";

    // Creazione della texture
    Texture texture(texturePath);

    // Simula una matrice viewMatrix (identità per test)
    glm::mat4 viewMatrix(1.0f);

    std::cout << "Chiamata al metodo render()..." << std::endl;
    texture.render(viewMatrix);

    std::cout << "Render della texture completato." << std::endl;
}

// Test per il distruttore
void testTextureDestructor() {
    std::cout << "\n=== Test Distruttore Texture ===" << std::endl;

    const std::string texturePath = "test_texture.png";

    {
        Texture texture(texturePath);
        std::cout << "Texture creata. Verrà distrutta automaticamente all'uscita dallo scope." << std::endl;
    }

    std::cout << "Texture distrutta correttamente (distruttore chiamato)." << std::endl;
}

int main() {
    testTextureConstructor();
    testRenderTexture();
    testTextureDestructor();

    return 0;
}
