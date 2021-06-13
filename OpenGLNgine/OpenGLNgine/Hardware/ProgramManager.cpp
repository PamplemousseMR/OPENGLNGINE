#include "OpenGLNgine/Hardware/ProgramManager.hpp"

namespace Hardware
{

ProgramManager* ProgramManager::s_instance = nullptr;

ProgramManager& ProgramManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

ProgramPtr ProgramManager::createProgram(const std::string& _name)
{
    const ProgramPtr ptr(new Program(this, _name));
    ::Core::IManager< Program >::add(ptr);
    return ptr;
}

ShaderPtr ProgramManager::createShader(const std::string& _name, SHADER_TYPE _type)
{
    const ShaderPtr ptr(new Shader(this, _name, _type));
    ::Core::IManager< Shader >::add(ptr);
    return ptr;
}

ProgramManager::Initializer::Initializer()
{
    ProgramManager::s_instance = new ProgramManager();
}

ProgramManager::Initializer::~Initializer()
{
    delete ProgramManager::s_instance;
    ProgramManager::s_instance = nullptr;
}

ProgramManager::ProgramManager():
    ::Core::IManager<Shader>()
{
}

ProgramManager::~ProgramManager()
{
}

}
