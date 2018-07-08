#include "GL/Program.h"
#include "GL/Shader.h"

using namespace std;

namespace GL
{

	Program::Program()
		: m_id(glCreateProgram()), m_toggled(false)
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
        glDeleteProgram(m_id);
#ifdef _DEBUG
		cout << "[Program] [~Program()]...\tsuccess" << endl;
#endif
	}

	void Program::attach(Shader* shader)
	{
#ifdef _DEBUG
		cout << "[Program] [attach(Shader* shader)]..." << endl;
#endif
		m_shaders.push_back(shader);
		glAttachShader(m_id, shader->getId());
#ifdef _DEBUG
		cout << "[Program] [attach(Shader* shader)]...\tsuccess" << endl;
#endif
	}

	void Program::detach(Shader* shader)
	{
#ifdef _DEBUG
		cout << "[Program] [detach(Shader* shader)]..." << endl;
#endif
		auto p = find(m_shaders.begin(), m_shaders.end(), shader);
		if (p != m_shaders.end())
		{
			glDetachShader(m_id, shader->getId());
			m_shaders.erase(p);
		}
#ifdef _DEBUG
		cout << "[Program] [detach(Shader* shader)]...\tsuccess" << endl;
#endif
	}

	void Program::detachAll()
	{
		vector<Shader*> shaderList = m_shaders;
		for (Shader* s : shaderList)
			detach(s);
	}

	void Program::link() const throw(...)
	{
#ifdef _DEBUG
		cout << "[Program] [link() const throw(...)]..." << endl;
#endif
		GLint Result = GL_FALSE;
		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &Result);
		int InfoLogLength;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(m_id, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
			throw invalid_argument("[Program] [link] " + ProgramErrorMessage[0]);
		}
#ifdef _DEBUG
		cout << "[Program] [link() const throw(...)]...\tsuccess" << endl;
#endif
	}

	void Program::toggle()
	{
		if (!m_toggled)
		{
			glUseProgram(m_id);
			m_toggled = true;
		}
		else
		{
			glUseProgram(0);
			m_toggled = false;
		}
	}

	bool Program::isActive() const
	{
		return m_toggled;
	}

	GLuint Program::getId() const
	{
		return m_id;
	}
}
