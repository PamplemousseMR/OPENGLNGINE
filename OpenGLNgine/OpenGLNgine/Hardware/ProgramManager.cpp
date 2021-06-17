#include "OpenGLNgine/Hardware/ProgramManager.hpp"

namespace Hardware
{

ProgramPtr ProgramManager::createProgram(const std::string& _name)
{
    const ProgramPtr ptr(new Program(this, _name));
    this->add(ptr);
    return ptr;
}

ShaderPtr ProgramManager::createShader(const std::string& _name, SHADER_TYPE _type)
{
    const ShaderPtr ptr(new Shader(this, _name, _type));
    this->add(ptr);
    return ptr;
}

ProgramManager::ProgramManager():
    ::Core::IHardwareManager()
{
}

ProgramManager::~ProgramManager()
{
}

}
