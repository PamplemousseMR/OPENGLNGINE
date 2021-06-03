#include "OpenGLNgine/Hardware/RenderTarget.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <algorithm>

namespace Hardware
{

RenderTarget::RenderTarget(RenderTargetManager* const _manager, const std::string& _name):
    ::Core::IResource(_name),
    m_manager(_manager)
{
}

RenderTarget::~RenderTarget()
{
}

}
