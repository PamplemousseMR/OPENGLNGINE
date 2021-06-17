#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include <map>
#include <memory>
#include <string>

namespace Core
{

class IManager
{

protected:

    IManager();

    virtual ~IManager();

    void add(const std::shared_ptr< IResource >& _resource);

    std::shared_ptr< IResource > get(const std::string& _name) const;

private:

    void removeAll();

    typedef std::map< std::string, std::shared_ptr< IResource > > ResourceList;

    ResourceList m_resources {};

};

}
