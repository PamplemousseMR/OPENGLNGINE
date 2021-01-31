#pragma once

#include <GL/glew.h>

namespace GL
{

/**
 * @brief Manages GL data ID and the binding of a GL data.
 */
class IBindable
{

public:

    /// Default contructor.
    IBindable() = default;

    /// Default destructor.
    virtual ~IBindable() = default;

    /// Deleted move constructor.
    IBindable(IBindable&&) = delete;

    /// Deleted move operator.
    IBindable& operator=(IBindable&&) = delete;

    /// Default copy contructor.
    IBindable(const IBindable&) = default;

    /// Default copy operator.
    IBindable& operator=(const IBindable&) = default;

    /**
     * @brief Gets the GL data ID.
     * @return The GL data ID.
     */
    inline GLuint getId() const;

    /// Binds the data.
    virtual void bind() const = 0;

    /// Unbinds the data.
    virtual void unbind() const = 0;

protected:

    /// Defines the ID of the GL data.
    GLuint m_id {};

};

inline GLuint IBindable::getId() const
{
    return m_id;
}

}

