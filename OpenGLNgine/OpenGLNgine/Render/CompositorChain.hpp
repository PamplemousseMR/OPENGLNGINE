#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Hardware/Compositor.hpp"
#include "OpenGLNgine/Render/Viewport.hpp"

#include <vector>

namespace Render
{

class RenderWindow;

class CompositorChain final : public ::Core::IResource
{

    friend RenderWindow;

public:

    typedef std::vector< ::Hardware::CompositorPtr > CompositorList;


    CompositorChain(const CompositorChain&) = delete;

    CompositorChain(CompositorChain&&) = delete;

    CompositorChain& operator=(const CompositorChain&) = delete;

    CompositorChain& operator=(CompositorChain&&) = delete;

    inline Viewport* getViewport() const;

    inline void addCompositor(const ::Hardware::CompositorPtr& _compositor);

    inline const CompositorList& getCompositors() const;

private:

    CompositorChain(Viewport* const _viewport, const std::string& _name);

    ~CompositorChain();

    Viewport* const m_viewport;

    CompositorList m_compositors {};

};

inline Viewport* CompositorChain::getViewport() const
{
    return m_viewport;
}

inline void CompositorChain::addCompositor(const ::Hardware::CompositorPtr& _compositor)
{
    m_compositors.push_back(_compositor);
}

inline const CompositorChain::CompositorList& CompositorChain::getCompositors() const
{
    return m_compositors;
}

}
