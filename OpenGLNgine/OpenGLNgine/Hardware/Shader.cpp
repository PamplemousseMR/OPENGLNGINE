#include "OpenGLNgine/Hardware/Shader.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Hardware/ProgramManager.hpp"

namespace Hardware
{

::GL::SHADER_TYPE Shader::getType(SHADER_TYPE _type)
{
    switch(_type)
    {
    case ST_VERTEX:
        return ::GL::ST_VERTEX;
    case ST_GEOMETRY:
        return ::GL::ST_GEOMETRY;
    case ST_FRAGMENT:
        return ::GL::ST_FRAGMENT;
    default:
        GLNGINE_EXCEPTION("Unhandle shader type");
    }
}

Shader::Shader(ProgramManager* const _manager, const std::string& _name, SHADER_TYPE _type):
    ::Core::IHardwareResource(_manager, _name),
    type(_type),
    m_manager(_manager),
    m_shader(getType(_type))
{
}

Shader::~Shader()
{
}

void Shader::setSourceFromFile(const std::filesystem::path& _path)
{
    m_shader.setSourceFromFile(_path);
}

void Shader::load()
{
    m_shader.compile();
}

}
