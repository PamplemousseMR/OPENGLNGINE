#include "OpenGLNgine/Hardware/RenderTargetManager.hpp"

namespace Hardware
{

RenderTargetManager* RenderTargetManager::s_instance = nullptr;

RenderTargetManager& RenderTargetManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

RenderTargetPtr RenderTargetManager::create(const std::string& _name)
{
    RenderTargetPtr ptr = std::make_shared< RenderTarget >(this, _name);
    this->add(ptr);
    return ptr;
}

RenderTargetPtr RenderTargetManager::getByName(const std::string& _name)
{
    return this->get(_name);
}

void RenderTargetManager::destroy(const RenderTargetPtr& _renderTarget)
{
    this->remove(_renderTarget);
}

RenderTargetManager::Initializer::Initializer()
{
    RenderTargetManager::s_instance = new RenderTargetManager();
}

RenderTargetManager::Initializer::~Initializer()
{
    delete RenderTargetManager::s_instance;
    RenderTargetManager::s_instance = nullptr;
}

RenderTargetManager::RenderTargetManager():
    ::Core::IManager<RenderTarget>()
{
}

RenderTargetManager::~RenderTargetManager()
{
}

}
