#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include <string>

namespace Core
{

class IManager;

/**
 * @brief This interface allows to manage a resource for the render.
 */
class IHardwareResource : public IResource
{

public:

    /// Destroys the nameable resource.
    virtual ~IHardwareResource();

protected:

    /**
     * @brief Creates a hardware resource.
     * @param _manager The manager of this resource.
     * @param _name The name of the ressouce.
     */
    IHardwareResource(IManager* const _manager, const std::string& _name);

    /// Stores the manager of this resource.
    IManager* const m_manager;

};

}
