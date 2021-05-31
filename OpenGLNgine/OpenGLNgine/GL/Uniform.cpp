#include "OpenGLNgine/GL/Uniform.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace GL
{

Uniform::Uniform(const std::string& _name, GLuint _program) :
    m_name(_name),
    m_location(glGetUniformLocation(_program, _name.c_str()))
{
    GLNGINE_CHECK_GL;
}

Uniform::~Uniform()
{
}

Uniform::Uniform(const Uniform& _uniform) :
    m_name(_uniform.m_name),
    m_location(_uniform.m_location)
{
}

Uniform& Uniform::operator=(const Uniform& _uniform)
{
    if(this != &_uniform)
    {
        m_name = _uniform.m_name;
        m_location = _uniform.m_location;
    }
    return *this;
}

void Uniform::operator=(bool _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_bCache || m_bCache.value() != _t)
    {
        m_bCache = _t;
        glUniform1i(m_location, _t ? 1 : 0);
        GLNGINE_CHECK_GL;
    }
#else
glUniform1i(m_location, _t ? 1 : 0);
#endif
}

void Uniform::operator=(int _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_iCache || m_iCache.value() != _t)
    {
        m_iCache = _t;
        glUniform1i(m_location, _t);
        GLNGINE_CHECK_GL;
    }
#else
glUniform1i(m_location, _t);
#endif
}

void Uniform::operator=(unsigned _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_uiCache || m_uiCache.value() != _t)
    {
        m_uiCache = _t;
        glUniform1ui(m_location, _t);
        GLNGINE_CHECK_GL;
    }
#else
glUniform1ui(m_location, _t);
#endif
}

void Uniform::operator=(float _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_fCache || m_fCache.value() != _t)
    {
        m_fCache = _t;
        glUniform1f(m_location, _t);
        GLNGINE_CHECK_GL;
    }
#else
glUniform1f(m_location, _t);
#endif
}

void Uniform::operator=(const ::glm::vec2& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_f2Cache || m_f2Cache.value() != _t)
    {
        m_f2Cache = _t;
        glUniform2f(m_location, _t.x, _t.y);
        GLNGINE_CHECK_GL;
    }
#else
glUniform2f(m_location, _t.x, _t.y);
#endif
}

void Uniform::operator=(const ::glm::vec3& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_f3Cache || m_f3Cache.value() != _t)
    {
        m_f3Cache = _t;
        glUniform3f(m_location, _t.x, _t.y, _t.z);
        GLNGINE_CHECK_GL;
    }
#else
glUniform3f(m_location, _t.x, _t.y, _t.z);
#endif
}

void Uniform::operator=(const std::vector< ::glm::vec3 >& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_f3vCache || m_f3vCache.value() != _t)
    {
        m_f3vCache = _t;
        glUniform3fv(m_location, static_cast< GLsizei >(_t.size()), glm::value_ptr(_t[0]));
        GLNGINE_CHECK_GL;
    }
#else
glUniform3fv(m_location, static_cast< GLsizei >(_t.size()), glm::value_ptr(_t[0]));
#endif
}

void Uniform::operator=(const ::glm::vec4& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_f4Cache || m_f4Cache.value() != _t)
    {
        m_f4Cache = _t;
        glUniform4f(m_location, _t.x, _t.y, _t.z, _t.w);
        GLNGINE_CHECK_GL;
    }
#else
glUniform4f(m_location, _t.x, _t.y, _t.z, _t.w);
#endif
}

void Uniform::operator=(const std::vector< ::glm::vec4 >& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_f4vCache || m_f4vCache.value() != _t)
    {
        m_f4vCache = _t;
        glUniform4fv(m_location, static_cast< GLsizei >(_t.size()), glm::value_ptr(_t[0]));
        GLNGINE_CHECK_GL;
    }
#else
glUniform4fv(m_location, static_cast< GLsizei >(_t.size()), glm::value_ptr(_t[0]));
#endif
}

void Uniform::operator=(const ::glm::mat3& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_m3Cache || m_m3Cache.value() != _t)
    {
        m_m3Cache = _t;
        glUniformMatrix3fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
        GLNGINE_CHECK_GL;
    }
#else
glUniformMatrix3fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
#endif
}

void Uniform::operator=(const ::glm::mat4& _t) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(!m_m4Cache || m_m4Cache.value() != _t)
    {
        m_m4Cache = _t;
        glUniformMatrix4fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
        GLNGINE_CHECK_GL;
    }
#else
glUniformMatrix4fv(m_location, 1, false, reinterpret_cast<const GLfloat*>(&_t));
#endif
}

}
