#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include <string>

namespace Core
{

class IHardwareManager;

/**
 * @brief This interface allows to manage a resource for the render.
 */
class IHardwareResource : public IResource
{

public:

    /// Destroys the nameable resource.
    virtual ~IHardwareResource();

    /// Stores the manager of this resource.
    IHardwareManager* const m_manager;

protected:

    /**
     * @brief Creates a hardware resource.
     * @param _manager The manager of this resource.
     * @param _name The name of the ressouce.
     */
    IHardwareResource(IHardwareManager* const _manager, const std::string& _name);

};

}
