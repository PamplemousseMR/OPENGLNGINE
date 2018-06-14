#include"Shader.h"

using namespace std;

namespace GL
{

	Shader::Shader(shaderType type)
		: _type(type), _id(glCreateShader(type)), _sources("")
	{
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [Shader(shaderType type)]..." << endl;
		cout << "[Shader " << _type << "] [Shader(shaderType type)]...\tsuccess" << endl;
#endif
	}

	Shader::~Shader()
	{
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [~Shader()]..." << endl;
#endif
		glDeleteShader(_id);
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [~Shader()]...\tsuccess" << endl;
#endif
	}

	Shader::Shader(const Shader& shader)
		: _type(shader._type), _id(glCreateShader(shader._type)), _sources(shader._sources)
	{
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [Shader(const Shader& shader)]..." << endl;
		cout << "[Shader " << _type << "] [Shader(const Shader& shader)]...\tsuccess" << endl;
#endif
	}

	Shader& Shader::operator=(const Shader& shader)
	{
		if (this != &shader)
		{
			glDeleteShader(_id);
			_type = shader._type;
			_id = glCreateShader(shader._type);
			_sources = shader._sources;
		}
		return *this;
	}

	GLenum Shader::getType() const
	{
		return _type;
	}

	GLuint Shader::getId() const
	{
		return _id;
	}

	void Shader::setSource(const std::string& src)
	{
		_sources = src;
	}

	void Shader::setSourceFromFile(const std::string& path) throw(...)
	{
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [setSource(const std::string& src)]..." << endl;
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
		_sources = shaderCode;
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [setSource(const std::string& src)]...\tsuccess" << endl;
#endif
	}

	void GL::Shader::compile() const throw(...)
	{
#ifdef _DEBUG
		cout << "[Shader " << _type << "] [compile() const throw(...)]..." << endl;
#endif
		GLint Result = GL_FALSE;
		int InfoLogLength;

		char const * VertexSourcePointer = _sources.c_str();
		glShaderSource(_id, 1, &VertexSourcePointer, nullptr);
		glCompileShader(_id);

		glGetShaderiv(_id, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			vector<char> shaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(_id, InfoLogLength, nullptr, &shaderErrorMessage[0]);
			string ty;
			switch (_type)
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
		cout << "[Shader " << _type << "] [compile() const throw(...)]...\tsuccess" << endl;
#endif
	}

}