#pragma once

#include <GL/glew.h>

#include <assert.h>
#include <filesystem>
#include <string>
#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class Texture : public IGLObject
{

public:

    enum TEXTURE_TYPE
    {
        TYPE_1D,
        TYPE_2D,
        TYPE_DEPTH
    };

    enum TEXTURE_FORMAT
    {
        FORMAT_RGB = GL_RGB,
        FORMAT_RGBA = GL_RGBA,
        FORMAT_DEPTH = GL_DEPTH_COMPONENT,
        FORMAT_DEPTH16 = GL_DEPTH_COMPONENT16,
        FORMAT_DEPTH24 = GL_DEPTH_COMPONENT24,
        FORMAT_DEPTH32 = GL_DEPTH_COMPONENT32
    };

    enum TEXTURE_FILTER
    {
        FILTER_LINEAR = GL_LINEAR,
        FILTER_NEAREST = GL_NEAREST,
        FILTER_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
        FILTER_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        FILTER_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
        FILTER_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST
    };

public:

    Texture(TEXTURE_TYPE);
    ~Texture() noexcept;
    Texture(const Texture&);
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&);
    Texture& operator=(Texture&&) = delete;

    int load(const std::filesystem::path&);
    void allocate(int, int, TEXTURE_FORMAT) const;
    inline void generateMipmap() const noexcept;

    inline void bind() const noexcept;
    inline void unbind() const noexcept;

    inline int getLocation() const noexcept;
    inline TEXTURE_TYPE getType() const noexcept;

    inline void setMagFilter(TEXTURE_FILTER) const noexcept;
    inline void setMinFilter(TEXTURE_FILTER) const noexcept;

private:

    static std::vector<bool> s_location;
    static GLint s_maxSize;
    static bool s_first;

private:

    TEXTURE_TYPE m_type {TYPE_2D};
    GLenum m_glType {GL_TEXTURE_2D};
    int m_location {-1};

};


inline void Texture::bind() const noexcept
{
    glActiveTexture(GLenum(GL_TEXTURE0 + m_location));
    glBindTexture(m_glType, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void Texture::unbind() const noexcept
{
    glBindTexture(m_glType, 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline int Texture::getLocation() const noexcept
{
    return m_location;
}

inline Texture::TEXTURE_TYPE Texture::getType() const noexcept
{
    return m_type;
}

inline void Texture::setMinFilter(TEXTURE_FILTER _filter) const noexcept
{
    glTexParameteri(m_glType, GL_TEXTURE_MIN_FILTER, _filter);
    assert(glGetError() == GL_NO_ERROR);
}

inline void Texture::setMagFilter(TEXTURE_FILTER _filter) const noexcept
{
    glTexParameteri(m_glType, GL_TEXTURE_MAG_FILTER, _filter);
    assert(glGetError() == GL_NO_ERROR);
}

inline void Texture::generateMipmap() const noexcept
{
    glGenerateMipmap(m_glType);
    assert(glGetError() == GL_NO_ERROR);
}

}

