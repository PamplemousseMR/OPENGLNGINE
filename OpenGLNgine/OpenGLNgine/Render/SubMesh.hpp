#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Hardware/IndexData.hpp"
#include "OpenGLNgine/Hardware/Material.hpp"
#include "OpenGLNgine/Hardware/VertexData.hpp"
#include "OpenGLNgine/Render/MaterialInfo.hpp"

namespace Render
{

class Mesh;

class SubMesh final : public ::Core::IResource
{

    friend MaterialInfo;
    friend Mesh;

public:

    SubMesh(const SubMesh&) = delete;

    SubMesh(SubMesh&&) = delete;

    SubMesh& operator=(const SubMesh&) = delete;

    SubMesh& operator=(SubMesh&&) = delete;

    inline bool isDirty() const;

    inline void _notifyDirty() const;

    void setMaterialInfo(MaterialInfo* const _matInfo);

    inline MaterialInfo* getMaterialInfo() const;

    ::Hardware::VertexData* m_vertexData { nullptr };

    ::Hardware::IndexData* m_indexData { nullptr };

    ::Hardware::MaterialPtr m_material { nullptr };

    Mesh* const m_parent;

private:

    SubMesh(Mesh* const _mesh, const std::string& _name);

    ~SubMesh();

    void _notifyMaterialInfoDestroyed();

    mutable bool m_dirty { true };

    MaterialInfo* m_materialInfo { nullptr };

};

inline bool SubMesh::isDirty() const
{
    return m_dirty;
}

inline void SubMesh::_notifyDirty() const
{
    m_dirty = false;
}

inline MaterialInfo* SubMesh::getMaterialInfo() const
{
    return m_materialInfo;
}

}
