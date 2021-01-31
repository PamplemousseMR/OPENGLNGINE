#include "OpenGLNgine/GL/Shader.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <fstream>
#include <vector>

namespace GL
{

Shader::Shader(SHADER_TYPE _type) :
    m_id(glCreateShader(_type)),
    m_type(_type)
{
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the shader");
    }
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

Shader::Shader(const Shader& _shader) :
    m_id(glCreateShader(_shader.m_type)),
    m_type(_shader.m_type),
    m_sources(_shader.m_sources)
{
    GLNGINE_CHECK_GL;
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the shader");
    }
}

Shader& Shader::operator=(const Shader& _shader)
{
    if(this != &_shader)
    {
        m_sources = _shader.m_sources;
        m_type = _shader.m_type;

        glDeleteShader(m_id);

        m_id = glCreateShader(_shader.m_type);

        GLNGINE_CHECK_GL;
        if(m_id == 0)
        {
            GLNGINE_EXCEPTION("Can't create the shader");
        }
    }
    return *this;
}

void Shader::setSourceFromFile(const std::filesystem::path& _path)
{
    GLNGINE_ASSERT_IF(!std::filesystem::exists(_path), std::filesystem::is_regular_file(_path));

    std::string shaderCode;
    std::ifstream shaderStream(_path, std::ios::in);
    if(shaderStream.is_open())
    {
        std::string Line = "";
        while(getline(shaderStream, Line))
        {
            shaderCode += "\n" + Line;
        }
        shaderStream.close();
    }
    else
    {
        GLNGINE_EXCEPTION("Can't open '" + _path.string() + "'");
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

    if(!result)
    {
        int infoLogLength;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> shaderErrorMessage(size_t(infoLogLength + 1));
        glGetShaderInfoLog(m_id, infoLogLength, nullptr, &shaderErrorMessage[0]);

        std::string str(shaderErrorMessage.begin(), shaderErrorMessage.end());
        GLNGINE_EXCEPTION(str);
    }
    GLNGINE_CHECK_GL;
}

}
