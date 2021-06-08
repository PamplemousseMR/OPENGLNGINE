#include "OpenGLNgine/Hardware/CompositorManager.hpp"

namespace Hardware
{

CompositorManager* CompositorManager::s_instance = nullptr;

CompositorManager& CompositorManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

CompositorPtr CompositorManager::create(const std::string& _name)
{
    CompositorPtr ptr = std::make_shared< Compositor >(this, _name);
    this->add(ptr);
    return ptr;
}

CompositorManager::Initializer::Initializer()
{
    CompositorManager::s_instance = new CompositorManager();
}

CompositorManager::Initializer::~Initializer()
{
    delete CompositorManager::s_instance;
    CompositorManager::s_instance = nullptr;
}

CompositorManager::CompositorManager():
    ::Core::IManager<Compositor>()
{
}

CompositorManager::~CompositorManager()
{
}

}
