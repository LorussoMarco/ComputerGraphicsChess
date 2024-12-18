#pragma once

#include <iostream>

// Controlla se il simbolo _WINDOWS definito -> determina se il codice viene compilato su Windows
#ifdef _WINDOWS
#ifdef SIMPLEDYNLIB_EXPORTS

// Se SIMPLEDYNLIB_EXPORTS definito, 
// LIB_API viene definito come __declspec(dllexport), il che indica che le funzioni e 
// le classi dichiarate con LIB_API sono esportate dalla DLL (Dynamic Link Library).
#define LIB_API __declspec(dllexport)

// Se non definito, LIB_API viene definito come __declspec(dllimport), 
// che indica che le funzioni e le classi dichiarate con LIB_API sono importate da una DLL.
#else
#define LIB_API __declspec(dllimport)
#endif
#else
// Se _WINDOWS non definito (Linux)
// LIB_API viene definito come nulla.
#define LIB_API
#endif

#define _DEBUG
#ifdef _DEBUG
#define DEBUG( message ) \
        std::cout << "[DEBUG] " << message << std::endl;
#else
    //  Se _DEBUG non definito definito come una macro vuota.
#define DEBUG( message )
#endif

//  Macro per stampare messaggi di avviso. 
#define WARNING( message ) \
    std::cout << "[WARNING] " << message << std::endl;

// Macro per stampare messaggi di errore. 
#define ERROR( message ) \
    std::cerr << "[ERROR] " << message << std::endl;
