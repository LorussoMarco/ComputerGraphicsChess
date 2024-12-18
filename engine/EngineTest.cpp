#include "engine.h"
#include <iostream>
#include <GL/freeglut.h>

// Variabili globali per gestione del test
float backgroundColor[] = { 0.0f, 0.0f, 0.0f }; // Colore di sfondo (nero)

// Callback per il rendering della finestra
void displayCallback() {
    Eng::Base::getInstance().clearWindow();

    // Simula il rendering di una scena
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Colore rosso
    glutSolidTeapot(1.0);

    Eng::Base::getInstance().swapBuffers();
}

// Callback per la gestione della tastiera
void keyboardCallback(unsigned char key, int x, int y) {
    std::cout << "Tasto premuto: " << key << " (posizione: " << x << ", " << y << ")" << std::endl;

    if (key == 'q' || key == 'Q') {
        std::cout << "Chiusura motore..." << std::endl;
        Eng::Base::getInstance().free();
        exit(0);
    }

    // Cambia il colore di sfondo con tasti numerici
    if (key == '1') backgroundColor[0] = 1.0f; // Rosso
    if (key == '2') backgroundColor[1] = 1.0f; // Verde
    if (key == '3') backgroundColor[2] = 1.0f; // Blu

    Eng::Base::getInstance().setBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
}

// Callback per il ridimensionamento della finestra
void reshapeCallback(int width, int height) {
    std::cout << "Ridimensionamento finestra: larghezza=" << width << ", altezza=" << height << std::endl;
    Eng::Base::getInstance().resizeViewport(width, height);
}

int main() {
    // Ottieni l'istanza del motore
    Eng::Base& engine = Eng::Base::getInstance();

    // Inizializza il motore
    if (!engine.init("Test Engine Window", 800, 600)) {
        std::cerr << "Errore durante l'inizializzazione del motore." << std::endl;
        return -1;
    }

    // Imposta i callback
    engine.setDisplayCallback(displayCallback);
    engine.setKeyboardCallback(keyboardCallback);
    engine.setReshapeCallback(reshapeCallback);

    // Imposta il colore di sfondo iniziale
    engine.setBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2]);

    // Avvia il ciclo principale
    std::cout << "Premi 'Q' per chiudere la finestra." << std::endl;
    engine.run();

    return 0;
}
