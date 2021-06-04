#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Render/Viewport.hpp"

namespace Render
{

class RenderWindow;

class CompositorChain final : public ::Core::IResource
{

    friend RenderWindow;

public:

    CompositorChain(const CompositorChain&) = delete;

    CompositorChain(CompositorChain&&) = delete;

    CompositorChain& operator=(const CompositorChain&) = delete;

    CompositorChain& operator=(CompositorChain&&) = delete;

    inline Viewport* getViewport() const;

private:

    CompositorChain(Viewport* const _viewport, const std::string& _name);

    ~CompositorChain();

    Viewport* const m_viewport;

};

inline Viewport* CompositorChain::getViewport() const
{
    return m_viewport;
}

}
