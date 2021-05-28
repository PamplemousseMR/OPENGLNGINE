#pragma once

#include <string>

namespace Core
{

/**
 * @brief This interface allows to manage a resource for the render.
 */
class IResource
{

public:

    /// Destroys the nameable resource.
    virtual ~IResource();

    /**
     * @brief Gets the name of the resource.
     * @return The name of the resource.
     */
    inline const std::string& getName() const;

protected:

    /// Creates a unique name based on the current memory adress.
    IResource();

    /**
     * @brief Creates a name from a string.
     * @param _name The name of the ressouce.
     */
    IResource(const std::string& _name);

    /// Defines the name of the resource.
    std::string m_name { "" };

};

inline const std::string& IResource::getName() const
{
    return m_name;
}

}
