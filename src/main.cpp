#include <GLFW/glfw3.h>

#include <iostream>

#include "core/App.hpp"

using namespace fenton::core;

const double INCR = 0.001;

class TestApp : public App
{
    private:
        bool toggle;
        double val;
    public:
        TestApp(int w,int h,const std::string& title,bool poll) : App(w,h,title,poll)
        {
            toggle = false;
            val = 0.0;
            init();
        }
        ~TestApp() {}
        void myFunc()
        {
            std::cout << "myFunc() executing!\n";
        }
        void init()
        {
            mapCallbackToInput(Key::Escape,[this]() {quit();});
            mapCallbackToInput(Key::T,[this]() { toggle = !toggle; });
            mapCallbackToInput(Key::P,[this]()
            {
                std::cout << "current time: " << m_clock.current() << "s\n";
            });
            mapCallbackToInput(Key::E,[this]()
            {
                std::cout << "elapsed time: " << m_clock.elapsed() << "s = " << 1.0 / m_clock.elapsed() << "fps\n";
            });
            mapCallbackToInput(Key::Up,[this]()
            {
                val += INCR;
                std::cout << val << std::endl;
            });
            mapCallbackToInput(Key::Down,[this]()
            {
                val -= INCR;
                std::cout << val << std::endl;
            });
            mapCallbackToInput(Key::ABC,[this]()
            {
                std::cout << "Pressed keys A,B and C all together.\n";
            });
        }
        void update()
        {
            if(m_eventRegistry.isKeyDown(Keyboard::U))
            {
                val += 1;
                std::cout << val << std::endl;
            }

            unsigned int h,v;
            if(m_eventRegistry.isMousePressed(h,v))
            {
                std::cout << "mouse is pressed at: (" << h << "," << v << ")" << std::endl;
            }
            if(m_eventRegistry.isMouseReleased())
            {
                std::cout << "mouse is released" << std::endl;
                unsigned int x,y;
                m_eventRegistry.getMouseBegin(x,y);
                std::cout << "begin: (" << x << "," << y << ")";
                m_eventRegistry.getMouseEnd(x,y);
                std::cout << ", end: (" << x << "," << y << ")" << std::endl;
            }
            if(m_eventRegistry.isMouseDown(h,v))
            {
                std::cout << "mouse is down at: (" << h << "," << v << ")" << std::endl;
            }

            // clear events
            m_eventRegistry.clear();
        }
        void render()
        {
            if(toggle)
                glClearColor(1.0f,0.0f,0.0f,1.0f);
            else
                glClearColor(0.0f,0.0f,0.0f,1.0f);
        }
        void cleanup() override
        {
            std::cout << "Cleanup\n";
        }
    private:
    protected:
};

int main() {
    TestApp app(800,600,"app",true);
    app.run();

    return 0;
}
