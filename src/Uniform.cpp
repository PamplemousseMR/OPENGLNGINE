#include "Uniform.h"

using namespace std;
using namespace glm;

namespace GL
{
	Uniform::Uniform(const string & name, GLuint program)
		:_name(name), _location(glGetUniformLocation(program, name.c_str()))
	{
#ifdef _DEBUG
		cout << "[Uniform " << _name << "] [Uniform(const string & name, GLuint program)]..." << endl;
		cout << "[Uniform " << _name << "] [Uniform(const string & name, GLuint program)]...\tsuccess" << endl;
#endif
	}

	Uniform::~Uniform()
	{
#ifdef _DEBUG
		cout << "[Uniform " << _name << "] [~Uniform()]..." << endl;
		cout << "[Uniform " << _name << "] [~Uniform()]...\tsuccess" << endl;
#endif
	}

	GLuint Uniform::getLocation() const
	{
		return _location;
	}

	const string& Uniform::getName() const
	{
		return _name;
	}

	void Uniform::operator= (bool t) 
	{ 
		glUniform1i(_location, t ? 1 : 0); 
	}

	void Uniform::operator= (int t) 
	{ 
		glUniform1i(_location, t);
	}

	void Uniform::operator= (float t) 
	{ 
		glUniform1f(_location, t); 
	}
	void Uniform::operator= (const vec2& t) 
	{
		glUniform2f(_location, t.x, t.y); 
	}

	void Uniform::operator= (const vec3& t)
	{ 
		glUniform3f(_location, t.x, t.y, t.z); 
	}

	void Uniform::operator= (const vec4& t) 
	{ 
		glUniform4f(_location, t.x, t.y, t.z, t.w); 
	}

	void Uniform::operator= (const mat4& t)
	{ 
		glUniformMatrix4fv(_location, 1, false, value_ptr(t)); 
	}

	void Uniform::operator= (const mat3& t)
	{
		glUniformMatrix3fv(_location, 1, false, value_ptr(t));
	}
}