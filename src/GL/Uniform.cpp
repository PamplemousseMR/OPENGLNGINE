#include "GL/Uniform.hpp"

#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

namespace GL
{
    Uniform::Uniform(const string& name, GLuint program) :
        m_name(name),
        m_program(program),
        m_location(glGetUniformLocation(program, name.c_str()))
    {
    }

    Uniform::~Uniform()
    {
    }

    Uniform::Uniform(const Uniform& _uniform) :
        m_name(_uniform.m_name),
        m_location(glGetUniformLocation(_uniform.m_program, _uniform.m_name.c_str()))
    {
    }

    Uniform& Uniform::operator=(const Uniform& _uniform)
    {
        if (this != &_uniform)
        {
            m_name = _uniform.m_name;
            m_location = glGetUniformLocation(_uniform.m_program, _uniform.m_name.c_str());
        }
        return *this;
    }

    GLuint Uniform::getLocation() const
    {
        return m_location;
    }

    const string& Uniform::getName() const
    {
        return m_name;
    }

    void Uniform::operator=(bool _t)
    {
        glUniform1i(m_location, _t ? 1 : 0);
    }

    void Uniform::operator=(int _t)
    {
        glUniform1i(m_location, _t);
    }

    void Uniform::operator=(float _t)
    {
        glUniform1f(m_location, _t);
    }
    void Uniform::operator=(const vec2& _t)
    {
        glUniform2f(m_location, _t.x, _t.y);
    }

    void Uniform::operator=(const vec3& _t)
    {
        glUniform3f(m_location, _t.x, _t.y, _t.z);
    }

    void Uniform::operator=(const vec4& _t)
    {
        glUniform4f(m_location, _t.x, _t.y, _t.z, _t.w);
    }

    void Uniform::operator=(const mat4& _t)
    {
        glUniformMatrix4fv(m_location, 1, false, value_ptr(_t));
    }

    void Uniform::operator= (const mat3& _t)
    {
        glUniformMatrix3fv(m_location, 1, false, value_ptr(_t));
    }
}
