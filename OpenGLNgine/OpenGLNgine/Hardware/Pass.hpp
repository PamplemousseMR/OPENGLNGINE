#pragma once

#include "OpenGLNgine/GL/PixelOperation.hpp"
#include "OpenGLNgine/Hardware/Program.hpp"
#include "OpenGLNgine/Hardware/TextureUnitState.hpp"

#include <array>

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

    typedef std::list< TextureUnitState* > TextureUnitStateList;

    static ::GL::PIXELOPERATION_DEPTH getType(MATERIAL_DEPTH _type);

    static ::GL::PIXELOPERATION_BLEND getType(MATERIAL_BLEND _type);

    Pass(const Pass&) = delete;

    Pass(Pass&&) = delete;

    Pass& operator=(const Pass&) = delete;

    Pass& operator=(Pass&&) = delete;

    inline void setProgram(const ProgramPtr& program);

    void lock();

    void unlock();

    inline const Program::AutoConstantMap& getAutoConstants() const;

    inline const Program::TextureConstantMap& getTextureConstants() const;

    TextureUnitState* createTextureUnitState(TEXTUREUNITSTATE_SEMANTIC _semantic);

    void destroyAllTextureUnitStates();

    inline const TextureUnitStateList& getTextureUnitStates() const;

    std::array< bool, 4 > colorMask { true, true, true, true };

    bool depthTest { false };

    bool depthWrite { true };

    MATERIAL_DEPTH depthFunc { MD_LESS };

    bool blendTest { false };

    MATERIAL_BLEND sourceFactor { MB_ONE };

    MATERIAL_BLEND destinationFactor { MB_ZERO };

    /// Specifies whether meshes using this material must be rendered with backface culling.
    bool m_twoSided { true };

    /// Defines the opacity of the material.
    float m_opacity { 1.f };

    /// Gets the transparency factor.
    float m_transparencyfactor { 0.f };

    /// Defines the bump scaling of the material.
    float m_bumpScaling { 0.f };

    /// Defines the shininess of the material.
    float m_shininess { 0.f };

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
    ::glm::vec3 m_specular {0.f, 0.f, 0.f};

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
