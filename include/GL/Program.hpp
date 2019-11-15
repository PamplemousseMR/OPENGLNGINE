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
    ~Program() final;
    Program(const Program&);
    Program(Program&&) = delete;
    Program& operator=(const Program&);
    Program& operator=(Program&&) = delete;

    void attach(Shader&);
    void detach(const Shader&);
    void detachAll();
    void link() const;

    inline virtual void bind() const final;
    inline virtual void unbind() const final;

private:

    std::vector<Shader*> m_shaders {};

};

inline void Program::bind() const
{
    glUseProgram(m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void Program::unbind() const
{
    glUseProgram(0);
    assert(glGetError() == GL_NO_ERROR);
}

}
