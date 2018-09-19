#include "GL/Program.hpp"
#include "GL/Shader.hpp"

#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

namespace GL
{
    Program::Program() :
        IGLObject()
    {
        m_id = glCreateProgram();
        if(m_id == 0)
        {
            throw overflow_error("[Program] Out of memory");
        }
    }

    Program::~Program() noexcept
    {
        detachAll();
        glDeleteProgram(m_id);
    }

    Program::Program(const Program& _program) :
        IGLObject(_program)
    {
        m_id = glCreateProgram();
        if(m_id == 0)
        {
            throw overflow_error("[Program] Out of memory");
        }
        for (Shader* const s : _program.m_shaders)
        {
            attach(*s);
        }
    }

    Program& Program::operator=(const Program& _program)
    {
        if(this != &_program)
        {
            detachAll();
            glDeleteProgram(m_id);
            IGLObject::operator=(_program);
            m_id = glCreateProgram();
            if(m_id == 0)
            {
                throw overflow_error("[Program] Out of memory");
            }
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
            throw runtime_error("[Program] shader already attached ");
        }
        m_shaders.push_back(&_shader);
        glAttachShader(m_id, _shader.getId());
    }

    void Program::detach(const Shader& _shader)
    {
        auto p = find(m_shaders.begin(), m_shaders.end(), &_shader);
        if (p == m_shaders.end())
        {
            throw runtime_error("[Program] shader not attached ");
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
            vector<char> programErrorMessage(size_t(infoLogLength) + 1);
            glGetProgramInfoLog(m_id, infoLogLength, nullptr, &programErrorMessage[0]);
            throw runtime_error("[Program] " + std::string(programErrorMessage.begin(), programErrorMessage.end()));
        }
    }
}
