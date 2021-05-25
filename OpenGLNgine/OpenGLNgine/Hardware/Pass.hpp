#pragma once

#include "OpenGLNgine/GL/PixelOperation.hpp"
#include "OpenGLNgine/Hardware/Program.hpp"

namespace Hardware
{

enum MATERIAL_DEPTH
{
    MD_NEVER,
    MD_LESS,
    MD_EQUAL,
    MD_LEQUAL,
    MD_GREATER,
    MD_NOTEQUAL,
    MD_GEQUAL,
    MD_ALWAYS
};

enum MATERIAL_BLEND
{
    MB_ZERO,
    MB_ONE,
    MB_SRC_COLOR,
    MB_ONE_MINUS_SRC_COLOR,
    MB_DST_COLOR,
    MB_ONE_MINUS_DST_COLOR,
    MB_SRC_ALPHA,
    MB_ONE_MINUS_SRC_ALPHA,
    MB_DST_ALPHA,
    MB_ONE_MINUS_DST_ALPHA,
    MB_CONSTANT_COLOR,
    MB_ONE_MINUS_CONSTANT_COLOR,
    MB_CONSTANT_ALPHA,
    MB_ONE_MINUS_CONSTANT_ALPHA,
    MB_SRC_ALPHA_SATURATE,
    MB_SRC1_COLOR,
    MB_ONE_MINUS_SRC1_COLOR,
    MB_SRC1_ALPHA,
    MB_ONE_MINUS_SRC1_ALPHA,
};

class Material;

class Pass
{

    friend Material;

public:

    static GL::PIXELOPERATION_DEPTH getType(MATERIAL_DEPTH _type);

    static GL::PIXELOPERATION_BLEND getType(MATERIAL_BLEND _type);

    inline void setProgram(const ProgramPtr& program);

    inline void lock();

    inline void unlock();

    std::array< bool, 4 > colorMask { true, true, true, true };

    bool depthTest { false };

    bool depthWrite { true };

    MATERIAL_DEPTH depthFunc { MD_LESS };

    bool blendTest { false };

    MATERIAL_BLEND sourceFactor { MB_ONE };

    MATERIAL_BLEND destinationFactor { MB_ZERO };

private:

    Pass();

    ~Pass();

    ProgramPtr m_program { nullptr };

};

void Pass::setProgram(const ProgramPtr& program)
{
    m_program = program;
}

inline void Pass::lock()
{
    m_program->lock();
}

inline void Pass::unlock()
{
    m_program->unlock();
}

}