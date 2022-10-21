#pragma once

#include <glad/glad.h>

namespace fenton
{

namespace graphics
{

struct Vector3
{
    float x,y,z;
};

enum VertexFormat
{
    POSITION
};

const int VertexFormatSize[] =
{
    sizeof(Vector3)
};

enum BufferDataUsage
{
    DEFAULT         = GL_STATIC_DRAW,
    IMMUTABLE       = GL_STATIC_DRAW,
    DYNAMIC         = GL_DYNAMIC_DRAW
};

enum PrimitiveType
{
    POINT           = GL_POINTS,
    LINE            = GL_LINES,
    TRIANGLE        = GL_TRIANGLES
};

} // namespace graphics

} // namespace fenton
