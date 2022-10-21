#include <glad/glad.h>

#include "graphics/VertexBuffer.hpp"
#include "graphics/constants.hpp"

namespace fenton
{

namespace graphics
{

VertexBuffer::VertexBuffer()
{
    glGenVertexArrays(1,&m_vaoID);
    glGenBuffers(1,&m_ID);
}

VertexBuffer::~VertexBuffer()
{
    this->destroy();
}

bool VertexBuffer::create(VertexFormat vertexFormat,unsigned int numVertices,void* data,BufferDataUsage usage)
{    
    glBindVertexArray(m_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER,m_ID);

    glBufferData
    (
        GL_ARRAY_BUFFER,
        6 * 3 * sizeof(float), // numVertices*VertexFormatSize[vertexFormat],
        data,
        usage
    );
    if(glGetError() != GL_NO_ERROR)
    {
        this->destroy();
        return false;
    }

    m_vertexFormat = vertexFormat;
    m_numVertices = numVertices;

    unsigned int stride = VertexFormatSize[vertexFormat];
    unsigned int offset = 0;

    switch(vertexFormat)
    {
        case POSITION:
            break;
        default:
            break;
    }

    glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
    glVertexAttribPointer
    (
        SHADER_ATTRIBUTE_POSITION,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (GLvoid*)offset
    );

    // unbind VAO
    glBindVertexArray(0);

    return true;
}

void VertexBuffer::bind()
{
    glBindVertexArray(m_vaoID);
}

void VertexBuffer::destroy()
{
    glDeleteBuffers(1,&m_ID);
    glDeleteVertexArrays(1,&m_vaoID);
    m_ID = m_vaoID = m_numVertices = 0;
}

} // namespace graphics

} // namespace fenton
