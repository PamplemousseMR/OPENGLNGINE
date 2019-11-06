#pragma once

#include <GL/glew.h>

#include <assert.h>
#include <vector>

#include "GL/IBindable.hpp"

namespace GL
{

class Shader;

class Program : public IBindable
{

public:

    Program();
    ~Program() noexcept final;
    Program(const Program&);
    Program(Program&&) = delete;
    Program& operator=(const Program&) noexcept;
    Program& operator=(Program&&) = delete;

    void attach(Shader&);
    void detach(const Shader&);
    void detachAll() noexcept;
    void link() const;

    inline virtual void bind() const noexcept final;
    inline virtual void unbind() const noexcept final;

private:

    std::vector<Shader*> m_shaders {};

};

inline void Program::bind() const noexcept
{
    glUseProgram(m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void Program::unbind() const noexcept
{
    glUseProgram(0);
    assert(glGetError() == GL_NO_ERROR);
}

}
