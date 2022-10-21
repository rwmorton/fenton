#include <iostream>
#include <cmath>

#include "core/App.hpp"

using namespace fenton::core;

const double INCR = 0.001;

// Shader sources
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    uniform vec3 triangleColor;
    void main()
    {
        outColor = vec4(triangleColor, 1.0);
    }
)glsl";

class Triangle
{
    private:
        GLuint vao,vbo,vertexShader,fragmentShader,shaderProgram;
    public:
        Triangle()
        {
            glGenVertexArrays(1,&vao);
            glBindVertexArray(vao);

            GLfloat vertices[] = {
                -1.f,1.f,
                1.f,0.f,
                0.f,-1.f
            };

            glGenBuffers(1,&vbo);
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader,1,&vertexSource,nullptr);
            glCompileShader(vertexShader);

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader,1,&fragmentSource,nullptr);
            glCompileShader(fragmentShader);

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram,vertexShader);
            glAttachShader(shaderProgram,fragmentShader);
            glLinkProgram(shaderProgram);
        }

        void render()
        {
            glUseProgram(shaderProgram);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);
        }
};

class TestApp : public App
{
    private:
        bool toggle;
        double val;
        GLuint vao,vbo,ebo,vertexShader,fragmentShader,shaderProgram,posAttrib,uniColor;
        Triangle tri;
    public:
        TestApp(int w,int h,const std::string& title,bool poll,bool fullscreen) : App(w,h,title,poll,fullscreen)
        {
            toggle = false;
            val = 0.0;
            init();
        }
        ~TestApp()
        {
            this->cleanup();
        }
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

            glGenVertexArrays(1,&vao);
            glBindVertexArray(vao);

            float vertices[] = {
                0.5f, 0.5f, 0.0f, // top right
                0.5f, -0.5f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f // top left
            };
            unsigned int indices[] = { // note that we start from 0!
                0, 1, 3, // first triangle
                1, 2, 3 // second triangle
            };

            glGenBuffers(1,&vbo);
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            glGenBuffers(1,&ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader,1,&vertexSource,nullptr);
            glCompileShader(vertexShader);

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader,1,&fragmentSource,nullptr);
            glCompileShader(fragmentShader);

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram,vertexShader);
            glAttachShader(shaderProgram,fragmentShader);
            glBindFragDataLocation(shaderProgram,0,"outColor");
            glLinkProgram(shaderProgram);

            posAttrib = glGetAttribLocation(shaderProgram,"position");
            glEnableVertexAttribArray(posAttrib);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),0);

            uniColor = glGetUniformLocation(shaderProgram,"triangleColor");

            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

            glClearColor(0.f,0.f,0.f,1.f);
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
            
            // update triangle colors
            double t = m_clock.current();
            glUniform3f
            (
                uniColor,
                (
                    std::sin(t * 1.0f) + 1.0f),
                    (std::sin(t * 2.0f) + 1.0f),
                    (std::sin(t * 3.0f) + 1.0f)
            );

            // clear events
            m_eventRegistry.clear();
        }
        void render()
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(vao);
            // glDrawArrays(GL_TRIANGLES,0,3);
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
            glBindVertexArray(0);

            // tri.render();

            glFinish(); // testing only
        }
        void cleanup() override
        {
            std::cout << "Cleanup\n";
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(shaderProgram);
            glDeleteVertexArrays(1,&vao);
            glDeleteBuffers(1,&vbo);
            glDeleteBuffers(1,&ebo);
        }
    private:
    protected:
};

int main() {
    TestApp app(800,600,"app",true,false);
    app.run();

    return 0;
}
