#pragma once

#include <GL/glew.h>

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <string>

namespace GL
{

class Uniform
{

public:

    Uniform(const std::string&, GLuint);
    ~Uniform();
    Uniform(const Uniform&);
    Uniform(Uniform&&) = delete;
    Uniform& operator=(const Uniform&);
    Uniform& operator=(Uniform&&) = delete;

    inline void operator=(bool);
    inline void operator=(int);
    inline void operator=(float);
    inline void operator=(const glm::vec2&);
    inline void operator=(const glm::vec3&);
    inline void operator=(const glm::vec4&);
    inline void operator=(const glm::mat4&);
    inline void operator=(const glm::mat3&);

    inline GLint getLocation() const;
    inline const std::string& getName() const;

private:

    std::string m_name {};
    GLuint m_program {0};
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

inline void Uniform::operator=(bool _t)
{
    glUniform1i(m_location, _t ? 1 : 0);
}

inline void Uniform::operator=(int _t)
{
    glUniform1i(m_location, _t);
}

inline void Uniform::operator=(float _t)
{
    glUniform1f(m_location, _t);
}

inline void Uniform::operator=(const glm::vec2& _t)
{
    glUniform2f(m_location, _t.x, _t.y);
}

inline void Uniform::operator=(const glm::vec3& _t)
{
    glUniform3f(m_location, _t.x, _t.y, _t.z);
}

inline void Uniform::operator=(const glm::vec4& _t)
{
    glUniform4f(m_location, _t.x, _t.y, _t.z, _t.w);
}

inline void Uniform::operator=(const glm::mat4& _t)
{
    glUniformMatrix4fv(m_location, 1, false, value_ptr(_t));
}

inline void Uniform::operator= (const glm::mat3& _t)
{
    glUniformMatrix3fv(m_location, 1, false, value_ptr(_t));
}

}
