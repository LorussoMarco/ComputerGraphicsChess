/**
 * @file        engine.h
 * @brief       Graphics engine main include file
 *
 * @author
 */
#pragma once

 //////////////
 // #INCLUDE //
 //////////////

 // C++ Standard:
#include <memory>
#include <functional>

/////////////
// VERSION //
/////////////

// Generic info:
#ifdef _DEBUG
#define LIB_NAME      "My Graphics Engine v0.1a (debug)"   ///< Library credits
#else
#define LIB_NAME      "My Graphics Engine v0.1a"          ///< Library credits
#endif
#define LIB_VERSION   10                                     ///< Library version (divide by 10)

// Export API:
#ifdef _WINDOWS
#ifdef ENGINE_EXPORTS
#define ENG_API __declspec(dllexport)
#else
#define ENG_API __declspec(dllimport)
#endif      
#else
#define ENG_API
#endif

///////////////
// NAMESPACE //
///////////////

namespace Eng {

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
        void run();

        // Set callbacks
        void setKeyboardCallback(std::function<void(unsigned char, int, int)> callback);
        void setDisplayCallback(std::function<void()> callback);
        void setReshapeCallback(std::function<void(int, int)> callback);

        // Rendering utilities
        void clearWindow();
        void swapBuffers();
        void setBackgroundColor(float r, float g, float b);

        // Status
        bool isRunning() const;

        // Viewport management
        void resizeViewport(int width, int height);

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

} // end of namespace Eng
