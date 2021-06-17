#include "OpenGLNgine/Hardware/CompositorManager.hpp"

namespace Hardware
{

CompositorPtr CompositorManager::create(const std::string& _name)
{
    const CompositorPtr ptr(new Compositor(this, _name));
    this->add(ptr);
    return ptr;
}

CompositorManager::CompositorManager():
    ::Core::IHardwareManager()
{
}

CompositorManager::~CompositorManager()
{
}

}
