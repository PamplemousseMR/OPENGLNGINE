#include "OpenGLNgine/Hardware/CompositorManager.hpp"

namespace Hardware
{

CompositorPtr CompositorManager::create(const std::string& _name)
{
    const CompositorPtr ptr(new Compositor(this, _name));
    this->add(ptr);
    return ptr;
}

CompositorManager::CompositorManager(const ::Render::RenderWindow* const _renderWindow) :
    ::Core::IHardwareManager(_renderWindow)
{
}

CompositorManager::~CompositorManager()
{
}

}
