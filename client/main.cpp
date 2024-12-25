#include <iostream>
#include <memory>
#include <Engine.h>
#include <Node.h>
#include <PerspectiveCamera.h>
#include <OvoParser.h>
#include <PointLight.h>

void addLightAboveScene() {
    // Crea una luce di tipo puntuale
    std::shared_ptr<PointLight> lightAbove = std::make_shared<PointLight>();
    lightAbove->setName("LightAbove");

    // Posiziona la luce sopra la scena
    glm::vec3 lightPosition = glm::vec3(0.0f, 100.0f, 0.0f); // Sopra la scena
    lightAbove->setPosition(lightPosition);

    // Imposta il colore della luce (bianco in questo esempio)
    lightAbove->setDiffuseColor(glm::vec3(0.5f, 0.5f, 0.5f));  // Luce diffusa meno intensa
    lightAbove->setAmbientColor(glm::vec3(0.2f, 0.2f, 0.2f));  // Luce ambientale più leggera
    lightAbove->setSpecularColor(glm::vec3(0.6f, 0.6f, 0.6f)); // Luce speculare moderata

    // Imposta il raggio della luce (influenza)
    lightAbove->setRadius(10.0f); // Cambia il raggio in base alle dimensioni della scena

    // Aggiungi la luce alla scena
    Engine::getScene()->addChild(lightAbove);
}

int main() {
    // Inizializza il motore con titolo finestra, larghezza e altezza
    Engine::init("Test Scene", 800, 600);

    // Crea un nodo di scena e lo imposta
    std::shared_ptr<Node> scene = std::make_shared<Node>();
    scene->setName("RootNode");
    Engine::setScene(scene);

    // Aggiungi una luce sopra la scena
    addLightAboveScene();

    // Crea una telecamera prospettica e la imposta come attiva
    std::shared_ptr<PerspectiveCamera> camera = std::make_shared<PerspectiveCamera>();
    camera->setName("MainCamera");
    camera->setPosition(glm::vec3(0.0f, 110.0f, 100.0f)); // Posizione
    camera->setRotation(glm::vec3(-40.0f, 0.0f, 0.0f));  // Rotazione
    scene->addChild(camera);
    Engine::setActiveCamera(camera);

    // Carica una scena da file OVO e la imposta
    std::shared_ptr<Node> ovoScene = OVOParser::fromFile("./table.ovo");
    if (ovoScene) {
        scene->addChild(ovoScene);
    }
    else {
        std::cerr << "[Error] Unable to load OVO file." << std::endl;
    }

    // Esegui il ciclo principale del motore finché non viene chiuso
    while (Engine::isRunning()) {
        Engine::update();       // Gestisce eventi e callback
        Engine::clearScreen();  // Pulisce lo schermo per il nuovo frame
        Engine::render();       // Renderizza la scena
        Engine::swapBuffers();  // Scambia i buffer per visualizzare il frame
    }

    // Chiudi il motore e libera le risorse
    Engine::quit();

    return 0;
}