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

    enum TEXTURE_TYPE : GLenum
    {
        TEXTURE_1D = GL_TEXTURE_1D,
        TEXTURE_2D = GL_TEXTURE_2D,
    };

public:

    Texture(TEXTURE_TYPE);
    ~Texture() noexcept;
    Texture(const Texture&);
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&);
    Texture& operator=(Texture&&) = delete;

    int load(const std::filesystem::path&);
    void loadRGBA(int, int);
    inline void generateMipmap() const noexcept;
    void bind() const noexcept;
    void unbind() const noexcept;

    inline GLuint getId() const noexcept;
    inline int getLocation() const noexcept;
    inline TEXTURE_TYPE getType() const noexcept;

    inline void setParameter(GLenum, GLint) const noexcept;

private:

    static std::vector<bool> s_location;
    static bool s_first;

private:

    TEXTURE_TYPE m_type {TEXTURE_1D};
    bool m_hasAlpha {false};
    GLuint m_id {0};
    int m_location {-1};

};

inline GLuint Texture::getId() const noexcept
{
    return m_id;
}

inline int Texture::getLocation() const noexcept
{
    return m_location;
}

inline Texture::TEXTURE_TYPE Texture::getType() const noexcept
{
    return m_type;
}

inline void Texture::setParameter(GLenum pname, GLint param) const noexcept
{
    glTexParameteri(m_type, pname, param);
}

inline void Texture::generateMipmap() const noexcept
{
    glGenerateMipmap(m_type);
}

}

