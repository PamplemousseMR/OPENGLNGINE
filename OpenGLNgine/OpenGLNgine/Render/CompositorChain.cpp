#include "OpenGLNgine/Render/CompositorChain.hpp"

#include "OpenGLNgine/Core/IHardwareManager.hpp"

namespace Render
{

void CompositorChain::addCompositor(const ::Hardware::CompositorPtr& _compositor)
{
    GLNGINE_ASSERT_IF(_compositor->m_manager->m_renderWindow != m_viewport->m_renderWindow, "The compositor doe not came from this context");
    m_compositors.push_back(_compositor);
}

CompositorChain::CompositorChain(Viewport* const _viewport, const std::string& _name) :
    IResource(_name),
    m_viewport(_viewport)
{
}

CompositorChain::~CompositorChain()
{
    m_compositors.clear();
}

}
