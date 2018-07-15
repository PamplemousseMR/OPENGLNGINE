#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>
#include <vector>

namespace GL
{

class Texture
{

public:

    enum TEXTURE_TYPE
    {
        TEXTURE_1D = GL_TEXTURE_1D,
        TEXTURE_2D = GL_TEXTURE_2D,
    };

public:

    Texture(TEXTURE_TYPE) noexcept;
    ~Texture() noexcept;
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    int load(const std::filesystem::path&);
    void generateMipmap() const noexcept;
    void bind();
    void unbind() noexcept;

    inline GLuint getId() const noexcept;
    inline int getLocation() const noexcept;
    inline TEXTURE_TYPE getType() const noexcept;

    void setParameter(GLenum, GLint) const noexcept;

private:

    static std::vector<bool> s_location;
    static bool s_first;

private:

    TEXTURE_TYPE m_type {TEXTURE_1D};
    bool m_hasAlpha {false};
    GLuint m_id {0};
    int m_location {-1};

};

GLuint Texture::getId() const noexcept
{
    return m_id;
}

int Texture::getLocation() const noexcept
{
    return m_location;
}

Texture::TEXTURE_TYPE Texture::getType() const noexcept
{
    return m_type;
}

}

