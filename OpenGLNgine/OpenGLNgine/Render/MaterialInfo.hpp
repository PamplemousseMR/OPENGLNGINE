#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Render/TextureInfo.hpp"

#include <glm/glm.hpp>

#include <list>
#include <map>

namespace Render
{

class Render;
class SubMesh;

class MaterialInfo final : public ::Core::IResource
{
    friend Render;
    friend SubMesh;

public:

    typedef std::map<TEXTURE_TYPE, TextureInfo*> TextureInfoList;

    MaterialInfo(const MaterialInfo&) = delete;

    MaterialInfo(MaterialInfo&&) = delete;

    MaterialInfo& operator=(const MaterialInfo&) = delete;

    MaterialInfo& operator=(MaterialInfo&&) = delete;

    TextureInfo* addTextureInfo(TEXTURE_TYPE _type);

    TextureInfo* getTextureInfo(TEXTURE_TYPE _type);

    void removeAllTextureInfos();

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

    typedef std::map< std::string, SubMesh* const > SubMeshList;

    MaterialInfo(const std::string& _name);

    ~MaterialInfo();

    void _notifySubMeshAdded(SubMesh* const _subMesh);

    void _notifySubMeshRemoved(SubMesh* const _subMesh);

    SubMeshList m_subMeshes {};

    TextureInfoList m_textureInfos {};

};

}
