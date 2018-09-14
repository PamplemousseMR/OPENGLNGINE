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
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

public:

    Shader(SHADER_TYPE);
    ~Shader() noexcept;
    Shader(const Shader&);
    Shader& operator=(const Shader&);

    void compile() const;

    inline SHADER_TYPE getType() const noexcept;
    inline GLuint getId() const noexcept;

    inline void setSource(const std::string&) noexcept;
    void setSourceFromFile(const std::filesystem::path&);

private:

    GLuint m_id {0};
    SHADER_TYPE m_type {VERTEX};
    std::string m_sources {};

};

Shader::SHADER_TYPE Shader::getType() const noexcept
{
    return m_type;
}

GLuint Shader::getId() const noexcept
{
    return m_id;
}

void Shader::setSource(const std::string& src) noexcept
{
    m_sources = src;
}

}
