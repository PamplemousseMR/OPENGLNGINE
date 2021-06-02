#pragma once

#include "OpenGLNgine/GL/PixelOperation.hpp"
#include "OpenGLNgine/GL/Rasterizer.hpp"
#include "OpenGLNgine/Hardware/Program.hpp"
#include "OpenGLNgine/Hardware/TextureUnitState.hpp"

#include <array>
#include <list>

namespace Hardware
{

enum PASS_DEPTH
{
    PD_NEVER,
    PD_LESS,
    PD_EQUAL,
    PD_LEQUAL,
    PD_GREATER,
    PD_NOTEQUAL,
    PD_GEQUAL,
    PD_ALWAYS
};

enum PASS_BLEND
{
    PB_ZERO,
    PB_ONE,
    PB_SRC_COLOR,
    PB_ONE_MINUS_SRC_COLOR,
    PB_DST_COLOR,
    PB_ONE_MINUS_DST_COLOR,
    PB_SRC_ALPHA,
    PB_ONE_MINUS_SRC_ALPHA,
    PB_DST_ALPHA,
    PB_ONE_MINUS_DST_ALPHA,
    PB_CONSTANT_COLOR,
    PB_ONE_MINUS_CONSTANT_COLOR,
    PB_CONSTANT_ALPHA,
    PB_ONE_MINUS_CONSTANT_ALPHA,
    PB_SRC_ALPHA_SATURATE,
    PB_SRC1_COLOR,
    PB_ONE_MINUS_SRC1_COLOR,
    PB_SRC1_ALPHA,
    PB_ONE_MINUS_SRC1_ALPHA,
};

enum PASS_CULLING
{
    PC_NONE,
    PC_FRONT,
    PC_BACK,
    PC_FRONT_AND_BACK
};

class Material;

class Pass
{

    friend Material;

public:

    typedef std::list< TextureUnitState* > TextureUnitStateList;

    static ::GL::PIXELOPERATION_DEPTH getType(PASS_DEPTH _type);

    static ::GL::PIXELOPERATION_BLEND getType(PASS_BLEND _type);

    static ::GL::RASTERIZER_CULLFACE getType(PASS_CULLING _type);

    Pass(const Pass&) = delete;

    Pass(Pass&&) = delete;

    Pass& operator=(const Pass&) = delete;

    Pass& operator=(Pass&&) = delete;

    inline void setProgram(const ProgramPtr& program);

    inline ProgramPtr getProgram() const;

    inline const Program::AutoConstantMap& getAutoConstants() const;

    inline const Program::TextureConstantMap& getTextureConstants() const;

    TextureUnitState* createTextureUnitState(TEXTUREUNITSTATE_SEMANTIC _semantic);

    void destroyAllTextureUnitStates();

    TextureUnitState* findTextureUnitStateBySemantic(TEXTUREUNITSTATE_SEMANTIC _semantic) const;

    inline const TextureUnitStateList& getTextureUnitStates() const;

    std::array< bool, 4 > m_colorMask { true, true, true, true };

    bool m_depthTest { false };

    bool m_depthWrite { true };

    PASS_DEPTH m_depthFunc { PD_LESS };

    bool m_blendTest { false };

    PASS_BLEND m_sourceFactor { PB_ONE };

    PASS_BLEND m_destinationFactor { PB_ZERO };

    PASS_CULLING m_culling { PC_NONE };

    /// Defines the opacity of the material.
    float m_opacity { 1.f };

    /// Gets the transparency factor.
    float m_transparencyfactor { 0.f };

    /// Defines the bump scaling of the material.
    float m_bumpScaling { 0.f };

    /// Defines the shininess of the material.
    float m_shininess { 1.f };

    /// Defines the reflectivity of the material.
    float m_reflectivity { 0.f };

    /// Scales the specular color of the material.
    float m_shininessStrenght { 1.f };

    /// Defines the index of refraction for the material.
    float m_refracti { 1.f };

    /// Defines the ambient color of the material.
    ::glm::vec3 m_ambient {1.f, 1.f, 1.f};

    /// Defines the diffuse color of the material.
    ::glm::vec3 m_diffuse {1.f, 1.f, 1.f};

    /// Defines the specular color of the material.
    ::glm::vec3 m_specular {1.f, 1.f, 1.f};

    /// Defines the emissive color of the material.
    ::glm::vec3 m_emissive {0.f, 0.f, 0.f};

    /// Defines the transparent color of the material.
    ::glm::vec3 m_transparent {1.f, 1.f, 1.f};

    /// Defines the color reflective of the material.
    ::glm::vec3 m_colorReflective { 0.f, 0.f, 0.f };

private:

    Pass();

    ~Pass();

    ProgramPtr m_program { nullptr };

    TextureUnitStateList m_textureUnitStates {};

};

void Pass::setProgram(const ProgramPtr& program)
{
    m_program = program;
}

inline ProgramPtr Pass::getProgram() const
{
    return m_program;
}

inline const Program::AutoConstantMap& Pass::getAutoConstants() const
{
    return m_program->getAutoConstants();
}

inline const Program::TextureConstantMap& Pass::getTextureConstants() const
{
    return m_program->getTextureConstants();
}

inline const Pass::TextureUnitStateList& Pass::getTextureUnitStates() const
{
    return m_textureUnitStates;
}

}
