#pragma once

#include <glad/glad.h>

#include <string>

namespace fenton
{

namespace graphics
{

class Shader
{
    private:
        GLuint m_ID;
    public:
        Shader();
        ~Shader();
        
        void fromFile(const std::string& vertexPath,const std::string& fragmentPath);
        void fromSource(const std::string& vertexSource,const std::string& fragmentSource);
        void use();
};

} // namespace graphics

} // namespace fenton
