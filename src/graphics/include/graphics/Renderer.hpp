#pragma once

#include "graphics/VertexBuffer.hpp"

namespace fenton
{

namespace graphics
{

class Renderer
{
    private:
    public:
        void draw(PrimitiveType primitiveType,const VertexBuffer& vertexBuffer,unsigned int numVertices);
};

} // namespace graphics

} // namespace fenton
