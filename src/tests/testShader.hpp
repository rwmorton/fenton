#pragma once

#include "core/App.hpp"
#include "graphics/VertexBuffer.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Shader.hpp"

#include "shaders.hpp"
#include "vertices.hpp"

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
            
            shader.fromSource(vertexSource,fragmentSource);
            shader.use();

            glClearColor(1.0f,0.0f,0.0f,1.0f);
        }
        void update()
        {
            //
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
