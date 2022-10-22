#include "core/App.hpp"

namespace fenton
{

namespace core
{

InputRegistry App::m_inputRegistry = InputRegistry();
EventRegistry App::m_eventRegistry = EventRegistry();
CallbackMap App::m_callbackMap = CallbackMap();
double App::m_lastCursorX;
double App::m_lastCursorY;
double App::m_cursorOffsetX;
double App::m_cursorOffsetY;
bool App::m_firstCursor;
double App::m_scrollX;
double App::m_scrollY;

App::App
(
    int width,int height,
    const std::string& title,
    bool poll = true,
    bool fullscreen = false
)
:   m_width(width),m_height(height),
    m_title(title),
    m_window(nullptr),
    m_poll(poll),
    m_fullscreen(fullscreen)
{
    // initialize GLFW
    if(!glfwInit()) {
        glfwTerminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES,0);
    // glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

    m_window = m_fullscreen
        ? glfwCreateWindow(m_width,m_height,m_title.c_str(),glfwGetPrimaryMonitor(),nullptr)
        : glfwCreateWindow(m_width,m_height,m_title.c_str(),nullptr,nullptr);
    if(!m_window) {
        glfwTerminate();
    }

    // register all callbacks with GLFW
    this->registerCallbacks();

    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(0); // disable V-sync
    glfwSetInputMode(m_window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    // initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        this->quit();
    }
}

App::~App()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::run()
{
    unsigned int x,y;
    
    while(!glfwWindowShouldClose(m_window)) {
        glClearColor(0.f,0.f,0.f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->update();
        this->render();

        m_clock.update();

        App::computeScreenCoordinates(m_window,x,y);
        m_eventRegistry.updateCursor(x,y);

        glfwSwapBuffers(m_window);
        this->pollEvents();
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

void App::pollEvents()
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
    glfwSetCursorPosCallback(m_window,App::cursorCallback);
    glfwSetScrollCallback(m_window,App::scrollCallback);
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
            unsigned int newX,newY;
            App::computeScreenCoordinates(window,newX,newY);
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

void App::computeScreenCoordinates(GLFWwindow* window,unsigned int& xScreen,unsigned int& yScreen)
{
    double x,y;
    glfwGetCursorPos(window,&x,&y);

    int width,height;
    glfwGetFramebufferSize(window,&width,&height);

    int windowWidth,windowHeight;
    glfwGetWindowSize(window,&windowWidth,&windowHeight);

    const double scaleX = width / static_cast<double>(windowWidth);
    const double scaleY = height / static_cast<double>(windowHeight);

    xScreen = static_cast<int>(scaleX * x);
    yScreen = static_cast<int>(scaleY * y);
}

void App::cursorCallback(GLFWwindow* window,double xPos,double yPos)
{
    if(m_firstCursor)
    {
        App::m_lastCursorX = xPos;
        App::m_lastCursorY = yPos;
        App::m_firstCursor = false;
    }

    App::m_cursorOffsetX = xPos - m_lastCursorX;
    App::m_cursorOffsetY = m_lastCursorY - yPos;
    
    App::m_lastCursorX = xPos;
    App::m_lastCursorY = yPos;
}

void App::scrollCallback(GLFWwindow* window,double xOffset,double yOffset)
{
    App::m_scrollX = xOffset;
    App::m_scrollY = yOffset;
}

} // namespace core

} // namespace fenton
