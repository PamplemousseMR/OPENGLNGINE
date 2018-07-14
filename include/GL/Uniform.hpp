#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    GLuint getLocation() const;
    const std::string& getName() const;

private:

    GLuint m_program {0};
    GLuint m_location {0};
    std::string m_name {};

};

}
