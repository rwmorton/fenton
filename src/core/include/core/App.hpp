#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "core/InputRegistry.hpp"
#include "core/EventRegistry.hpp"
#include "core/CallbackMap.hpp"
#include "core/Clock.hpp"

namespace fenton
{

namespace core
{

class App
{
    private:
    protected:
        int m_width,m_height;
        std::string m_title;
        GLFWwindow* m_window;
        bool m_poll;
        bool m_fullscreen;
        static InputRegistry m_inputRegistry;
        static EventRegistry m_eventRegistry;
        static CallbackMap m_callbackMap;
        Clock m_clock;
    public:
        // prevent copies
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        App(int width,int height,const std::string& title,bool poll,bool fullscreen);
        virtual ~App();

        void run();
        void quit();
    protected:
        void mapCallbackToInput(const Input& input,Callback callback);
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void cleanup() = 0;
    private:
        void processEvents();
        // callbacks
        void registerCallbacks();
        static void errorCallback(int error,const char* description);
        static void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods);
        static void mouseCallback(GLFWwindow* window,int button,int action,int mods);
        static void resizeCallback(GLFWwindow* window,int w,int h);
        static void cursorEnterCallback(GLFWwindow*,int entered);

        void computeScreenCoordinates(unsigned int& xScreen,unsigned int& yScreen);

};

} // namespace core

} // namespace fenton
