#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/GL/IBindable.hpp"
#include "OpenGLNgine/GL/Shader.hpp"

#include <vector>

namespace GL
{

/**
 * @brief Manage a program object
 */
class Program final : public IBindable
{

public:

    /// Creates a program object
    Program();

    /// Destroys the program object
    ~Program();

    /**
     * @brief Creates a program copied from the parameter, without linking it.
     * @param _program The program to copy.
     */
    Program(const Program& _program);

    /**
     * @brief Destroys and creates a program copied from the parameter, without linking it.
     * @param _program The program to copy.
     */
    Program& operator=(const Program& _program);

    /// Deleted move constructor.
    Program(Program&&) = delete;

    /// Deleted move operator.
    Program& operator=(Program&&) = delete;

    /**
     * @brief Attachs the shader to the program.
     * @param _shader The shader to attach.
     */
    void attach(Shader& _shader);

    /**
     * @brief Dettachs the shader from the program.
     * @param _shader The shader from dettach.
     */
    void detach(const Shader& _shader);

    /// Dettachs all shadera from the program
    void detachAll();

    /// Links the program.
    void link() const;

    /// Binds the program.
    inline void bind() const override;

    /// Unbinds the program.
    inline void unbind() const override;

private:

    /// Contains all shaders attached to this program.
    std::vector<Shader*> m_shaders {};

    /// Defines the bind status.
    mutable bool m_isBinded { false };

};

inline void Program::bind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || !m_isBinded)
    {
        s_cache = add;
        m_isBinded = true;
        glUseProgram(m_id);
    }
}

inline void Program::unbind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_isBinded)
    {
        s_cache = add;
        m_isBinded = false;
        glUseProgram(0);
    }
}

}
