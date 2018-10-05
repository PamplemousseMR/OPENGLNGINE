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
        TYPE_2DMULTISAMPLE
    };

    enum TEXTURE_INTERNALFORMAT : GLint
    {
        INTERNALFORMAT_DEPTH = GL_DEPTH_COMPONENT,
        INTERNALFORMAT_DEPTH16 = GL_DEPTH_COMPONENT16,
        INTERNALFORMAT_DEPTH24 = GL_DEPTH_COMPONENT24,
        INTERNALFORMAT_DEPTH32 = GL_DEPTH_COMPONENT32,
        INTERNALFORMAT_DEPTH_STENCIL = GL_DEPTH_STENCIL,
        INTERNALFORMAT_DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
        INTERNALFORMAT_DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
        INTERNALFORMAT_RED = GL_RED,
        INTERNALFORMAT_RG = GL_RG,
        INTERNALFORMAT_RGB = GL_RGB,
        INTERNALFORMAT_RGBA = GL_RGBA,
        INTERNALFORMAT_R8 = GL_R8,
        INTERNALFORMAT_R8_SNORM = GL_R8_SNORM,
        INTERNALFORMAT_R16 = GL_R16,
        INTERNALFORMAT_R16_SNORM = GL_R16_SNORM,
        INTERNALFORMAT_RG8 = GL_RG8,
        INTERNALFORMAT_RG8_SNORM = GL_RG8_SNORM,
        INTERNALFORMAT_RG16 = GL_RG16,
        INTERNALFORMAT_RG16_SNORM = GL_RG16_SNORM,
        INTERNALFORMAT_R3_G3_B2 = GL_R3_G3_B2,
        INTERNALFORMAT_RGB4 = GL_RGB4,
        INTERNALFORMAT_RGB5 = GL_RGB5,
        INTERNALFORMAT_RGB8 = GL_RGB8,
        INTERNALFORMAT_RGB8_SNORM = GL_RGB8_SNORM,
        INTERNALFORMAT_RGB10 = GL_RGB10,
        INTERNALFORMAT_RGB12 = GL_RGB12,
        INTERNALFORMAT_RGB16_SNORM = GL_RGB16_SNORM,
        INTERNALFORMAT_RGBA2 = GL_RGBA2,
        INTERNALFORMAT_RGBA4 = GL_RGBA4,
        INTERNALFORMAT_RGB5_A1 = GL_RGB5_A1,
        INTERNALFORMAT_RGBA8 = GL_RGBA8,
        INTERNALFORMAT_RGBA8_SNORM = GL_RGBA8_SNORM,
        INTERNALFORMAT_RGB10_A2 = GL_RGB10_A2,
        INTERNALFORMAT_RGB10_A2UI = GL_RGB10_A2UI,
        INTERNALFORMAT_RGBA12 = GL_RGBA12,
        INTERNALFORMAT_RGBA16 = GL_RGBA16,
        INTERNALFORMAT_SRGB8 = GL_SRGB8,
        INTERNALFORMAT_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
        INTERNALFORMAT_R16F = GL_R16F,
        INTERNALFORMAT_RG16F = GL_RG16F,
        INTERNALFORMAT_RGB16F = GL_RGB16F,
        INTERNALFORMAT_RGBA16F = GL_RGBA16F,
        INTERNALFORMAT_R32F = GL_R32F,
        INTERNALFORMAT_RG32F = GL_RG32F,
        INTERNALFORMAT_RGB32F = GL_RGB32F,
        INTERNALFORMAT_RGBA32F = GL_RGBA32F,
        INTERNALFORMAT_R11F_G11F_B10F = GL_R11F_G11F_B10F,
        INTERNALFORMAT_RGB9_E5 = GL_RGB9_E5,
        INTERNALFORMAT_R8I = GL_R8I,
        INTERNALFORMAT_R8UI = GL_R8UI,
        INTERNALFORMAT_R16I = GL_R16I,
        INTERNALFORMAT_R16UI = GL_R16UI,
        INTERNALFORMAT_R32I = GL_R32I,
        INTERNALFORMAT_R32UI = GL_R32UI,
        INTERNALFORMAT_RG8I = GL_RG8I,
        INTERNALFORMAT_RG8UI = GL_RG8UI,
        INTERNALFORMAT_RG16I = GL_RG16I,
        INTERNALFORMAT_RG16UI = GL_RG16UI,
        INTERNALFORMAT_RG32I = GL_RG32I,
        INTERNALFORMAT_RG32UI = GL_RG32UI,
        INTERNALFORMAT_RGB8I = GL_RGB8I,
        INTERNALFORMAT_RGB8UI = GL_RGB8UI,
        INTERNALFORMAT_RGB16I = GL_RGB16I,
        INTERNALFORMAT_RGB16UI = GL_RGB16UI,
        INTERNALFORMAT_RGB32I = GL_RGB32I,
        INTERNALFORMAT_RGB32UI = GL_RGB32UI,
        INTERNALFORMAT_RGBA8I = GL_RGBA8I,
        INTERNALFORMAT_RGBA8UI = GL_RGBA8UI,
        INTERNALFORMAT_RGBA16I = GL_RGBA16I,
        INTERNALFORMAT_RGBA16UI = GL_RGBA16UI,
        INTERNALFORMAT_RGBA32I = GL_RGBA32I,
        INTERNALFORMAT_RGBA32UI = GL_RGBA32UI
    };

    enum TEXTURE_FORMAT : GLenum
    {
        FORMAT_RED = GL_RED,
        FORMAT_RG = GL_RG,
        FORMAT_RGB = GL_RGB,
        FORMAT_BGR = GL_BGR,
        FORMAT_RGBA = GL_RGBA,
        FORMAT_BGRA = GL_BGRA,
        FORMAT_RED_INTEGER = GL_RED_INTEGER,
        FORMAT_RG_INTEGER = GL_RG_INTEGER,
        FORMAT_RGB_INTEGER = GL_RGB_INTEGER,
        FORMAT_BGR_INTEGER = GL_BGR_INTEGER,
        FORMAT_RGBA_INTEGER = GL_RGBA_INTEGER,
        FORMAT_BGRA_INTEGER = GL_BGRA_INTEGER,
        FORMAT_STENCIL_INDEX = GL_STENCIL_INDEX,
        FORMAT_DEPTH = GL_DEPTH_COMPONENT,
        FORMAT_DEPTH_STENCIL = GL_DEPTH_STENCIL
    };

    enum TEXTURE_FILTER : GLint
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
    ~Texture() noexcept override;
    Texture(const Texture&);
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&);
    Texture& operator=(Texture&&) = delete;

    int load(const std::filesystem::path&, TEXTURE_INTERNALFORMAT);
    void allocate(int, int, TEXTURE_INTERNALFORMAT, TEXTURE_FORMAT);
    inline void generateMipmap() const;

    inline void bind() const noexcept override;
    inline void unbind() const noexcept override;

    inline int getLocation() const noexcept;
    inline TEXTURE_TYPE getType() const noexcept;

    inline void setMagFilter(TEXTURE_FILTER) const;
    inline void setMinFilter(TEXTURE_FILTER) const;

private:

    static std::vector<bool> s_location;
    static GLint s_maxSize;
    static GLint s_maxSample;
    static bool s_first;

private:

    void genTexture();

private:

    TEXTURE_TYPE m_type {TYPE_2D};
    TEXTURE_FORMAT m_format {FORMAT_RGBA};
    int m_location {-1};

};


inline void Texture::bind() const noexcept
{
    glActiveTexture(GLenum(GL_TEXTURE0 + m_location));
    switch(m_type)
    {
        case TYPE_1D :
            glBindTexture(GL_TEXTURE_1D, m_id);
        break;
        case TYPE_2D :
            glBindTexture(GL_TEXTURE_2D, m_id);
        break;
        case TYPE_2DMULTISAMPLE :
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_id);
        break;
    }
    assert(glGetError() == GL_NO_ERROR);
}

inline void Texture::unbind() const noexcept
{
    switch(m_type)
    {
        case TYPE_1D :
            glBindTexture(GL_TEXTURE_1D, 0);
        break;
        case TYPE_2D :
            glBindTexture(GL_TEXTURE_2D, 0);
        break;
        case TYPE_2DMULTISAMPLE :
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        break;
    }
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

inline void Texture::setMinFilter(TEXTURE_FILTER _filter) const
{
    switch(m_type)
    {
        case TYPE_1D :
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, _filter);
        break;
        case TYPE_2D :
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);
        break;
        case TYPE_2DMULTISAMPLE :
        throw std::invalid_argument("[Texture] Can't set filter to multisampled textures");
        break;
    }
    assert(glGetError() == GL_NO_ERROR);
}

inline void Texture::setMagFilter(TEXTURE_FILTER _filter) const
{
    switch(m_type)
    {
        case TYPE_1D :
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, _filter);
        break;
        case TYPE_2D :
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
        break;
        case TYPE_2DMULTISAMPLE :
            throw std::invalid_argument("[Texture] Can't set filter to multisampled textures");
        break;
    }
    assert(glGetError() == GL_NO_ERROR);
}

inline void Texture::generateMipmap() const
{
    switch(m_type)
    {
        case TYPE_1D :
            glGenerateMipmap(GL_TEXTURE_1D);
        break;
        case TYPE_2D :
            glGenerateMipmap(GL_TEXTURE_2D);
        break;
        case TYPE_2DMULTISAMPLE :
            throw std::invalid_argument("[Texture] Can't generate mipmap to multisampled textures");
        break;
    }
    assert(glGetError() == GL_NO_ERROR);
}

}

