#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include <map>
#include <memory>
#include <string>

namespace Render
{
    class RenderWindow;
}

namespace Core
{

class IHardwareManager
{

protected:

    IHardwareManager(const ::Render::RenderWindow* const _renderWindow);

    virtual ~IHardwareManager();

    void add(const std::shared_ptr< IResource >& _resource);

    std::shared_ptr< IResource > get(const std::string& _name) const;

    const ::Render::RenderWindow* const m_renderWindow;

private:

    void removeAll();

    typedef std::map< std::string, std::shared_ptr< IResource > > ResourceList;

    ResourceList m_resources {};

};

}
