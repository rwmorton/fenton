#include "graphics/Shader.hpp"
#include "core/utils.hpp"

#include <fstream>
#include <iostream>

#include <glad/glad.h>

namespace fenton
{

namespace graphics
{

Shader::Shader() {}

Shader::~Shader()
{
    glDeleteShader(m_ID);
}

void Shader::fromFile(const std::string& vertexPath,const std::string& fragmentPath)
{
    this->fromSource(
        fenton::core::readFile(vertexPath),
        fenton::core::readFile(fragmentPath)
    );
}

void Shader::fromSource(const std::string& vertexSource,const std::string& fragmentSource)
{
    int success;
    char infoLog[512];
    
    const char* vSrc = vertexSource.c_str();
    const char* fSrc = fragmentSource.c_str();

    // vertex shader
    GLuint v_ID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_ID,1,&vSrc,nullptr);
    glCompileShader(v_ID);
    glGetShaderiv(v_ID,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(v_ID,512,nullptr,infoLog);
        std::cerr << "Error: Could not compile vertex shader\n" << infoLog << std::endl;
    }

    // fragment shader
    GLuint f_ID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_ID,1,&fSrc,nullptr);
    glCompileShader(f_ID);
    glGetShaderiv(f_ID,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(f_ID,512,nullptr,infoLog);
        std::cerr << "Error: Could not compile fragment shader\n" << infoLog << std::endl;
    }

    // shader program
    if(m_ID != 0)
    {
        glDeleteShader(m_ID);
    }
    m_ID = glCreateProgram();
    glAttachShader(m_ID,v_ID);
    glAttachShader(m_ID,f_ID);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(m_ID,512,nullptr,infoLog);
        std::cerr << "Error: could not link shader program\n" << infoLog << std::endl;
    }

    glDeleteShader(v_ID);
    glDeleteShader(f_ID);
}

void Shader::use()
{
    glUseProgram(m_ID);
}

} // namespace graphics

} // namespace fenton
