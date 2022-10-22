#include "graphics/Renderer.hpp"

namespace fenton
{

namespace graphics
{

void Renderer::draw(PrimitiveType primitiveType,const VertexBuffer& vertexBuffer,unsigned int numVertices)
{
    vertexBuffer.bind();
    glDrawArrays(primitiveType,0,numVertices);
}

} // namespace graphics

} // namespace fenton
