#include "OpenGLNgine/Hardware/RenderTargetManager.hpp"

namespace Hardware
{

RenderTargetPtr RenderTargetManager::create(const std::string& _name, unsigned _sample)
{
    RenderTargetPtr ptr(new RenderTarget(this, _name, _sample));
    this->add(ptr);
    return ptr;
}

RenderTargetManager::RenderTargetManager():
    ::Core::IManager()
{
}

RenderTargetManager::~RenderTargetManager()
{
}

}
