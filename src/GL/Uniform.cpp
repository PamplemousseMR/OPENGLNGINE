#include "GL/Uniform.hpp"

using namespace std;
using namespace glm;

namespace GL
{
    Uniform::Uniform(const string & name, GLuint program)
        :m_name(name), m_location(glGetUniformLocation(program, name.c_str()))
    {
#ifdef _DEBUG
        cout << "[Uniform " << m_name << "] [Uniform(const string & name, GLuint program)]..." << endl;
        cout << "[Uniform " << m_name << "] [Uniform(const string & name, GLuint program)]...\tsuccess" << endl;
#endif
    }

    Uniform::~Uniform()
    {
#ifdef _DEBUG
        cout << "[Uniform " << m_name << "] [~Uniform()]..." << endl;
        cout << "[Uniform " << m_name << "] [~Uniform()]...\tsuccess" << endl;
#endif
    }

    GLuint Uniform::getLocation() const
    {
        return m_location;
    }

    const string& Uniform::getName() const
    {
        return m_name;
    }

    void Uniform::operator= (bool t) 
    { 
        glUniform1i(m_location, t ? 1 : 0); 
    }

    void Uniform::operator= (int t) 
    { 
        glUniform1i(m_location, t);
    }

    void Uniform::operator= (float t) 
    { 
        glUniform1f(m_location, t); 
    }
    void Uniform::operator= (const vec2& t) 
    {
        glUniform2f(m_location, t.x, t.y); 
    }

    void Uniform::operator= (const vec3& t)
    { 
        glUniform3f(m_location, t.x, t.y, t.z); 
    }

    void Uniform::operator= (const vec4& t) 
    { 
        glUniform4f(m_location, t.x, t.y, t.z, t.w); 
    }

    void Uniform::operator= (const mat4& t)
    { 
        glUniformMatrix4fv(m_location, 1, false, value_ptr(t)); 
    }

    void Uniform::operator= (const mat3& t)
    {
        glUniformMatrix3fv(m_location, 1, false, value_ptr(t));
    }
}
