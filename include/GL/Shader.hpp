#pragma once

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace GL
{

enum SHADER_TYPE
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader
{

public:

    Shader(SHADER_TYPE);
    ~Shader();
    Shader(const Shader&);
    Shader& operator=(const Shader&);

	void compile() const throw();

    GLenum getType() const;
    GLuint getId() const;

    void setSource(const std::string&);
	void setSourceFromFile(const std::string&) throw();

private:

    GLuint m_id;
    SHADER_TYPE m_type;
    std::string m_sources;
};

}
