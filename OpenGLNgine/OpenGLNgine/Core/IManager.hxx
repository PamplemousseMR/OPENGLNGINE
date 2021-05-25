#include "OpenGLNgine/Core/IManager.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

template< class T >
IManager< T >::IManager()
{
}

template< class T >
IManager< T >::~IManager()
{
    this->removeAll();
}

template< class T >
void IManager< T >::add(const std::shared_ptr< T >& _resource)
{
    if(m_resources.find(_resource->getName()) != m_resources.end())
    {
        GLNGINE_EXCEPTION("A resource with the name '" + _resource->getName() + "' already exists");
    }
    m_resources.emplace(_resource->getName(), _resource);
}

template< class T >
void IManager< T >::remove(const std::shared_ptr< T >& _resource)
{
    GLNGINE_ASSERT_IF(!_resource, "The resource mustn't be null");

    typename ResourceList::const_iterator it = m_resources.find(_resource->getName());
    if(it == m_resources.end())
    {
        GLNGINE_EXCEPTION("A resource with the name '" + _resource->getName() + "' doesn't exists");
    }

    m_resources.erase(it);
}

template< class T >
void IManager< T >::removeAll()
{
    typename ResourceList::iterator itBeg, itEnd;
    itEnd = m_resources.end();
    for(itBeg=m_resources.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        itBeg->second.reset();
    }
    m_resources.clear();
}
