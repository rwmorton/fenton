#include "core/App.hpp"

namespace fenton
{

namespace core
{

InputRegistry App::m_inputRegistry = InputRegistry();
EventRegistry App::m_eventRegistry = EventRegistry();
CallbackMap App::m_callbackMap = CallbackMap();

App::App
(
    int width,int height,
    const std::string& title,
    bool poll = true
)
:   m_width(width),m_height(height),
    m_title(title),
    m_window(nullptr),
    m_poll(poll)
{
    // initialize GLFW
    if(!glfwInit()) {
        glfwTerminate();
    }

    m_window = glfwCreateWindow(m_width,m_height,m_title.c_str(),nullptr,nullptr);
    if(!m_window) {
        glfwTerminate();
    }

    // register all callbacks with GLFW
    this->registerCallbacks();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    glfwMakeContextCurrent(m_window);
}

App::~App()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::run()
{
    while(!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        this->update();
        this->render();

        glfwSwapBuffers(m_window);
        this->processEvents();

        m_clock.update();

        unsigned int x,y;
        this->computeScreenCoordinates(x,y);
        m_eventRegistry.updateCursor(x,y);        
    }
}

void App::quit()
{
    glfwSetWindowShouldClose(m_window,GLFW_TRUE);
    this->cleanup();
}

void App::mapCallbackToInput(const Input& input,Callback callback)
{
    m_callbackMap.set(input,callback);
}

void App::processEvents()
{
    if(m_poll)
    {
        glfwPollEvents();
    }
    else
    {
        glfwWaitEvents();
    }
}

// register callbacks
void App::registerCallbacks()
{
    glfwSetErrorCallback(App::errorCallback);
    glfwSetKeyCallback(m_window,App::keyCallback);
    glfwSetMouseButtonCallback(m_window,App::mouseCallback);
    glfwSetWindowSizeCallback(m_window,App::resizeCallback);
}

// callbacks
void App::errorCallback(int error,const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

void App::keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    // save key press/release to the input registry
    if(static_cast<Action>(action) == Action::PRESS)
    {
        m_inputRegistry.add(static_cast<Keyboard>(key));
    }
    else if(static_cast<Action>(action) == Action::RELEASE)
    {
        m_inputRegistry.remove(static_cast<Keyboard>(key));
    }
    // IGNORE REPEAT STATE

    if(action == Action::PRESS || action == Action::REPEAT)
    {
        m_eventRegistry.onKeyDown(static_cast<Keyboard>(key));
    }
    else
    {
        m_eventRegistry.onKeyUp(static_cast<Keyboard>(key));
    }

    m_callbackMap.execute(Input(m_inputRegistry.keys(),m_inputRegistry.buttons()));
}

void App::mouseCallback(GLFWwindow* window,int button,int action,int mods)
{
    // save mouse button press/release to the input registry
    if(static_cast<Action>(action) == Action::PRESS)
    {
        m_inputRegistry.add(static_cast<Mouse>(button));
    }
    else if(static_cast<Action>(action) == Action::RELEASE)
    {
        m_inputRegistry.remove(static_cast<Mouse>(button));
    }
    // IGNORE REPEAT STATE

    if(button == Mouse::BUTTON_LEFT)
    {
        if(action == Action::PRESS)
        {
            double x,y;
            glfwGetCursorPos(window,&x,&y);

            int width,height;
            glfwGetFramebufferSize(window,&width,&height);

            int windowWidth,windowHeight;
            glfwGetWindowSize(window,&windowWidth,&windowHeight);

            double scaleX = width / static_cast<double>(windowWidth);
            double scaleY = height / static_cast<double>(windowHeight);

            int newX = static_cast<int>(scaleX * x);
            int newY = static_cast<int>(scaleY * y);

            m_eventRegistry.onMouseDown(newX,newY);
        }
        else
        {
            m_eventRegistry.onMouseUp();
        }
    }

    m_callbackMap.execute(Input(m_inputRegistry.keys(),m_inputRegistry.buttons()));
}


void App::resizeCallback(GLFWwindow* window,int w,int h)
{
    int width,height;
    glfwGetWindowSize(window,&width,&height);
    glViewport(0,0,width,height);
}

void App::cursorEnterCallback(GLFWwindow*,int entered)
{
    if(entered)
    {
        m_eventRegistry.setCursorInside(true);
    }
    else
    {
        m_eventRegistry.setCursorInside(false);
    }
}

void App::computeScreenCoordinates(unsigned int& xScreen,unsigned int& yScreen)
{
    double x,y;
    glfwGetCursorPos(m_window,&x,&y);

    int width,height;
    glfwGetFramebufferSize(m_window,&width,&height);

    int windowWidth,windowHeight;
    glfwGetWindowSize(m_window,&windowWidth,&windowHeight);

    double scaleX = width / static_cast<double>(windowWidth);
    double scaleY = height / static_cast<double>(windowHeight);

    xScreen = static_cast<int>(scaleX * x);
    yScreen = static_cast<int>(scaleY * y);
}

} // namespace core

} // namespace fenton
