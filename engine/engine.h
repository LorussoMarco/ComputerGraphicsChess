/**
 * @file		engine.h
 * @brief	Graphics engine main include file
 *
 * @author	Achille Peternier (C) SUPSI [achille.peternier@supsi.ch] << change this to your group members
 */
#pragma once


 
//////////////
// #INCLUDE //
//////////////

   // C/C++:         
   #include <memory> 



/////////////
// VERSION //
/////////////

   // Generic info:
#ifdef _DEBUG
   #define LIB_NAME      "My Graphics Engine v0.1a (debug)"   ///< Library credits
#else
   #define LIB_NAME      "My Graphics Engine v0.1a"   ///< Library credits
#endif
   #define LIB_VERSION   10                           ///< Library version (divide by 10)

   // Export API:
#ifdef _WINDOWS
   // Specifies i/o linkage (VC++ spec):
   #ifdef ENGINE_EXPORTS
      #define ENG_API __declspec(dllexport)
   #else
      #define ENG_API __declspec(dllimport)
   #endif      

   // Get rid of annoying warnings:
   #pragma warning(disable : 4251) 
#else // Under linux
   #define ENG_API
#endif



///////////////
// NAMESPACE //
///////////////

namespace Eng {



    //////////////
    // #INCLUDE //
    //////////////   

       // You can subinclude here other headers of your engine...



    ///////////////////////
    // MAIN ENGINE CLASS //
    ///////////////////////

    /**
     * @brief Base engine main class. This class is a singleton.
     */
    class ENG_API Base final {
    public:
        // Singleton instance
        static Base& getInstance();

        // Lifecycle
        bool init(const char* windowTitle, int width, int height);
        bool free();

        // Set callbacks
        void setKeyboardCallback(void (*callback)(unsigned char, int, int));
        void setDisplayCallback(void (*callback)());
        void setReshapeCallback(void (*callback)(int, int));

        // Rendering utilities
        void clearWindow();
        void swapBuffers();
        void setBackgroundColor(float r, float g, float b);

        // Status
        bool isRunning() const;

    private:
        // Private constructor/destructor
        Base();
        ~Base();

        // Prevent copying
        Base(const Base&) = delete;
        void operator=(const Base&) = delete;

        // Reserved data
        struct Reserved;
        std::unique_ptr<Reserved> reserved;

        // Internal state
        bool running;
    };
}; // end of namespace Eng::

