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

}
