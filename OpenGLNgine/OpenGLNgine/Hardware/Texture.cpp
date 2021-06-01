#include "OpenGLNgine/Hardware/Texture.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <algorithm>

namespace Hardware
{

::GL::TEXTURE_TYPE Texture::getType(TEXTURE_TYPE _type)
{
    switch(_type) {
    case TT_1D:
        return ::GL::TT_1D;
    case TT_2D:
        return ::GL::TT_2D;
    case TT_2DMULTISAMPLE:
        return ::GL::TT_2DMULTISAMPLE;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
}

::GL::TEXTURE_INTERNAL_FORMAT Texture::getType(TEXTURE_INTERNAL_FORMAT _format)
{
    switch(_format)
    {
    case TIF_DEPTH:
        return ::GL::TIF_DEPTH;
    case TIF_DEPTH16:
        return ::GL::TIF_DEPTH16;
    case TIF_DEPTH24:
        return ::GL::TIF_DEPTH24;
    case TIF_DEPTH32:
        return ::GL::TIF_DEPTH32;
    case TIF_DEPTH_STENCIL:
        return ::GL::TIF_DEPTH_STENCIL;
    case TIF_DEPTH24_STENCIL8:
        return ::GL::TIF_DEPTH24_STENCIL8;
    case TIF_DEPTH32F_STENCIL8:
        return ::GL::TIF_DEPTH32F_STENCIL8;
    case TIF_RED:
        return ::GL::TIF_RED;
    case TIF_RG:
        return ::GL::TIF_RG;
    case TIF_RGB:
        return ::GL::TIF_RGB;
    case TIF_RGBA:
        return ::GL::TIF_RGBA;
    case TIF_R8:
        return ::GL::TIF_R8;
    case TIF_R8_SNORM:
        return ::GL::TIF_R8_SNORM;
    case TIF_R16:
        return ::GL::TIF_R16;
    case TIF_R16_SNORM:
        return ::GL::TIF_R16_SNORM;
    case TIF_RG8:
        return ::GL::TIF_RG8;
    case TIF_RG8_SNORM:
        return ::GL::TIF_RG8_SNORM;
    case TIF_RG16:
        return ::GL::TIF_RG16;
    case TIF_RG16_SNORM:
        return ::GL::TIF_RG16_SNORM;
    case TIF_R3_G3_B2:
        return ::GL::TIF_R3_G3_B2;
    case TIF_RGB4:
        return ::GL::TIF_RGB4;
    case TIF_RGB5:
        return ::GL::TIF_RGB5;
    case TIF_RGB8:
        return ::GL::TIF_RGB8;
    case TIF_RGB8_SNORM:
        return ::GL::TIF_RGB8_SNORM;
    case TIF_RGB10:
        return ::GL::TIF_RGB10;
    case TIF_RGB12:
        return ::GL::TIF_RGB12;
    case TIF_RGB16_SNORM:
        return ::GL::TIF_RGB16_SNORM;
    case TIF_RGBA2:
        return ::GL::TIF_RGBA2;
    case TIF_RGBA4:
        return ::GL::TIF_RGBA4;
    case TIF_RGB5_A1:
        return ::GL::TIF_RGB5_A1;
    case TIF_RGBA8:
        return ::GL::TIF_RGBA8;
    case TIF_RGBA8_SNORM:
        return ::GL::TIF_RGBA8_SNORM;
    case TIF_RGB10_A2:
        return ::GL::TIF_RGB10_A2;
    case TIF_RGB10_A2UI:
        return ::GL::TIF_RGB10_A2UI;
    case TIF_RGBA12:
        return ::GL::TIF_RGBA12;
    case TIF_RGBA16:
        return ::GL::TIF_RGBA16;
    case TIF_SRGB8:
        return ::GL::TIF_SRGB8;
    case TIF_SRGB8_ALPHA8:
        return ::GL::TIF_SRGB8_ALPHA8;
    case TIF_R16F:
        return ::GL::TIF_R16F;
    case TIF_RG16F:
        return ::GL::TIF_RG16F;
    case TIF_RGB16F:
        return ::GL::TIF_RGB16F;
    case TIF_RGBA16F:
        return ::GL::TIF_RGBA16F;
    case TIF_R32F:
        return ::GL::TIF_R32F;
    case TIF_RG32F:
        return ::GL::TIF_RG32F;
    case TIF_RGB32F:
        return ::GL::TIF_RGB32F;
    case TIF_RGBA32F:
        return ::GL::TIF_RGBA32F;
    case TIF_R11F_G11F_B10F:
        return ::GL::TIF_R11F_G11F_B10F;
    case TIF_RGB9_E5:
        return ::GL::TIF_RGB9_E5;
    case TIF_R8I:
        return ::GL::TIF_R8I;
    case TIF_R8UI:
        return ::GL::TIF_R8UI;
    case TIF_R16I:
        return ::GL::TIF_R16I;
    case TIF_R16UI:
        return ::GL::TIF_R16UI;
    case TIF_R32I:
        return ::GL::TIF_R32I;
    case TIF_R32UI:
        return ::GL::TIF_R32UI;
    case TIF_RG8I:
        return ::GL::TIF_RG8I;
    case TIF_RG8UI:
        return ::GL::TIF_RG8UI;
    case TIF_RG16I:
        return ::GL::TIF_RG16I;
    case TIF_RG16UI:
        return ::GL::TIF_RG16UI;
    case TIF_RG32I:
        return ::GL::TIF_RG32I;
    case TIF_RG32UI:
        return ::GL::TIF_RG32UI;
    case TIF_RGB8I:
        return ::GL::TIF_RGB8I;
    case TIF_RGB8UI:
        return ::GL::TIF_RGB8UI;
    case TIF_RGB16I:
        return ::GL::TIF_RGB16I;
    case TIF_RGB16UI:
        return ::GL::TIF_RGB16UI;
    case TIF_RGB32I:
        return ::GL::TIF_RGB32I;
    case TIF_RGB32UI:
        return ::GL::TIF_RGB32UI;
    case TIF_RGBA8I:
        return ::GL::TIF_RGBA8I;
    case TIF_RGBA8UI:
        return ::GL::TIF_RGBA8UI;
    case TIF_RGBA16I:
        return ::GL::TIF_RGBA16I;
    case TIF_RGBA16UI:
        return ::GL::TIF_RGBA16UI;
    case TIF_RGBA32I:
        return ::GL::TIF_RGBA32I;
    case TIF_RGBA32UI:
        return ::GL::TIF_RGBA32UI;
    default:
        GLNGINE_EXCEPTION("Unhandle texture format");
    }
}

::GL::TEXTURE_FILTER Texture::getType(TEXTURE_FILTER _filter)
{
    switch(_filter) {
    case TF_LINEAR:
        return ::GL::TF_LINEAR;
    case TF_NEAREST:
        return ::GL::TF_NEAREST;
    case TF_LINEAR_MIPMAP_LINEAR:
        return ::GL::TF_LINEAR_MIPMAP_LINEAR;
    case TF_LINEAR_MIPMAP_NEAREST:
        return ::GL::TF_LINEAR_MIPMAP_NEAREST;
    case TF_NEAREST_MIPMAP_LINEAR:
        return ::GL::TF_NEAREST_MIPMAP_LINEAR;
    case TF_NEAREST_MIPMAP_NEAREST:
        return ::GL::TF_NEAREST_MIPMAP_NEAREST;
    default:
        GLNGINE_EXCEPTION("Unhandle texture filter");
    }
}

::GL::TEXTURE_WRAP Texture::getType(TEXTURE_WRAP _mode)
{
    switch(_mode) {
    case TW_REPEAT:
        return ::GL::TW_REPEAT;
    case TW_CLAMP:
        return ::GL::TW_CLAMP;
    case TW_BORDER:
        return ::GL::TW_BORDER;
    case TW_MIRROR:
        return ::GL::TW_MIRROR;
    default:
        GLNGINE_EXCEPTION("Unhandle wrapt mode");
    }
}

Texture::Texture(TextureManager* const _manager, const std::string& _name):
    Core::IResource(_name),
    m_manager(_manager)
{
}

Texture::~Texture()
{
}

void Texture::generateMipMaps()
{
    m_texture.generateMipmap();
    m_mipMapsGenerated = true;
}

void Texture::load(const std::filesystem::path& _path, TEXTURE_TYPE _type, TEXTURE_INTERNAL_FORMAT _internalFormat)
{
    m_texture.load(_path, getType(_type), getType(_internalFormat));
}

}
