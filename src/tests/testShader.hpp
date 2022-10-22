#pragma once

#include "core/App.hpp"
#include "graphics/VertexBuffer.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Camera.hpp"

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
        Camera camera;
        GLuint modelLoc,viewLoc,projectionLoc;
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
            modelLoc = glGetUniformLocation(shader.getID(),"model");
            viewLoc = glGetUniformLocation(shader.getID(),"view");
            projectionLoc = glGetUniformLocation(shader.getID(),"projection");

            camera.Position = glm::vec3(0.0f,0.0f,5.0f);

            glClearColor(1.0f,0.0f,0.0f,1.0f);

            //camera
            mapCallbackToInput(Key::W,[this]()
            {
                camera.ProcessKeyboard(CameraMovement::FORWARD,static_cast<float>(m_clock.elapsed()));
            });
            mapCallbackToInput(Key::S,[this]()
            {
                camera.ProcessKeyboard(CameraMovement::BACKWARD,static_cast<float>(m_clock.elapsed()));
            });
            mapCallbackToInput(Key::A,[this]()
            {
                camera.ProcessKeyboard(CameraMovement::LEFT,static_cast<float>(m_clock.elapsed()));
            });
            mapCallbackToInput(Key::D,[this]()
            {
                camera.ProcessKeyboard(CameraMovement::RIGHT,static_cast<float>(m_clock.elapsed()));
            });
        }
        void update()
        {
            shader.use();

            // set up uniforms
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate
            (
                model,
                static_cast<float>(m_clock.current()), // glm::radians(-55.0f),
                glm::vec3(1.0f,0.0f,0.0f)
            );
            shader.setMat4("model",model);

            camera.ProcessMouseMovement(m_cursorOffsetX,m_cursorOffsetY);
            camera.ProcessMouseScroll(m_scrollY);
            glm::mat4 view = camera.getViewMatrix();
            shader.setMat4("view",view);

            glm::mat4 projection = glm::perspective
            (
                glm::radians(camera.Zoom),
                800.0f / 600.0f,
                0.1f,
                100.0f
            );
            // projection = glm::mat4(1.0f);
            shader.setMat4("projection",projection);

            glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));
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
