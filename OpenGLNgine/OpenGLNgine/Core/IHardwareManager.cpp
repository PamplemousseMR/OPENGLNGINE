#include "OpenGLNgine/Core/IHardwareManager.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Core
{

IHardwareManager::IHardwareManager(const ::Render::RenderWindow* const _renderWindow) :
    m_renderWindow(_renderWindow)
{
    GLNGINE_ASSERT_IF(!_renderWindow, "The render window shall not be nullptr");
}

IHardwareManager::~IHardwareManager()
{
    this->removeAll();
}

void IHardwareManager::add(const std::shared_ptr< IResource >& _resource)
{
    if(m_resources.find(_resource->getName()) != m_resources.end())
    {
        GLNGINE_EXCEPTION("A resource with the name '" + _resource->getName() + "' already exists");
    }
    m_resources.emplace(_resource->getName(), _resource);
}

std::shared_ptr< IResource > IHardwareManager::get(const std::string& _name) const
{
    typename ResourceList::const_iterator it = m_resources.find(_name);
    return it != m_resources.end() ? it->second : nullptr;
}

void IHardwareManager::removeAll()
{
    typename ResourceList::iterator itBeg, itEnd;
    itEnd = m_resources.end();
    for(itBeg=m_resources.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        itBeg->second.reset();
    }
    m_resources.clear();
}

}
