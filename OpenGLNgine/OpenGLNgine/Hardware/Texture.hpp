#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/GL/Texture.hpp"

#include <memory>

namespace Hardware
{

enum TEXTURE_TYPE
{
    TT_1D,
    TT_2D,
    TT_2DMULTISAMPLE
};

enum TEXTURE_INTERNAL_FORMAT
{
    TIF_DEPTH,
    TIF_DEPTH16,
    TIF_DEPTH24,
    TIF_DEPTH32,
    TIF_DEPTH_STENCIL,
    TIF_DEPTH24_STENCIL8,
    TIF_DEPTH32F_STENCIL8,
    TIF_RED,
    TIF_RG,
    TIF_RGB,
    TIF_RGBA,
    TIF_R8,
    TIF_R8_SNORM,
    TIF_R16,
    TIF_R16_SNORM,
    TIF_RG8,
    TIF_RG8_SNORM,
    TIF_RG16,
    TIF_RG16_SNORM,
    TIF_R3_G3_B2,
    TIF_RGB4,
    TIF_RGB5,
    TIF_RGB8,
    TIF_RGB8_SNORM,
    TIF_RGB10,
    TIF_RGB12,
    TIF_RGB16_SNORM,
    TIF_RGBA2,
    TIF_RGBA4,
    TIF_RGB5_A1,
    TIF_RGBA8,
    TIF_RGBA8_SNORM,
    TIF_RGB10_A2,
    TIF_RGB10_A2UI,
    TIF_RGBA12,
    TIF_RGBA16,
    TIF_SRGB8,
    TIF_SRGB8_ALPHA8,
    TIF_R16F,
    TIF_RG16F,
    TIF_RGB16F,
    TIF_RGBA16F,
    TIF_R32F,
    TIF_RG32F,
    TIF_RGB32F,
    TIF_RGBA32F,
    TIF_R11F_G11F_B10F,
    TIF_RGB9_E5,
    TIF_R8I,
    TIF_R8UI,
    TIF_R16I,
    TIF_R16UI,
    TIF_R32I,
    TIF_R32UI,
    TIF_RG8I,
    TIF_RG8UI,
    TIF_RG16I,
    TIF_RG16UI,
    TIF_RG32I,
    TIF_RG32UI,
    TIF_RGB8I,
    TIF_RGB8UI,
    TIF_RGB16I,
    TIF_RGB16UI,
    TIF_RGB32I,
    TIF_RGB32UI,
    TIF_RGBA8I,
    TIF_RGBA8UI,
    TIF_RGBA16I,
    TIF_RGBA16UI,
    TIF_RGBA32I,
    TIF_RGBA32UI
};

enum TEXTURE_FILTER
{
    TF_LINEAR,
    TF_NEAREST,
    TF_LINEAR_MIPMAP_LINEAR,
    TF_LINEAR_MIPMAP_NEAREST,
    TF_NEAREST_MIPMAP_LINEAR,
    TF_NEAREST_MIPMAP_NEAREST
};

class Texture;
class TextureManager;

typedef std::shared_ptr< Texture > TexturePtr;

class Texture final : public ::Core::IResource
{

public:

    Texture(TextureManager* const _manager, const std::string& _name);

    ~Texture();

    Texture(const Texture&) = delete;

    Texture(Texture&&) = delete;

    Texture& operator=(const Texture&) = delete;

    Texture& operator=(Texture&&) = delete;

    inline void lock();

    inline void unlock();

    void load(const std::filesystem::path& _path, TEXTURE_TYPE _type, TEXTURE_INTERNAL_FORMAT _internalFormat);

    inline void setMagFilter(TEXTURE_FILTER _filter) const;

    inline void setMinFilter(TEXTURE_FILTER _filter) const;

private:

    static ::GL::TEXTURE_INTERNAL_FORMAT getType(TEXTURE_INTERNAL_FORMAT _format);

    static ::GL::TEXTURE_TYPE getType(TEXTURE_TYPE _format);

    static ::GL::TEXTURE_FILTER getType(TEXTURE_FILTER _filter);

    TextureManager* const m_manager;

    ::GL::Texture m_texture;

};

inline void Texture::lock()
{
    m_texture.bind();
}

inline void Texture::unlock()
{
    m_texture.unbind();
}

inline void Texture::setMagFilter(TEXTURE_FILTER _filter) const
{
    m_texture.setMagFilter(getType(_filter));
}

inline void Texture::setMinFilter(TEXTURE_FILTER _filter) const
{
    m_texture.setMinFilter(getType(_filter));
}

}
