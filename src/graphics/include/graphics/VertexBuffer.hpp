#pragma once

#include <glad/glad.h>

#include "graphics/tokens.hpp"

namespace fenton
{

namespace graphics
{

class VertexBuffer final
{
    private:
        GLuint m_ID;
        GLuint m_vaoID;
        VertexFormat m_vertexFormat;
        unsigned int m_numVertices;
    public:
        VertexBuffer();
        ~VertexBuffer();

        bool create(VertexFormat vertexFormat,unsigned int numVertices,void* data,BufferDataUsage usage);
        void bind() const;
        void destroy();
};

} // namespace graphics

} // namespace fenton
