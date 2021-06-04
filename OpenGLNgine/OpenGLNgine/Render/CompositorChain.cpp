#include "OpenGLNgine/Render/CompositorChain.hpp"

namespace Render
{

CompositorChain::CompositorChain(Viewport* const _viewport, const std::string& _name):
    IResource(_name),
    m_viewport(_viewport)
{
}

CompositorChain::~CompositorChain()
{
}

}
