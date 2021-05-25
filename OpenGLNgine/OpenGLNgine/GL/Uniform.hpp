#pragma once

#include "OpenGLNgine/Core/Exception.hpp"

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <string>

namespace GL
{

class Uniform final
{

public:

    Uniform(const std::string&, GLuint);

    ~Uniform();

    Uniform(const Uniform&);

    Uniform& operator=(const Uniform&);

    Uniform(Uniform&&) = delete;

    Uniform& operator=(Uniform&&) = delete;

    inline void operator=(bool) const;

    inline void operator=(int) const;

    inline void operator=(float) const;

    inline void operator=(const ::glm::vec2&) const;

    inline void operator=(const ::glm::vec3&) const;

    inline void operator=(const ::glm::vec4&) const;

    inline void operator=(const ::glm::mat4&) const;

    inline void operator=(const ::glm::mat3&) const;

    inline GLint getLocation() const;

    inline const std::string& getName() const;

private:

    std::string m_name {};

    GLint m_location {0};

};

inline GLint Uniform::getLocation() const
{
    return m_location;
}

inline const std::string& Uniform::getName() const
{
    return m_name;
}

inline void Uniform::operator=(bool _t) const
{
    glUniform1i(m_location, _t ? 1 : 0);
    GLNGINE_CHECK_GL;
}

inline void Uniform::operator=(int _t) const
{
    glUniform1i(m_location, _t);
    GLNGINE_CHECK_GL;
}

inline void Uniform::operator=(float _t) const
{
    glUniform1f(m_location, _t);
    GLNGINE_CHECK_GL;
}

inline void Uniform::operator=(const ::glm::vec2& _t) const
{
    glUniform2f(m_location, _t.x, _t.y);
    GLNGINE_CHECK_GL;
}

inline void Uniform::operator=(const ::glm::vec3& _t) const
{
    glUniform3f(m_location, _t.x, _t.y, _t.z);
    GLNGINE_CHECK_GL;
}

inline void Uniform::operator=(const ::glm::vec4& _t) const
{
    glUniform4f(m_location, _t.x, _t.y, _t.z, _t.w);
    GLNGINE_CHECK_GL;
}

void Uniform::operator=(const ::glm::mat4& _t) const
{
    glUniformMatrix4fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
    GLNGINE_CHECK_GL;
}

void Uniform::operator= (const ::glm::mat3& _t) const
{
    glUniformMatrix3fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
    GLNGINE_CHECK_GL;
}

}
