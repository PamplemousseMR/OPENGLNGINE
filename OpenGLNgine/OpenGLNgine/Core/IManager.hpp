#pragma once

#include <map>
#include <memory>
#include <string>

namespace Core
{

template <class T>
class IManager
{

public:

    std::shared_ptr< T > getByName(const std::string& _name);

protected:

    IManager();

    virtual ~IManager();

    void add(const std::shared_ptr< T >& _resource);

private:

    void removeAll();

    typedef std::map< std::string, std::shared_ptr< T > > ResourceList;

    ResourceList m_resources {};

};

#include "OpenGLNgine/Core/IManager.hxx"

}
