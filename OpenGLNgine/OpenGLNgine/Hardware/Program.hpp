#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/GL/Program.hpp"
#include "OpenGLNgine/Hardware/Shader.hpp"

#include <memory>

namespace Hardware
{

class Program;
class ProgramManager;

typedef std::shared_ptr< Program > ProgramPtr;

class Program final : public Core::IResource
{

public:

    Program(ProgramManager* const _manager, const std::string& _name);

    ~Program();

    Program(const Program&) = delete;

    Program(Program&&) = delete;

    Program& operator=(const Program&) = delete;

    Program& operator=(Program&&) = delete;

    int getIdTMP() const
    {
        return m_program.getId();
    }

    inline void lock();

    inline void unlock();

    void attach(ShaderPtr _shader);

    void link();

private:

    ProgramManager* const m_manager;

    GL::Program m_program;

    ShaderPtr m_vertexShader { nullptr };

    ShaderPtr m_geometryShader { nullptr };

    ShaderPtr m_fragmentShader { nullptr };

};

inline void Program::lock()
{
    m_program.bind();
}

inline void Program::unlock()
{
    m_program.unbind();
}

}
