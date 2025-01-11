#include <iostream>
#include <memory>
#include <engine.h>
#include <Node.h>
#include <PerspectiveCamera.h>
#include <OvoParser.h>
#include <PointLight.h>
#include <Material.h>
#include <algorithm> 

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
std::shared_ptr<PerspectiveCamera> whiteCamera;

std::shared_ptr<PerspectiveCamera> freeCamera;

std::shared_ptr<PerspectiveCamera> currentActiveCamera = whiteCamera;


// Movement speed
float cameraSpeed = 5.0f;

bool isLightEnabled = false;

// Rotation speed
float cameraRotationSpeed = 5.0f;

void textOverlay() 
{
    std::stringstream text;
    text << "---GAME COMMANDS---\n";
    text << "[left mouse click] Select piece\n";
    text << "[directional arrows] - Move pieces\n";
    text << "[enter] - Confirm move\n";
    text << "[z] - Undo move\n";
    text << "[v] - Redo move\n";
    text << "[r] - Reset game\n";
    text << "\n";
    text << "---ENVIRONMENT COMMANDS---\n";
    text << "[l] - Turn on/off light\n";
    text << "[c] - Switch camera\n";
    text << "Free camera commands:\n";
    text << "   [w][a][s][d] - Move camera\n";
    text << "   [q][e][y][x] - Rotate camera\n";
    Engine::setScreenText(text.str());
}



void intializeAndSetCameras(std::shared_ptr<Node> scene)
{
    //white camera
    whiteCamera = std::make_shared<PerspectiveCamera>();
    whiteCamera->setName("WhiteCamera");
    whiteCamera->setPosition(glm::vec3(-20.0f, 80.0f, 0.0f)); 
    whiteCamera->setRotation(glm::vec3(-45.0f, -90.0f, 0.0f)); 
    scene->addChild(whiteCamera);
    Engine::setActiveCamera(whiteCamera);

    //free camera
    freeCamera = std::make_shared<PerspectiveCamera>();
    freeCamera->setName("BlackCamera");
    freeCamera->setPosition(glm::vec3(30.0f, 85.0f, -35.0f)); 
    freeCamera->setRotation(glm::vec3(-40.0f, 160.0f, 0.0f));  
    scene->addChild(freeCamera);
    Engine::setActiveCamera(freeCamera);

}

void resetScene() {
    // Ottieni la scena corrente
    std::shared_ptr<Node> scene = Engine::getScene();

    // Rimuovi tutti i figli della scena (inclusi camera e luce)
    scene->removeAllChildren();

    // Riaggiungi la camera prospettica
    intializeAndSetCameras(scene);

    // Ricarica la scena dal file OVO
    std::shared_ptr<Node> ovoScene = OVOParser::fromFile("./scena1.ovo");
    if (ovoScene) {
        scene->addChild(ovoScene);
        std::cout << "[Info] Scene successfully reset." << std::endl;
    }
    else {
        std::cerr << "[Error] Unable to reload OVO file." << std::endl;
    }

    ChessLogic::resetLogic();
}

void switchLight()
{
    // Trova la spotlight nella scena usando il nome "Spot001"
    std::shared_ptr<Node> spotlightNode = Engine::findObjectByName("Spot001");

    if (spotlightNode) {
        // Effettua un cast dinamico a SpotLight
        std::shared_ptr<SpotLight> spotlight = std::dynamic_pointer_cast<SpotLight>(spotlightNode);
        std::shared_ptr<Node> lightLamp = Engine::findObjectByName("lightLamp");
        std::shared_ptr<Mesh> lampMesh = std::dynamic_pointer_cast<Mesh>(lightLamp);


        if (spotlight) {
            // Alterna lo stato della luce
             // Supponendo che la classe SpotLight abbia un metodo isEnabled

            if (isLightEnabled) {
                spotlight->setRadius(0);
                isLightEnabled = false;
                lampMesh->getMaterial()->setAmbientColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
                lampMesh->getMaterial()->setDiffuseColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
                std::cout << "[Info] Spotlight disattivata." << std::endl;
            }
            else {
                spotlight->setRadius(200);
                isLightEnabled = true;
                lampMesh->getMaterial()->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                lampMesh->getMaterial()->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                std::cout << "[Info] Spotlight attivata." << std::endl;
            }
        }
        else {
            std::cerr << "[Error] Oggetto trovato non � una spotlight." << std::endl;
        }
    }
    else {
        std::cerr << "[Error] Spotlight 'Spot001' non trovata nella scena." << std::endl;
    }
}

void nextCamera() {
    // Passa alla prossima camera nell'ordine in loop
    if (currentActiveCamera == whiteCamera) {
        currentActiveCamera = freeCamera;
        Engine::setActiveCamera(freeCamera);
        std::cout << "[Info] Switched to Black Camera." << std::endl;
    }
    else {
        currentActiveCamera = whiteCamera;
        Engine::setActiveCamera(whiteCamera);
        std::cout << "[Info] Switched to White Camera." << std::endl;
    }
}

int main() {
    // Inizializza il motore con titolo finestra, larghezza e altezza
    Engine::init("Test Scene", 1000, 800);

    ChessLogic::initialPopulate();
    ChessLogic::init();
    textOverlay();
    Engine::setMouseCallback([](int button, int state, int mouseX, int mouseY)
        {
            if (button == Constants::MOUSE_LEFT_BUTTON && state == Constants::MOUSE_DOWN)
            {
                // Ottiene l'oggetto selezionato.
                std::shared_ptr<Node> selectedNode = Engine::getNodeByClick(mouseX, mouseY);

                if (selectedNode != nullptr)
                {
                    std::string pieceName = selectedNode->getName();
                    if (ChessLogic::isPieceSelected() == false)
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

            case 27: // ESC per uscire
                Engine::stop();
                break;
            }
        });

    Engine::setKeyboardCallback([](const unsigned char key, const int mouseX, const int mouseY) {

        glm::mat4 globalTransform = Engine::getGlobalTransform(freeCamera);
        glm::vec3 rotation = freeCamera->getRotation();
        // Estrai i vettori front, right e up dalla matrice globale
        glm::vec3 cameraFront = glm::normalize(glm::vec3(globalTransform[2])); // Z
        glm::vec3 cameraRight = glm::normalize(glm::vec3(globalTransform[0])); // X
        glm::vec3 cameraUp = glm::normalize(glm::vec3(globalTransform[1]));    // Y

        glm::vec3 cameraPosition = freeCamera->getPosition();

        switch (key) {
        case Constants::KEYBOARD_KEY_ENTER:
            ChessLogic::selectPiece("none");
            break;
        case 'r': // Tasto 'r' per resettare la scena
            resetScene();
            break;
        case 'z': // Tasto 'z' per annullare l'ultima mossa
            ChessLogic::undoLastMove();
            std::cout << "[Info] Mossa annullata." << std::endl;
            break;
        case 'c':
            nextCamera();
            break;
        case 'l':
            switchLight();
            break;
        case 'w': // Muove la camera in avanti
            cameraPosition -= cameraFront * cameraSpeed;
            break;
        case 's': // Muove la camera indietro
            cameraPosition += cameraFront * cameraSpeed;
            break;
        case 'a': // Muove la camera a sinistra
            cameraPosition -= cameraRight * cameraSpeed;
            break;
        case 'd': // Muove la camera a destra
            cameraPosition += cameraRight * cameraSpeed;
            break;
        case 'x': // Freccia su
            rotation.x -= cameraRotationSpeed;
            if (rotation.x < -89.0f) rotation.x = -89.0f; // Limita il pitch
            break;
        case 'y': // Freccia gi�
            rotation.x += cameraRotationSpeed;
            if (rotation.x > 89.0f) rotation.x = 89.0f; // Limita il pitch
            break;
        case 'e': // Freccia sinistra
            rotation.y -= cameraRotationSpeed;
            break;
        case 'q': // Freccia destra
            rotation.y += cameraRotationSpeed;
            break;
        }

        freeCamera->setRotation(rotation);

        // Aggiorna la posizione della camera
        freeCamera->setPosition(cameraPosition);

        });

    


    // Crea un nodo di scena e lo imposta
    std::shared_ptr<Node> scene = std::make_shared<Node>();
    scene->setName("RootNode");
    Engine::setScene(scene);

    intializeAndSetCameras(scene);
    // Crea una telecamera prospettica e la imposta come attiva
    

    // Carica una scena da file OVO e la imposta
    std::shared_ptr<Node> ovoScene = OVOParser::fromFile("./scena1.ovo");
    if (ovoScene) {
        scene->addChild(ovoScene);
    }
    else {
        std::cerr << "[Error] Unable to load OVO file." << std::endl;
    }

    std::shared_ptr<Node> spotlightNode = Engine::findObjectByName("Spot001");
    std::shared_ptr<SpotLight> spotlight = std::dynamic_pointer_cast<SpotLight>(spotlightNode);
    spotlight->setRadius(0);

    // Esegui il ciclo principale del motore finch� non viene chiuso
    while (Engine::isRunning()) {
        Engine::update();       // Gestisce eventi e callback
        Engine::clearScreen();  // Pulisce lo schermo per il nuovo frame
        Engine::render();    // Renderizza la scena
        
        Engine::swapBuffers();  // Scambia i buffer per visualizzare il frame
        if (ChessLogic::getWinner() != "None")
        {
            std::cout << "Partita terminata! Vince il giocatore " << ChessLogic::getWinner() << "." << std::endl;
            resetScene();             // Reset della scena grafica
        }
    }

    // Chiudi il motore e libera le risorse
    Engine::quit();

    return 0;
}
