#pragma once

#include "OpenGLNgine/Core/IHardwareManager.hpp"
#include "OpenGLNgine/Hardware/Program.hpp"
#include "OpenGLNgine/Hardware/Shader.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class ProgramManager final :
        public ::Core::IHardwareManager
{

    friend ::Render::RenderWindow;

public:

    ProgramManager(const ProgramManager&) = delete;

    ProgramManager(ProgramManager&&) = delete;

    ProgramManager& operator=(const ProgramManager&) = delete;

    ProgramManager& operator=(ProgramManager&&) = delete;

    ProgramPtr createProgram(const std::string& _name);

    ShaderPtr createShader(const std::string& _name, SHADER_TYPE _type);

private:

    ProgramManager(const ::Render::RenderWindow* const _renderWindow);

    ~ProgramManager();

};

}
