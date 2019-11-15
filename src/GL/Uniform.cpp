#include "GL/Uniform.hpp"

using namespace std;
using namespace glm;

namespace GL
{
    Uniform::Uniform(const string& name, GLuint program) :
        m_name(name),
        m_location(glGetUniformLocation(program, name.c_str()))
    {
        assert(glGetError() == GL_NO_ERROR);
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
