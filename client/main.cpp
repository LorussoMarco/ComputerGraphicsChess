#include <iostream>
#include <memory>
#include <Engine.h>
#include <Node.h>
#include <PerspectiveCamera.h>
#include <OvoParser.h>
#include <PointLight.h>
#include <Material.h>

// Camera reference
std::shared_ptr<PerspectiveCamera> camera;

// Light reference
std::shared_ptr<PointLight> lightAbove;

// Movement speed
float cameraSpeed = 5.0f;
float lightSpeed = 5.0f;

// Rotation speed
float cameraRotationSpeed = 5.0f;

void addLightAboveScene() {
    // Crea una luce di tipo puntuale
    lightAbove = std::make_shared<PointLight>();
    lightAbove->setName("LightAbove");

    // Posiziona la luce sopra la scena
    glm::vec3 lightPosition = glm::vec3(0.0f, 100.0f, 0.0f); // Sopra la scena
    lightAbove->setPosition(lightPosition);

    // Imposta il colore della luce
    lightAbove->setDiffuseColor(glm::vec3(0.1f, 0.1f, 0.1f));  // Luce diffusa meno intensa
    lightAbove->setAmbientColor(glm::vec3(0.1f, 0.1f, 0.1f));  // Luce ambientale leggera
    lightAbove->setSpecularColor(glm::vec3(0.2f, 0.2f, 0.2f)); // Luce speculare moderata

    // Imposta il raggio della luce (influenza)
    lightAbove->setRadius(4.0f); // Raggio più ampio per diffondere la luce

    // Aggiungi la luce alla scena
    Engine::getScene()->addChild(lightAbove);
}

void setupCameraAndLightMovement() {
    Engine::setKeyboardCallback([](const unsigned char key, const int mouseX, const int mouseY) {
        // Ottieni la posizione corrente della camera e della luce
        glm::vec3 cameraPosition = camera->getPosition();
        glm::vec3 lightPosition = lightAbove->getPosition();

        switch (key) {
        case 'w': // Muove la camera in avanti
            cameraPosition.z -= cameraSpeed;
            break;
        case 's': // Muove la camera indietro
            cameraPosition.z += cameraSpeed;
            break;
        case 'a': // Muove la camera a sinistra
            cameraPosition.x -= cameraSpeed;
            break;
        case 'd': // Muove la camera a destra
            cameraPosition.x += cameraSpeed;
            break;
        case 'i': // Muove la luce in avanti
            lightPosition.z -= lightSpeed;
            break;
        case 'k': // Muove la luce indietro
            lightPosition.z += lightSpeed;
            break;
        case 'j': // Muove la luce a sinistra
            lightPosition.x -= lightSpeed;
            break;
        case 'l': // Muove la luce a destra
            lightPosition.x += lightSpeed;
            break;
        case 'u': // Muove la luce verso l'alto
            lightPosition.y += lightSpeed;
            break;
        case 'o': // Muove la luce verso il basso
            lightPosition.y -= lightSpeed;
            break;
        case 27: // ESC per uscire
            Engine::stop();
            break;
        }

        // Aggiorna la posizione della camera e della luce
        camera->setPosition(cameraPosition);
        lightAbove->setPosition(lightPosition);
        });

    Engine::setMethodSpecialCallback([](int key, int mouseX, int mouseY) {
        // Ottieni la rotazione corrente della camera
        glm::vec3 rotation = camera->getRotation();

        switch (key) {
        case 101: // Freccia su
            rotation.x -= cameraRotationSpeed;
            break;
        case 103: // Freccia giù
            rotation.x += cameraRotationSpeed;
            break;
        case 100: // Freccia sinistra
            rotation.y -= cameraRotationSpeed;
            break;
        case 102: // Freccia destra
            rotation.y += cameraRotationSpeed;
            break;
        }

        // Aggiorna la rotazione della camera
        camera->setRotation(rotation);
        });
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
    camera = std::make_shared<PerspectiveCamera>();
    camera->setName("MainCamera");
    camera->setPosition(glm::vec3(0.0f, 110.0f, 100.0f)); // Posizione
    camera->setRotation(glm::vec3(-40.0f, 0.0f, 0.0f));  // Rotazione
    scene->addChild(camera);
    Engine::setActiveCamera(camera);

    // Imposta il movimento della camera e della luce
    setupCameraAndLightMovement();

    // Carica una scena da file OVO e la imposta
    std::shared_ptr<Node> ovoScene = OVOParser::fromFile("./table2.ovo");
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
