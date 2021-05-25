#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include <map>
#include <memory>

namespace Core
{

template <class T>
class IManager
{

protected:

    IManager();

    virtual ~IManager();

    void add(const std::shared_ptr< T >& _resource);

    void remove(const std::shared_ptr< T >& _resource);

    void removeAll();

private:

    typedef std::map< std::string, std::shared_ptr< T > > ResourceList;

    ResourceList m_resources {};

};

#include "OpenGLNgine/Core/IManager.hxx"

}