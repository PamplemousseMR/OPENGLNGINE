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

    void operator=(bool _t) const;

    void operator=(int _t) const;

    void operator=(unsigned _t) const;

    void operator=(float _t) const;

    void operator=(const ::glm::vec2& _t) const;

    void operator=(const ::glm::vec3& _t) const;

    void operator=(const std::vector< ::glm::vec3 >& _t) const;

    void operator=(const ::glm::vec4& _t) const;

    void operator=(const std::vector< ::glm::vec4 >& _t) const;

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

}
