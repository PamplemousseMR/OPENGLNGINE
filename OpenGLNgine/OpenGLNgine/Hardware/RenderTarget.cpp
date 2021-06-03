#include "OpenGLNgine/Hardware/RenderTarget.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <algorithm>

namespace Hardware
{

void RenderTarget::attach(unsigned _location)
{
    TextureList::const_iterator it = m_textures.find(_location);
    if(it == m_textures.end())
    {
        GLNGINE_EXCEPTION("The texture '" + std::to_string(_location) + "'doesn't exists");
    }
    switch (it->second.second) {
    case TIF_DEPTH:
    case TIF_DEPTH16:
    case TIF_DEPTH24:
    case TIF_DEPTH32:
        m_frameBuffer.attachDepthTexture(it->second.first);
        break;
    case TIF_DEPTH_STENCIL:
    case TIF_DEPTH24_STENCIL8:
    case TIF_DEPTH32F_STENCIL8:
        m_frameBuffer.attachDepthStencilTexture(it->second.first);
        break;
    case TIF_RED:
    case TIF_RG:
    case TIF_RGB:
    case TIF_RGBA:
    case TIF_R8:
    case TIF_R8_SNORM:
    case TIF_R16:
    case TIF_R16_SNORM:
    case TIF_RG8:
    case TIF_RG8_SNORM:
    case TIF_RG16:
    case TIF_RG16_SNORM:
    case TIF_R3_G3_B2:
    case TIF_RGB4:
    case TIF_RGB5:
    case TIF_RGB8:
    case TIF_RGB8_SNORM:
    case TIF_RGB10:
    case TIF_RGB12:
    case TIF_RGB16_SNORM:
    case TIF_RGBA2:
    case TIF_RGBA4:
    case TIF_RGB5_A1:
    case TIF_RGBA8:
    case TIF_RGBA8_SNORM:
    case TIF_RGB10_A2:
    case TIF_RGB10_A2UI:
    case TIF_RGBA12:
    case TIF_RGBA16:
    case TIF_SRGB8:
    case TIF_SRGB8_ALPHA8:
    case TIF_R16F:
    case TIF_RG16F:
    case TIF_RGB16F:
    case TIF_RGBA16F:
    case TIF_R32F:
    case TIF_RG32F:
    case TIF_RGB32F:
    case TIF_RGBA32F:
    case TIF_R11F_G11F_B10F:
    case TIF_RGB9_E5:
    case TIF_R8I:
    case TIF_R8UI:
    case TIF_R16I:
    case TIF_R16UI:
    case TIF_R32I:
    case TIF_R32UI:
    case TIF_RG8I:
    case TIF_RG8UI:
    case TIF_RG16I:
    case TIF_RG16UI:
    case TIF_RG32I:
    case TIF_RG32UI:
    case TIF_RGB8I:
    case TIF_RGB8UI:
    case TIF_RGB16I:
    case TIF_RGB16UI:
    case TIF_RGB32I:
    case TIF_RGB32UI:
    case TIF_RGBA8I:
    case TIF_RGBA8UI:
    case TIF_RGBA16I:
    case TIF_RGBA16UI:
    case TIF_RGBA32I:
    case TIF_RGBA32UI:
        m_frameBuffer.attachColorTexture(it->second.first, _location);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture format");
        break;
    }
}

void RenderTarget::addTexture(TEXTURE_INTERNAL_FORMAT _format, unsigned _location)
{
    m_textures.emplace(_location, std::make_pair(::GL::Texture(), _format));
    m_dirty = true;
}

void RenderTarget::removeTexture(unsigned _location)
{
    TextureList::const_iterator it = m_textures.find(_location);
    if(it == m_textures.end())
    {
        GLNGINE_EXCEPTION("The texture '" + std::to_string(_location) + "'doesn't exists");
    }
    m_textures.erase(it);
    m_dirty = true;
}

void RenderTarget::removeAllTextures()
{
    m_textures.clear();
    m_dirty = true;
}

RenderTarget::RenderTarget(RenderTargetManager* const _manager, const std::string& _name):
    ::Core::IResource(_name),
    m_manager(_manager)
{
}

RenderTarget::~RenderTarget()
{
    this->removeAllTextures();
}

}
