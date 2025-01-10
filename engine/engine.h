#pragma once

#define LIB_NAME      "Engine"
#define LIB_VERSION   10

#include <sstream>

#include "Camera.h"
#include "Common.h"
#include "Material.h"
#include "List.h"
#include "Mesh.h"

/**
 * @class Engine
 * @brief La classe principale del motore grafico.
 *
 * Questa classe gestisce l'inizializzazione del motore, la gestione delle finestre,
 * il rendering, e la gestione della scena e delle camere.     necessario chiamare
 * la funzione `init` prima di poter utilizzare qualsiasi altra funzione del motore.
 * Alla fine,     necessario chiamare `quit` per liberare la memoria utilizzata.
 */
class LIB_API Engine
{
public:

    // Inizializza il motore
    static void init(const std::string windowTitle, const int windowWidth, const int windowHeight);

    // Getter
    static std::shared_ptr<Camera> getActiveCamera();
    static std::shared_ptr<Node> getScene();

    // Setter
    static void setBackGround(const float red, const float green, const float blue);
    static void setScene(const std::shared_ptr<Node> newScene);
    static void setActiveCamera(const std::shared_ptr<Camera> newActiveCamera);
    static void setScreenText(const std::string newText);

    // Set Callback
    static void setKeyboardCallback(void (*newKeyboardCallback) (const unsigned char key, const int mouseX, const int mouseY));
    static void setBlinkingCallback(void (*callback)());
    static void setMouseCallback(void(*newMouseCallback)(int button, int state, int mouseX, int mouseY));
    static void setMethodSpecialCallback(void(*newSpecialCallback) (int key, int mouseX, int mouseY));


    static bool isRunning();
    static void render();
    static void timerCallback(int value);
    static void update();
    static void clearScreen();
    static void swapBuffers();
    static void stop();
    static void quit();
    static std::shared_ptr<Node> findObjectByName(const std::string nameToFind);
    static std::shared_ptr<Node> findObjectByID(int idToFind);
    static std::shared_ptr<Node> getNodeByClick(int mouseX, int mouseY);
    static bool removeObject(const std::shared_ptr<Node>& nodeToRemove, const std::shared_ptr<Node>& root);
    static bool removeObject(const std::shared_ptr<Node>& nodeToRemove);
    static void removeAllObjects();
    static void initializeShadowMap(int width, int height);
private:

    static void resizeCallback(const int width, const int height);
    static void (*blinkingCallback)(); ///< Funzione di callback per il lampeggiamento.
    static std::shared_ptr<Node> findObjectByName(const std::string nameToFind, const std::shared_ptr<Node> root);
    static std::shared_ptr<Node> findObjectByID(int idToFind, const std::shared_ptr<Node> root);

    static bool isInitializedFlag; ///< Flag che indica se il motore     stato inizializzato.
    static bool isRunningFlag; ///< Flag che indica se il motore     in esecuzione.
    static int windowId;  ///< ID della finestra.

    static int windowWidth; ///< Larghezza della finestra.
    static int windowHeight; ///< Altezza della finestra.

    static std::shared_ptr<Node> scene; ///< Puntatore alla scena.
    static std::shared_ptr<Camera> activeCamera;  ///< Puntatore alla telecamera attiva.
    static std::shared_ptr<Material> shadowMaterial; ///< Puntatore al materiale per le ombre.
    static std::string screenText; ///< Testo da visualizzare sullo schermo.
    static int frames; ///< Contatore di frames
    static float fps; ///< Frames al secondo
};
