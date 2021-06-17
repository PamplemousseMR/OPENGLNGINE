#pragma once

#include "OpenGLNgine/Core/IHardwareResource.hpp"
#include "OpenGLNgine/GL/Shader.hpp"

#include <filesystem>
#include <memory>

namespace Hardware
{

enum SHADER_TYPE
{
    ST_VERTEX,
    ST_GEOMETRY,
    ST_FRAGMENT
};

class Program;
class Shader;
class ProgramManager;

typedef std::shared_ptr< Shader > ShaderPtr;

class Shader final : public ::Core::IHardwareResource
{

    friend Program;
    friend ProgramManager;

public:

    ~Shader();

    Shader(const Shader&) = delete;

    Shader(Shader&&) = delete;

    Shader& operator=(const Shader&) = delete;

    Shader& operator=(Shader&&) = delete;

    void setSourceFromFile(const std::filesystem::path& _path);

    void load();

    const SHADER_TYPE type;

private:

    static ::GL::SHADER_TYPE getType(SHADER_TYPE _type);

    Shader(ProgramManager* const _manager, const std::string& _name, SHADER_TYPE _type);

    ::GL::Shader m_shader;

};

}
