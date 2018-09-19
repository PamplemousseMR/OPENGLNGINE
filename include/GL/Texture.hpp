#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>
#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class Texture : public IGLObject
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
    void loadDepth(int, int);
    inline void generateMipmap() const noexcept;

    inline void bind() const noexcept;
    inline void unbind() const noexcept;

    inline int getLocation() const noexcept;
    inline TEXTURE_TYPE getType() const noexcept;

    inline void setParameter(GLenum, GLint) const noexcept;

private:

    static std::vector<bool> s_location;
    static int s_maxSize;
    static bool s_first;

private:

    TEXTURE_TYPE m_type {TEXTURE_1D};
    bool m_hasAlpha {false};
    int m_location {-1};

};


inline void Texture::bind() const noexcept
{
    glActiveTexture(GLenum(GL_TEXTURE0 + m_location));
    glBindTexture(m_type, m_id);
}

inline void Texture::unbind() const noexcept
{
    glBindTexture(m_type, 0);
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

