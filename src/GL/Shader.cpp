#include "GL/Shader.h"

using namespace std;

namespace GL
{

	Shader::Shader(SHADER_TYPE type)
		: m_type(type), m_id(glCreateShader(type)), m_sources("")
	{
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [Shader(shaderType type)]..." << endl;
        cout << "[Shader " << m_type << "] [Shader(shaderType type)]...\tsuccess" << endl;
#endif
	}

	Shader::~Shader()
	{
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [~Shader()]..." << endl;
#endif
		glDeleteShader(m_id);
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [~Shader()]...\tsuccess" << endl;
#endif
	}

	Shader::Shader(const Shader& shader)
		: m_type(shader.m_type), m_id(glCreateShader(shader.m_type)), m_sources(shader.m_sources)
	{
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [Shader(const Shader& shader)]..." << endl;
        cout << "[Shader " << m_type << "] [Shader(const Shader& shader)]...\tsuccess" << endl;
#endif
	}

	Shader& Shader::operator=(const Shader& shader)
	{
		if (this != &shader)
		{
			glDeleteShader(m_id);
			m_type = shader.m_type;
			m_id = glCreateShader(shader.m_type);
			m_sources = shader.m_sources;
		}
		return *this;
	}

	GLenum Shader::getType() const
	{
		return m_type;
	}

	GLuint Shader::getId() const
	{
		return m_id;
	}

	void Shader::setSource(const std::string& src)
	{
		m_sources = src;
	}

	void Shader::setSourceFromFile(const std::string& path) throw(...)
	{
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [setSource(const std::string& src)]..." << endl;
#endif
		string shaderCode;
		ifstream shaderStream(path, ios::in);
		if (shaderStream.is_open()) {
			string Line = "";
			while (getline(shaderStream, Line))
				shaderCode += "\n" + Line;
			shaderStream.close();
		}
		else 
			throw invalid_argument("[Shader] [setSource(const std::string& src)]  can't open file : " + path);
		m_sources = shaderCode;
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [setSource(const std::string& src)]...\tsuccess" << endl;
#endif
	}

	void GL::Shader::compile() const throw(...)
	{
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [compile() const throw(...)]..." << endl;
#endif
		GLint Result = GL_FALSE;
		int InfoLogLength;

        char const * VertexSourcePointer = m_sources.c_str();
        glShaderSource(m_id, 1, &VertexSourcePointer, nullptr);
        glCompileShader(m_id);

        glGetShaderiv(m_id, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			vector<char> shaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(m_id, InfoLogLength, nullptr, &shaderErrorMessage[0]);
			string ty;
            switch (m_type)
			{
			case VERTEX:
				ty = "vertex";
				break;
			case FRAGMENT:
				ty = "fragment";
				break;
			}
			string str(shaderErrorMessage.begin(), shaderErrorMessage.end());
			throw invalid_argument("[Shader " + ty + "] [compile() const throw(...)] " + str);
		}
#ifdef _DEBUG
        cout << "[Shader " << m_type << "] [compile() const throw(...)]...\tsuccess" << endl;
#endif
	}

}
