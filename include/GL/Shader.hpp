#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>

namespace GL
{

class Shader
{

public:

    enum SHADER_TYPE : GLenum
    {
        ST_VERTEX = GL_VERTEX_SHADER,
        ST_FRAGMENT = GL_FRAGMENT_SHADER,
        ST_GEOMETRY = GL_GEOMETRY_SHADER
    };

public:

    Shader(SHADER_TYPE);
    ~Shader();
    Shader(const Shader&);
    Shader(Shader&&) = delete;
    Shader& operator=(const Shader&);
    Shader& operator=(Shader&&) = delete;

    void compile() const;

    inline SHADER_TYPE getType() const;
    inline GLuint getId() const;

    inline void setSource(const std::string&);
    void setSourceFromFile(const std::filesystem::path&);

private:

    GLuint m_id {0};
    SHADER_TYPE m_type {ST_VERTEX};
    std::string m_sources {};

};

inline Shader::SHADER_TYPE Shader::getType() const
{
    return m_type;
}

inline GLuint Shader::getId() const
{
    return m_id;
}

inline void Shader::setSource(const std::string& src)
{
    m_sources = src;
}

}
