/**
 * @file		main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Achille Peternier (C) SUPSI [achille.peternier@supsi.ch] << change this to your group members
 */



//////////////
// #INCLUDE //
//////////////
   
   // Library header:
   #include "engine.h"

   // C/C++:
   #include <iostream>
   
   #define GLM_ENABLE_EXPERIMENTAL
   #include <glm/glm.hpp>
   #include <glm/gtx/string_cast.hpp>
    #include <GL/freeglut.h>


void display();
void keyboard(unsigned char key, int x, int y);
void reshape(int width, int height);

//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[]) {
    // Inizializzazione di GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 300);
    glutCreateWindow("Test FreeGLUT");

    // Callback per il rendering
    glutDisplayFunc(display);
    // Callback per il ridimensionamento
    glutReshapeFunc(reshape);

    // Configurazione di base
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Sfondo nero
    glEnable(GL_DEPTH_TEST); // Abilita il test di profondità

    // Loop principale
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Pulisce il buffer
    glLoadIdentity(); // Resetta la matrice
    glTranslatef(0.0f, 0.0f, -5.0f); // Posiziona la scena

    // Disegna un triangolo
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Rosso
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glVertex3f(1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blu
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    glFlush(); // Mostra il contenuto
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC to exit
        Eng::Base::getInstance().free();
    }
}

void reshape(int width, int height) {
    if (height == 0) height = 1; // Prevenzione divisione per zero
    float aspect = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height); // Imposta la viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f); // Proiezione prospettica
    glMatrixMode(GL_MODELVIEW);
}