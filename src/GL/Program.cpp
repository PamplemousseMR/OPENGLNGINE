#include "GL/Program.hpp"
#include "GL/Shader.hpp"

#include <algorithm>

using namespace std;

namespace GL
{
    Program::Program() noexcept :
        m_id(glCreateProgram())
    {
    }

    Program::~Program() noexcept
    {
        detachAll();
        glDeleteProgram(m_id);
    }

    Program::Program(const Program& _program) noexcept :
        m_id(glCreateProgram())
    {
        for (Shader* const s : _program.m_shaders)
        {
            attach(*s);
        }
    }

    Program& Program::operator=(const Program& _program) noexcept
    {
        if(this != &_program)
        {
            detachAll();
            for (Shader* const s : _program.m_shaders)
            {
                attach(*s);
            }
        }
        return *this;
    }

    void Program::attach(Shader& _shader)
    {
        auto p = find(m_shaders.begin(), m_shaders.end(), &_shader);
        if (p != m_shaders.end())
        {
            throw invalid_argument("[Program] shader already attached ");
        }
        m_shaders.push_back(&_shader);
        glAttachShader(m_id, _shader.getId());
    }

    void Program::detach(const Shader& _shader)
    {
        auto p = find(m_shaders.begin(), m_shaders.end(), &_shader);
        if (p == m_shaders.end())
        {
            throw invalid_argument("[Program] shader not attached ");
        }
        glDetachShader(m_id, _shader.getId());
        m_shaders.erase(p);
    }

    void Program::detachAll() noexcept
    {
        for (const Shader* const s : m_shaders)
        {
            detach(*s);
        }
    }

    void Program::link() const
    {
        glLinkProgram(m_id);
        GLint result = GL_FALSE;
        glGetProgramiv(m_id, GL_LINK_STATUS, &result);
        if (!result)
        {
            int infoLogLength;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
            vector<char> programErrorMessage(infoLogLength + 1);
            glGetProgramInfoLog(m_id, infoLogLength, nullptr, &programErrorMessage[0]);
            throw invalid_argument("[Program] " + programErrorMessage[0]);
        }
    }

    void Program::toggle() noexcept
    {
        if (!m_toggled)
        {
            glUseProgram(m_id);
        }
        else
        {
            glUseProgram(0);
        }
        m_toggled = !m_toggled;
    }
}
