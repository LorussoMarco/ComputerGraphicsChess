#include <iostream>
#include <memory>
#include <Engine.h>
#include <Node.h>
#include <PerspectiveCamera.h>
#include <OvoParser.h>
#include <PointLight.h>
#include <Material.h>
#include <algorithm> // Per std::find

#include "ChessLogic.h"

namespace Constants {
    constexpr inline int MOUSE_LEFT_BUTTON = 0;
    constexpr inline int MOUSE_DOWN = 0;
    constexpr inline int KEYBOARD_KEY_UP = 101;
    constexpr inline int KEYBOARD_KEY_DOWN = 103;
    constexpr inline int KEYBOARD_KEY_LEFT = 100;
    constexpr inline int KEYBOARD_KEY_RIGHT = 102;
    constexpr inline int KEYBOARD_KEY_ENTER = 13;
}

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

/*void setupCameraAndLightMovement() {
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
        case 'q': // Muove la camera a sinistra
            cameraPosition.y -= cameraSpeed;
            break;
        case 'e': // Muove la camera a destra
            cameraPosition.y += cameraSpeed;
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

        glm::vec3 cameraRotation = camera->getRotation();
        std::cout << "Camera Position: (" 
            << cameraPosition.x << ", "
            << cameraPosition.y << ", "
            << cameraPosition.z << ")" << std::endl;
        std::cout << "Camera Rotation: ("
            << cameraRotation.x << ", "
            << cameraRotation.y << ", "
            << cameraRotation.z << ")" << std::endl;
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

        glm::vec3 cameraPosition = camera->getPosition();
        std::cout << "Camera Position: ("
            << cameraPosition.x << ", "
            << cameraPosition.y << ", "
            << cameraPosition.z << ")" << std::endl;
        std::cout << "Camera Rotation: ("
            << rotation.x << ", "
            << rotation.y << ", "
            << rotation.z << ")" << std::endl;
        });
}*/

int main() {
    // Inizializza il motore con titolo finestra, larghezza e altezza
    Engine::init("Test Scene", 800, 600);

    ChessLogic::initialPopulate();
    ChessLogic::init();

    static std::list<std::string> stringList = {"Rooftop", "Floor", "Wall001", "Wall002", "Wall003", "Table", "Tableleg001","Tableleg002" ,"Tableleg003" ,"Tableleg004", "Omni001","ChessBoard.001"};

    Engine::setMouseCallback([](int button, int state, int mouseX, int mouseY)
        {
            if (button == Constants::MOUSE_LEFT_BUTTON && state == Constants::MOUSE_DOWN)
            {
                // Ottiene l'oggetto selezionato.
                std::shared_ptr<Node> selectedNode = Engine::getNodeByClick(mouseX, mouseY);

                if (selectedNode != nullptr)
                {
                    std::string pieceName = selectedNode->getName();

                    // Controlla se il nome è nella lista globale
                    if (std::find(stringList.begin(), stringList.end(), pieceName) != stringList.end())
                    {
                        std::cout << "Il pezzo \"" << pieceName << "\" non può essere selezionato poiché è nella lista." << std::endl;
                    }
                    else
                    {
                        ChessLogic::selectPiece(pieceName);
                    }
                }
                else
                {
                    std::cout << "Nessun oggetto selezionato." << std::endl;
                }
            }
        });

    Engine::setMethodSpecialCallback([](int key, int mouseX, int mouseY)
        {
            
            switch (key) {
            case Constants::KEYBOARD_KEY_UP:
                ChessLogic::move(Direction::UP);
                break;

            case Constants::KEYBOARD_KEY_DOWN:
                ChessLogic::move(Direction::DOWN);
                break;

            case Constants::KEYBOARD_KEY_LEFT:
                ChessLogic::move(Direction::LEFT);
                break;

            case Constants::KEYBOARD_KEY_RIGHT:
                ChessLogic::move(Direction::RIGHT);
                break;
            }

        });

    Engine::setKeyboardCallback([](const unsigned char key, const int mouseX, const int mouseY) {
        
        switch (key) {
        case 13: 
            ChessLogic::selectPiece("none");
            break;
        }
    });

    // Crea un nodo di scena e lo imposta
    std::shared_ptr<Node> scene = std::make_shared<Node>();
    scene->setName("RootNode");
    Engine::setScene(scene);

    // Aggiungi una luce sopra la scena
    addLightAboveScene();

    // Crea una telecamera prospettica e la imposta come attiva
    camera = std::make_shared<PerspectiveCamera>();
    camera->setName("MainCamera");
    camera->setPosition(glm::vec3(-10.0f, 60.0f, 0.0f)); // Posizione
    camera->setRotation(glm::vec3(-45.0f, -90.0f, 0.0f));  // Rotazione
    scene->addChild(camera);
    Engine::setActiveCamera(camera);

    // Imposta il movimento della camera e della luce
    //setupCameraAndLightMovement();

    // Carica una scena da file OVO e la imposta
    std::shared_ptr<Node> ovoScene = OVOParser::fromFile("./scena1.ovo");
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
