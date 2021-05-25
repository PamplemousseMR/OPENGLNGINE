#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Hardware/IndexData.hpp"
#include "OpenGLNgine/Hardware/Material.hpp"
#include "OpenGLNgine/Hardware/VertexData.hpp"

namespace Render
{

class Mesh;

class SubMesh final : public Core::IResource
{

    friend Mesh;

public:

    SubMesh(const SubMesh&) = delete;

    SubMesh(SubMesh&&) = delete;

    SubMesh& operator=(const SubMesh&) = delete;

    SubMesh& operator=(SubMesh&&) = delete;

    inline bool isDirty() const;

    inline void _notifyDirty() const;

    Hardware::VertexData* vertexData { nullptr };

    Hardware::IndexData* indexData { nullptr };

    Hardware::MaterialPtr material { nullptr };

    Mesh* const m_parent;

private:

    SubMesh(Mesh* const _mesh, const std::string& _name);

    ~SubMesh();

    mutable bool m_dirty { true };

};

inline bool SubMesh::isDirty() const
{
    return m_dirty;
}

inline void SubMesh::_notifyDirty() const
{
    m_dirty = false;
}

}
