#include "Program.h"
#include "Shader.h"

using namespace std;

namespace GL
{

	Program::Program()
		: _id(glCreateProgram()), _toggled(false)
	{
#ifdef _DEBUG
		cout << "[Program] [Program()]..." << endl;
		cout << "[Program] [Program()]...\tsuccess" << endl;
#endif
	}

	GL::Program::~Program()
	{
#ifdef _DEBUG
		cout << "[Program] [~Program()]..." << endl;
#endif
		detachAll();
		glDeleteProgram(_id);
#ifdef _DEBUG
		cout << "[Program] [~Program()]...\tsuccess" << endl;
#endif
	}

	void Program::attach(Shader* shader)
	{
#ifdef _DEBUG
		cout << "[Program] [attach(Shader* shader)]..." << endl;
#endif
		_shaders.push_back(shader);
		glAttachShader(_id, shader->getId());
#ifdef _DEBUG
		cout << "[Program] [attach(Shader* shader)]...\tsuccess" << endl;
#endif
	}

	void Program::detach(Shader* shader)
	{
#ifdef _DEBUG
		cout << "[Program] [detach(Shader* shader)]..." << endl;
#endif
		auto p = find(_shaders.begin(), _shaders.end(), shader);
		if (p != _shaders.end())
		{
			glDetachShader(_id, shader->getId());
			_shaders.erase(p);
		}
#ifdef _DEBUG
		cout << "[Program] [detach(Shader* shader)]...\tsuccess" << endl;
#endif
	}

	void Program::detachAll()
	{
		vector<Shader*> shaderList = _shaders;
		for (Shader* s : shaderList)
			detach(s);
	}

	void Program::link() const throw(...)
	{
#ifdef _DEBUG
		cout << "[Program] [link() const throw(...)]..." << endl;
#endif
		GLint Result = GL_FALSE;
		glLinkProgram(_id);
		glGetProgramiv(_id, GL_LINK_STATUS, &Result);
		int InfoLogLength;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(_id, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
			throw invalid_argument("[Program] [link] " + ProgramErrorMessage[0]);
		}
#ifdef _DEBUG
		cout << "[Program] [link() const throw(...)]...\tsuccess" << endl;
#endif
	}

	void Program::toggle()
	{
		if (!_toggled)
		{
			glUseProgram(_id);
			_toggled = true;
		}
		else
		{
			glUseProgram(0);
			_toggled = false;
		}
	}

	bool Program::isActive() const
	{
		return _toggled;
	}

	GLuint Program::getId() const
	{
		return _id;
	}
}