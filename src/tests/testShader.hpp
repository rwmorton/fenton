#pragma once

#include "core/App.hpp"
#include "graphics/VertexBuffer.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Shader.hpp"

#include "constants.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace fenton::core;
using namespace fenton::graphics;

class TestShader : public App
{
    private:
        Renderer renderer;
        VertexBuffer vertexBuffer;
        Shader shader;
    public:
        TestShader(int w,int h,const std::string& title,bool poll,bool fullscreen) : App(w,h,title,poll,fullscreen)
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
            
            const std::string vs = TEST_SHADERS_DIR + "vertexShader_glm_test.vert";
            const std::string fs = TEST_SHADERS_DIR + "fragShader.frag";
            shader.fromFile(vs,fs);

            glClearColor(1.0f,0.0f,0.0f,1.0f);
        }
        void update()
        {
            // set up uniforms
            glm::mat4 transform = glm::mat4(1.0f);
            //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
            transform = glm::rotate
            (
                transform,
                static_cast<float>(m_clock.current()),
                glm::vec3(0.0f,0.0f,1.0f)
            );

            shader.use();
            GLuint transformLoc = glGetUniformLocation(shader.getID(),"transform");
            glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform));
        }
        void render()
        {
            renderer.draw(PrimitiveType::TRIANGLE,vertexBuffer,6);
        }
        void cleanup()
        {
            vertexBuffer.destroy();
        }
};
