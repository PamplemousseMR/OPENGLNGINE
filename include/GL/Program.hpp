#pragma once

#include <GL/glew.h>

#include <vector>

namespace GL
{

class Shader;

class Program
{

public:

    Program();
    ~Program() noexcept;
    Program(const Program&);
    Program& operator=(const Program&);

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

inline bool Program::isActive() const noexcept
{
    return m_toggled;
}

inline GLuint Program::getId() const noexcept
{
    return m_id;
}

}
