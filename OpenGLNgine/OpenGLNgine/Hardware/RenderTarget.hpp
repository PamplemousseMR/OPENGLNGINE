#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/GL/FrameBuffer.hpp"
#include "OpenGLNgine/GL/Texture.hpp"
#include "OpenGLNgine/Hardware/Pass.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

#include <memory>
#include <map>

namespace Hardware
{

class RenderTarget;
class RenderTargetManager;

typedef std::shared_ptr< RenderTarget > RenderTargetPtr;

class RenderTarget final : public ::Core::IResource
{

public:

    typedef std::map< unsigned, std::pair< ::GL::Texture, TEXTURE_INTERNAL_FORMAT > > TextureList;

    RenderTarget(RenderTargetManager* const _manager, const std::string& _name);

    ~RenderTarget();

    RenderTarget(const RenderTarget&) = delete;

    RenderTarget(RenderTarget&&) = delete;

    RenderTarget& operator=(const RenderTarget&) = delete;

    RenderTarget& operator=(RenderTarget&&) = delete;

    inline void lock();

    inline void unlock();

    inline void lockDraw();

    inline void lockRead();

    void lock(unsigned _location);

    void unlock(unsigned _location);

    void allocate(unsigned _location, int _width, int _height);

    void attach(unsigned _location);

    inline void check() const;

    void addTexture(TEXTURE_INTERNAL_FORMAT _format, unsigned _location);

    inline const TextureList& getTextures() const;

    inline bool isDirty() const;

    inline void setDirty();

    inline void _notifyDirty() const;

private:

    RenderTargetManager* const m_manager;

    ::GL::FrameBuffer m_frameBuffer {};

    TextureList m_textures {};

    mutable bool m_dirty { true };

};

inline void RenderTarget::lock()
{
    m_frameBuffer.bind();
}

inline void RenderTarget::unlock()
{
    m_frameBuffer.unbind();
}

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

inline const RenderTarget::TextureList& RenderTarget::getTextures() const
{
    return m_textures;
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
