#pragma once

#include "OpenGLNgine/Core/Exception.hpp"

#include <GL/glew.h>

#include <glm/ext/matrix_relational.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <optional>
#include <string>
#include <vector>
#include <iostream>

namespace GL
{

class Uniform final
{

public:

    Uniform(const std::string&, GLuint);

    ~Uniform();

    Uniform(const Uniform&);

    Uniform& operator=(const Uniform&);

    Uniform(Uniform&&) = delete;

    inline GLint getLocation() const;

    inline const std::string& getName() const;

    Uniform& operator=(Uniform&&) = delete;

    inline void operator=(bool _t) const;

    inline void operator=(int _t) const;

    inline void operator=(unsigned _t) const;

    inline void operator=(float _t) const;

    inline void operator=(const ::glm::vec2& _t) const;

    inline void operator=(const ::glm::vec3& _t) const;

    inline void operator=(const std::vector< ::glm::vec3 >& _t) const;

    inline void operator=(const ::glm::vec4& _t) const;

    inline void operator=(const std::vector< ::glm::vec4 >& _t) const;

    void operator=(const ::glm::mat3& _t) const;

    void operator=(const ::glm::mat4& _t) const;

private:

    std::string m_name {};

    GLint m_location {0};

#ifdef GLNGINE_USE_STATE_CACHE
    mutable std::optional< bool > m_bCache { std::nullopt };

    mutable std::optional< int > m_iCache { std::nullopt };

    mutable std::optional< unsigned > m_uiCache { std::nullopt };

    mutable std::optional< float > m_fCache { std::nullopt };

    mutable std::optional< ::glm::vec2 > m_f2Cache { std::nullopt };

    mutable std::optional< ::glm::vec3 > m_f3Cache { std::nullopt };

    mutable std::optional< std::vector< ::glm::vec3 > > m_f3vCache { std::nullopt };

    mutable std::optional< ::glm::vec4 > m_f4Cache { std::nullopt };

    mutable std::optional< std::vector< ::glm::vec4 > > m_f4vCache { std::nullopt };

    mutable std::optional< ::glm::mat3 > m_m3Cache { std::nullopt };

    mutable std::optional< ::glm::mat4 > m_m4Cache { std::nullopt };
#endif

};

inline GLint Uniform::getLocation() const
{
    return m_location;
}

inline const std::string& Uniform::getName() const
{
    return m_name;
}

inline void Uniform::operator=(bool _t) const
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

inline void Uniform::operator=(int _t) const
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

inline void Uniform::operator=(unsigned _t) const
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

inline void Uniform::operator=(float _t) const
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

inline void Uniform::operator=(const ::glm::vec2& _t) const
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

inline void Uniform::operator=(const ::glm::vec3& _t) const
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

inline void Uniform::operator=(const std::vector< ::glm::vec3 >& _t) const
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

inline void Uniform::operator=(const ::glm::vec4& _t) const
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

inline void Uniform::operator=(const std::vector< ::glm::vec4 >& _t) const
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

}
