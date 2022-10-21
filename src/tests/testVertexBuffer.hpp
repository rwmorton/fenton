#pragma once

#include "core/App.hpp"
#include "graphics/VertexBuffer.hpp"
#include "graphics/Renderer.hpp"

#include "shaders.hpp"

using namespace fenton::core;
using namespace fenton::graphics;

GLfloat vertices[] = {
    -0.90, -0.90, 0.0, // Triangle 1
    0.85, -0.90, 0.0,
    -0.90, 0.85, 0.0,
    0.90, -0.85, 0.0, // Triangle 2
    0.90, 0.90, 0.0,
    -0.85, 0.90, 0.0
};

class TestVBO : public App
{
    private:
        Renderer renderer;
        VertexBuffer vertexBuffer;
        GLuint vertexShader,fragmentShader,shaderProgram;
    public:
        TestVBO(int w,int h,const std::string& title,bool poll,bool fullscreen) : App(w,h,title,poll,fullscreen)
        {
            init();
        }
        void init()
        {
            mapCallbackToInput(Key::Escape,[this](){quit();});
            //
            vertexBuffer.create
            (
                VertexFormat::POSITION,
                6,
                &vertices,
                BufferDataUsage::DEFAULT
            );

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

            glUseProgram(shaderProgram);

            glClearColor(0.0f,0.0f,0.0f,1.0f);
        }
        void update()
        {
            //
        }
        void render()
        {
            // glClear(GL_COLOR_BUFFER_BIT);
            renderer.draw(PrimitiveType::TRIANGLE,vertexBuffer,6);
        }
        void cleanup()
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(shaderProgram);
            vertexBuffer.destroy();
        }
};
