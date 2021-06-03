#include "OpenGLNgine/Hardware/Compositor.hpp"

namespace Hardware
{

Compositor::Compositor(CompositorManager* const _manager, const std::string& _name):
    ::Core::IResource(_name),
    m_manager(_manager)
{
}

Compositor::~Compositor()
{
}

}
