#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/GL/FrameBuffer.hpp"
#include "OpenGLNgine/GL/Texture.hpp"
#include "OpenGLNgine/Hardware/Pass.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

#include <memory>

namespace Hardware
{

class RenderTarget;
class RenderTargetManager;

typedef std::shared_ptr< RenderTarget > RenderTargetPtr;

class RenderTarget final : public ::Core::IResource
{

    friend RenderTargetManager;

public:

    typedef std::vector< std::pair< std::shared_ptr< ::GL::Texture >, TEXTURE_INTERNAL_FORMAT > > TextureList;

    ~RenderTarget();

    RenderTarget(const RenderTarget&) = delete;

    RenderTarget(RenderTarget&&) = delete;

    RenderTarget& operator=(const RenderTarget&) = delete;

    RenderTarget& operator=(RenderTarget&&) = delete;

    inline void lockDraw();

    inline void lockRead();

    void allocate(int _width, int _height);

    void attach();

    inline void check() const;

    void pushTexture(TEXTURE_INTERNAL_FORMAT _format);

    inline bool isDirty() const;

    inline void setDirty();

    inline void _notifyDirty() const;

    float m_widthScale { 1.f };

    float m_heightScale { 1.f };

    const unsigned m_sample;

private:

    RenderTarget(RenderTargetManager* const _manager, const std::string& _name, unsigned _sample);

    RenderTargetManager* const m_manager;

    ::GL::FrameBuffer m_frameBuffer {};

    TextureList m_textures {};

    mutable bool m_dirty { true };

};

inline void RenderTarget::lockDraw()
{
    m_frameBuffer.bindDraw();
}

inline void RenderTarget::lockRead()
{
    m_frameBuffer.bindRead();
}

inline void RenderTarget::check() const
{
    m_frameBuffer.checkStatus();
}

inline bool RenderTarget::isDirty() const
{
    return m_dirty;
}

inline void RenderTarget::setDirty()
{
    m_dirty = true;
}

inline void RenderTarget::_notifyDirty() const
{
    m_dirty = false;
}

}
