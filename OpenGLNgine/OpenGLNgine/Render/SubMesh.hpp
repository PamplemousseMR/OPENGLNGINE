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

    bool useSharedVertices {false};

    Hardware::VertexData* vertexData { nullptr };

    Hardware::IndexData* indexData { nullptr };

    Hardware::MaterialPtr material { nullptr };

    Mesh* const m_parent;

private:

    SubMesh(Mesh* const _mesh, const std::string& _name);

    ~SubMesh();

};

}
