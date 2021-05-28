#include "OpenGLNgine/GL/Program.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <algorithm>
#include <string>

namespace GL
{
Program::Program() :
    IBindable()
{
    m_id = glCreateProgram();
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the program");
    }
}

Program::~Program()
{
    detachAll();
    glDeleteProgram(m_id);
}

Program::Program(const Program& _program) :
    IBindable(_program)
{
    m_id = glCreateProgram();
    GLNGINE_CHECK_GL;
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the program");
    }
    for(Shader* const s : _program.m_shaders)
    {
        attach(*s);
    }
}

Program& Program::operator=(const Program& _program)
{
    if(this != &_program)
    {
        detachAll();
        for(Shader* const s : _program.m_shaders)
        {
            attach(*s);
        }
    }
    return *this;
}

void Program::attach(Shader& _shader)
{
    auto p = find(m_shaders.begin(), m_shaders.end(), &_shader);
    if(p != m_shaders.end())
    {
        GLNGINE_EXCEPTION("Shader already attached");
    }
    m_shaders.push_back(&_shader);
    glAttachShader(m_id, _shader.getId());

    GLNGINE_CHECK_GL;
}

void Program::detach(const Shader& _shader)
{
    auto p = find(m_shaders.begin(), m_shaders.end(), &_shader);
    if(p == m_shaders.end())
    {
        GLNGINE_EXCEPTION("Shader not attached");
    }
    glDetachShader(m_id, _shader.getId());

    GLNGINE_CHECK_GL;
    m_shaders.erase(p);
}

void Program::detachAll()
{
    while(m_shaders.size() != 0)
    {
        detach(*m_shaders[0]);
    }
}

void Program::link() const
{
    glLinkProgram(m_id);
    GLint result = GL_FALSE;
    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    if(!result)
    {
        int infoLogLength;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> programErrorMessage(size_t(infoLogLength) + 1);
        glGetProgramInfoLog(m_id, infoLogLength, nullptr, &programErrorMessage[0]);

        std::string str(programErrorMessage.begin(), programErrorMessage.end());
        GLNGINE_EXCEPTION(str);
    }
    GLNGINE_CHECK_GL;
}

void Program::bind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || !m_isBinded)
    {
        s_cache = add;
        m_isBinded = true;
        glUseProgram(m_id);
    }
#else
    glUseProgram(m_id);
#endif
}

void Program::unbind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_isBinded)
    {
        s_cache = add;
        m_isBinded = false;
        glUseProgram(0);
    }
#else
    glUseProgram(0);
#endif
}

}
