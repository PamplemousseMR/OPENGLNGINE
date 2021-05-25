#include "OpenGLNgine/Hardware/Program.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Hardware
{

Program::Program(ProgramManager* const _manager, const std::string& _name):
    Core::IResource(_name),
    m_manager(_manager)
{
}

Program::~Program()
{
}

void Program::attach(ShaderPtr _shader)
{
    switch(_shader->type)
    {
    case ST_VERTEX:
        m_vertexShader = _shader;
        break;
    case ST_GEOMETRY:
        m_geometryShader = _shader;
        break;
    case ST_FRAGMENT:
        m_fragmentShader = _shader;
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle shader type");
    }
}

void Program::link()
{
    if(m_vertexShader != nullptr)
    {
        m_program.attach(m_vertexShader->m_shader);
    }
    if(m_geometryShader != nullptr)
    {
        m_program.attach(m_geometryShader->m_shader);
    }
    if(m_fragmentShader != nullptr)
    {
        m_program.attach(m_fragmentShader->m_shader);
    }
    m_program.link();
}

void Program::setNamedAutoConstant(PROGRAM_PARAMETER _parameter, const std::string& _name)
{
    m_parameters.emplace(_parameter, GL::Uniform(_name, m_program.getId()));
}

}
