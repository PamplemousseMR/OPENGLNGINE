#pragma once

#include <GL/glew.h>

#include <assert.h>
#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class Shader;

class Program : public IGLObject
{

public:

    Program();
    ~Program() noexcept override;
    Program(const Program&);
    Program(Program&&) = delete;
    Program& operator=(const Program&);
    Program& operator=(Program&&) = delete;

    void attach(Shader&);
    void detach(const Shader&);
    void detachAll() noexcept;
    void link() const;

    inline virtual void bind() const noexcept override;
    inline virtual void unbind() const noexcept override;

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
