#pragma once

#include "OpenGLNgine/Core/IManager.hpp"
#include "OpenGLNgine/Hardware/Program.hpp"
#include "OpenGLNgine/Hardware/Shader.hpp"

namespace Hardware
{

class ProgramManager final :
        public ::Core::IManager< Shader >,
        public ::Core::IManager< Program >
{

public:

    static ProgramManager& getInstance();

    ProgramManager(const ProgramManager&) = delete;

    ProgramManager(ProgramManager&&) = delete;

    ProgramManager& operator=(const ProgramManager&) = delete;

    ProgramManager& operator=(ProgramManager&&) = delete;

    ProgramPtr createProgram(const std::string& _name);

    ShaderPtr createShader(const std::string& _name, SHADER_TYPE _type);

private:

    struct Initializer final
    {
        Initializer();

        ~Initializer();
    };

    static ProgramManager* s_instance;

    ProgramManager();

    ~ProgramManager();

};

}
