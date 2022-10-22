#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

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

        GLuint getID()
        {
            return m_ID;
        }
        
        void setVec3(const std::string& name,const glm::vec3& value) const
        {
            glUniform3fv(glGetUniformLocation(m_ID,name.c_str()),1,&value[0]);
        }

        void setMat4(const std::string& name,const glm::mat4& value) const
        {
            glUniformMatrix4fv(glGetUniformLocation(m_ID,name.c_str()),1,GL_FALSE,&value[0][0]);
        }
};

} // namespace graphics

} // namespace fenton
