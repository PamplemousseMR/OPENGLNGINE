#pragma once

#include <GL/glew.h>

#include <glm/vec3.hpp>
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
    Uniform& operator=(const Uniform&);

    void operator=(bool);
    void operator=(int);
    void operator=(float);
    void operator=(const glm::vec2&);
    void operator=(const glm::vec3&);
    void operator=(const glm::vec4&);
    void operator=(const glm::mat4&);
    void operator=(const glm::mat3&);

    GLint getLocation() const;
    const std::string& getName() const;

private:

    std::string m_name {};
    GLuint m_program {0};
    GLint m_location {0};

};

}
