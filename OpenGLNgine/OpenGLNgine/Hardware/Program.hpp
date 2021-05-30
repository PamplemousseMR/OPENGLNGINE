#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/GL/Program.hpp"
#include "OpenGLNgine/GL/Uniform.hpp"
#include "OpenGLNgine/Hardware/Shader.hpp"
#include "OpenGLNgine/Hardware/TextureUnitState.hpp"

#include <map>
#include <memory>
#include <string>

namespace Hardware
{

enum PROGRAM_PARAMETER
{
    PP_MODELVIEWPROJ_MATRIX,
    PP_MODELVIEW_MATRIX,
    PP_VIEW_MATRIX,
    PP_LIGHT_COUNT,
    PP_LIGHT_POSITION_WORLD_SPACE_ARRAY,
    PP_LIGHT_POSITION_VIEW_SPACE_ARRAY,
    PP_LIGHT_AMBIENT_COLOR_ARRAY,
    PP_LIGHT_DIFFUSE_COLOR_ARRAY,
    PP_LIGHT_SPECULAR_COLOR_ARRAY
};

class Program;
class ProgramManager;

typedef std::shared_ptr< Program > ProgramPtr;

class Program final : public ::Core::IResource
{

public:

    typedef std::map<PROGRAM_PARAMETER, ::GL::Uniform> AutoConstantMap;

    typedef std::map<std::string, std::pair< ::GL::Uniform, ::Hardware::TEXTUREUNITSTATE_SEMANTIC > > TextureConstantMap;

    Program(ProgramManager* const _manager, const std::string& _name);

    ~Program();

    Program(const Program&) = delete;

    Program(Program&&) = delete;

    Program& operator=(const Program&) = delete;

    Program& operator=(Program&&) = delete;

    inline void lock();

    inline void unlock();

    void attach(ShaderPtr _shader);

    void link();

    void setNamedAutoConstant(PROGRAM_PARAMETER _parameter, const std::string& _name);

    inline const AutoConstantMap& getAutoConstants() const;

    void setTextureConstant(const std::string& _name, ::Hardware::TEXTUREUNITSTATE_SEMANTIC _semantic);

    inline const TextureConstantMap& getTextureConstants() const;

private:

    ProgramManager* const m_manager;

    ::GL::Program m_program;

    ShaderPtr m_vertexShader { nullptr };

    ShaderPtr m_geometryShader { nullptr };

    ShaderPtr m_fragmentShader { nullptr };

    AutoConstantMap m_autoConstants {};

    TextureConstantMap m_textureConstants {};

};

inline void Program::lock()
{
    m_program.bind();
}

inline void Program::unlock()
{
    m_program.unbind();
}

inline const Program::AutoConstantMap& Program::getAutoConstants() const
{
    return m_autoConstants;
}

inline const Program::TextureConstantMap& Program::getTextureConstants() const
{
    return m_textureConstants;
}

}
