#include "GL/Shader.hpp"

#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

namespace GL
{

    Shader::Shader(SHADER_TYPE type) :
        m_id(glCreateShader(type)),
        m_type(type)
    {
        if(m_id == 0)
        {
            throw overflow_error("[Shader] Out of memory");
        }
    }

    Shader::~Shader() noexcept
    {
        glDeleteShader(m_id);
    }

    Shader::Shader(const Shader& _shader) :
        m_id(glCreateShader(_shader.m_type)),
        m_type(_shader.m_type),
        m_sources(_shader.m_sources)
    {
        if(m_id == 0)
        {
            throw overflow_error("[Shader] Out of memory");
        }
    }

    Shader& Shader::operator=(const Shader& _shader)
    {
        if (this != &_shader)
        {
            glDeleteShader(m_id);
            m_type = _shader.m_type;
            m_id = glCreateShader(_shader.m_type);
            if(m_id == 0)
            {
                throw overflow_error("[Shader] Out of memory");
            }
            m_sources = _shader.m_sources;
        }
        return *this;
    }

    void Shader::setSourceFromFile(const std::filesystem::path& _path)
    {
        if(!filesystem::exists(_path) || !filesystem::is_regular_file(_path))
        {
            throw invalid_argument("[Shader] path doesn't exists : " + _path.string());
        }
        string shaderCode;
        ifstream shaderStream(_path, ios::in);
        if (shaderStream.is_open())
        {
            string Line = "";
            while (getline(shaderStream, Line))
            {
                shaderCode += "\n" + Line;
            }
            shaderStream.close();
        }
        else
        {
            throw invalid_argument("[Shader] can't open file : " + _path.string());
        }
        m_sources = shaderCode;
    }

    void GL::Shader::compile() const
    {
        const char* const vertexSourcePointer = m_sources.c_str();
        glShaderSource(m_id, 1, &vertexSourcePointer, nullptr);
        glCompileShader(m_id);

        GLint result = GL_FALSE;
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);

        if (!result)
        {
            int infoLogLength;
            glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

            vector<char> shaderErrorMessage(size_t(infoLogLength + 1));
            glGetShaderInfoLog(m_id, infoLogLength, nullptr, &shaderErrorMessage[0]);

            string str(shaderErrorMessage.begin(), shaderErrorMessage.end());
            throw invalid_argument("[Shader] can't compile : " + str);
        }
    }

}
