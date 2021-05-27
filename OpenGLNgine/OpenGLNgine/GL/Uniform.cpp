#include "OpenGLNgine/GL/Uniform.hpp"

namespace GL
{

Uniform::Uniform(const std::string& _name, GLuint _program) :
    m_name(_name),
    m_location(glGetUniformLocation(_program, _name.c_str()))
{
    GLNGINE_CHECK_GL;
}

Uniform::~Uniform()
{
}

Uniform::Uniform(const Uniform& _uniform) :
    m_name(_uniform.m_name),
    m_location(_uniform.m_location)
{
}

Uniform& Uniform::operator=(const Uniform& _uniform)
{
    if(this != &_uniform)
    {
        m_name = _uniform.m_name;
        m_location = _uniform.m_location;
    }
    return *this;
}

void Uniform::operator= (const ::glm::mat3& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    //if(!m_m3Cache || m_m3Cache.value() != _t)
    {
        m_m3Cache = _t;
        glUniformMatrix3fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
        GLNGINE_CHECK_GL;
    }
#else
glUniformMatrix3fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
#endif
}

void Uniform::operator=(const ::glm::mat4& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_m4Cache || m_m4Cache.value() != _t)
    {
        m_m4Cache = _t;
        glUniformMatrix4fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
        GLNGINE_CHECK_GL;
    }
#else
glUniformMatrix4fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
#endif
}

}
