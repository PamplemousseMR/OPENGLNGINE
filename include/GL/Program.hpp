#pragma once

#include <GL/glew.h>

#include <iostream>
#include <vector>

namespace GL
{

class Shader;

class Program
{

public:

    Program() noexcept;
    ~Program() noexcept;
    Program(const Program&) noexcept;
    Program& operator=(const Program&) noexcept;

    void attach(Shader& shader);
    void detach(const Shader& shader);
    void detachAll() noexcept;
    void link() const;
    void toggle() noexcept;

    inline bool isActive() const noexcept;
    inline GLuint getId() const noexcept;

private:

    GLuint m_id {0};
    bool m_toggled {false};
    std::vector<Shader*> m_shaders {};

};

bool Program::isActive() const noexcept
{
    return m_toggled;
}

GLuint Program::getId() const noexcept
{
    return m_id;
}

}
