#pragma once

#include "OpenGLNgine/GL/IBindable.hpp"
#include "OpenGLNgine/Core/Exception.hpp"

#include <GL/glew.h>

#include <filesystem>

namespace GL
{

enum TEXTURE_TYPE
{
    TT_1D,
    TT_2D,
    TT_2DMULTISAMPLE
};

enum TEXTURE_INTERNAL_FORMAT : GLint
{
    TIF_DEPTH = GL_DEPTH_COMPONENT,
    TIF_DEPTH16 = GL_DEPTH_COMPONENT16,
    TIF_DEPTH24 = GL_DEPTH_COMPONENT24,
    TIF_DEPTH32 = GL_DEPTH_COMPONENT32,
    TIF_DEPTH_STENCIL = GL_DEPTH_STENCIL,
    TIF_DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
    TIF_DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
    TIF_RED = GL_RED,
    TIF_RG = GL_RG,
    TIF_RGB = GL_RGB,
    TIF_RGBA = GL_RGBA,
    TIF_R8 = GL_R8,
    TIF_R8_SNORM = GL_R8_SNORM,
    TIF_R16 = GL_R16,
    TIF_R16_SNORM = GL_R16_SNORM,
    TIF_RG8 = GL_RG8,
    TIF_RG8_SNORM = GL_RG8_SNORM,
    TIF_RG16 = GL_RG16,
    TIF_RG16_SNORM = GL_RG16_SNORM,
    TIF_R3_G3_B2 = GL_R3_G3_B2,
    TIF_RGB4 = GL_RGB4,
    TIF_RGB5 = GL_RGB5,
    TIF_RGB8 = GL_RGB8,
    TIF_RGB8_SNORM = GL_RGB8_SNORM,
    TIF_RGB10 = GL_RGB10,
    TIF_RGB12 = GL_RGB12,
    TIF_RGB16_SNORM = GL_RGB16_SNORM,
    TIF_RGBA2 = GL_RGBA2,
    TIF_RGBA4 = GL_RGBA4,
    TIF_RGB5_A1 = GL_RGB5_A1,
    TIF_RGBA8 = GL_RGBA8,
    TIF_RGBA8_SNORM = GL_RGBA8_SNORM,
    TIF_RGB10_A2 = GL_RGB10_A2,
    TIF_RGB10_A2UI = GL_RGB10_A2UI,
    TIF_RGBA12 = GL_RGBA12,
    TIF_RGBA16 = GL_RGBA16,
    TIF_SRGB8 = GL_SRGB8,
    TIF_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
    TIF_R16F = GL_R16F,
    TIF_RG16F = GL_RG16F,
    TIF_RGB16F = GL_RGB16F,
    TIF_RGBA16F = GL_RGBA16F,
    TIF_R32F = GL_R32F,
    TIF_RG32F = GL_RG32F,
    TIF_RGB32F = GL_RGB32F,
    TIF_RGBA32F = GL_RGBA32F,
    TIF_R11F_G11F_B10F = GL_R11F_G11F_B10F,
    TIF_RGB9_E5 = GL_RGB9_E5,
    TIF_R8I = GL_R8I,
    TIF_R8UI = GL_R8UI,
    TIF_R16I = GL_R16I,
    TIF_R16UI = GL_R16UI,
    TIF_R32I = GL_R32I,
    TIF_R32UI = GL_R32UI,
    TIF_RG8I = GL_RG8I,
    TIF_RG8UI = GL_RG8UI,
    TIF_RG16I = GL_RG16I,
    TIF_RG16UI = GL_RG16UI,
    TIF_RG32I = GL_RG32I,
    TIF_RG32UI = GL_RG32UI,
    TIF_RGB8I = GL_RGB8I,
    TIF_RGB8UI = GL_RGB8UI,
    TIF_RGB16I = GL_RGB16I,
    TIF_RGB16UI = GL_RGB16UI,
    TIF_RGB32I = GL_RGB32I,
    TIF_RGB32UI = GL_RGB32UI,
    TIF_RGBA8I = GL_RGBA8I,
    TIF_RGBA8UI = GL_RGBA8UI,
    TIF_RGBA16I = GL_RGBA16I,
    TIF_RGBA16UI = GL_RGBA16UI,
    TIF_RGBA32I = GL_RGBA32I,
    TIF_RGBA32UI = GL_RGBA32UI
};

enum TEXTURE_FORMAT : GLenum
{
    TF_RED = GL_RED,
    TF_RG = GL_RG,
    TF_RGB = GL_RGB,
    TF_BGR = GL_BGR,
    TF_RGBA = GL_RGBA,
    TF_BGRA = GL_BGRA,
    TF_RED_INTEGER = GL_RED_INTEGER,
    TF_RG_INTEGER = GL_RG_INTEGER,
    TF_RGB_INTEGER = GL_RGB_INTEGER,
    TF_BGR_INTEGER = GL_BGR_INTEGER,
    TF_RGBA_INTEGER = GL_RGBA_INTEGER,
    TF_BGRA_INTEGER = GL_BGRA_INTEGER,
    TF_STENCIL_INDEX = GL_STENCIL_INDEX,
    TF_DEPTH = GL_DEPTH_COMPONENT,
    TF_DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum TEXTURE_DATA : GLenum
{
    TD_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    TD_BYTE = GL_BYTE,
    TD_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    TD_SHORT = GL_SHORT,
    TD_UNSIGNED_INT = GL_UNSIGNED_INT,
    TD_INT = GL_INT,
    TD_FLOAT = GL_FLOAT,
    TD_UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8,
    TD_UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    TD_UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    TD_UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    TD_UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    TD_UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    TD_UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    TD_UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    TD_UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    TD_UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    TD_UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    TD_UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    TD_UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};

enum TEXTURE_FILTER : GLint
{
    TF_LINEAR = GL_LINEAR,
    TF_NEAREST = GL_NEAREST,
    TF_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
    TF_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    TF_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    TF_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST
};

class Texture final : public IBindable
{

public:

    Texture(TEXTURE_TYPE);

    ~Texture() override;

    Texture(const Texture&);

    Texture& operator=(const Texture&);

    Texture(Texture&&) = delete;

    Texture& operator=(Texture&&) = delete;

    static void setLocation(int);

    int load(const std::filesystem::path& _path, TEXTURE_INTERNAL_FORMAT _internalFormat);

    void allocate(int _width, int _height, TEXTURE_INTERNAL_FORMAT _internalFormat, TEXTURE_FORMAT _format, TEXTURE_DATA _data);

    void allocateMultisample(int _width, int _height, TEXTURE_INTERNAL_FORMAT _internalFormat, TEXTURE_FORMAT _format, int _sample);

    void generateMipmap() const;

    inline TEXTURE_TYPE getType() const;

    void setMagFilter(TEXTURE_FILTER _filter) const;

    void setMinFilter(TEXTURE_FILTER _filter) const;

    void bind() const override;

    void unbind() const override;

private:

    /// Automaticaly called one time.
    struct Initializer final
    {
        /// Gets the max size of textures.
        Initializer();
    };

    static GLint s_MAX_SIZE;

    static GLint s_MAX_SAMPLE;

    static GLint s_MAX_LOCATION;

    void genTexture();

    TEXTURE_TYPE m_type {TT_2D};

    TEXTURE_FORMAT m_format {TF_RGBA};

#ifdef GLNGINE_USE_STATE_CACHE
    /// Defines the bind status.
    mutable bool m_isBinded { false };
#endif

};

inline TEXTURE_TYPE Texture::getType() const
{
    return m_type;
}

}

