#pragma once

#include "OpenGLNgine/Hardware/IndexData.hpp"
#include "OpenGLNgine/Hardware/Material.hpp"
#include "OpenGLNgine/Hardware/VertexData.hpp"
#include "OpenGLNgine/Render/Component.hpp"
#include "OpenGLNgine/Render/SubMesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <set>

namespace Render
{

class SceneManager;

class Mesh final : public Component
{

    friend SceneManager;

public:

    typedef std::set<SubMesh*> SubMeshList;

    Mesh(const Mesh&) = delete;

    Mesh(Mesh&&) = delete;

    Mesh& operator=(const Mesh&) = delete;

    Mesh& operator=(Mesh&&) = delete;

    SubMesh* createSubMesh(const std::string& _name);

    void destroySubMesh(SubMesh* _subMesh);

    void destroyAllSubMeshes();

    inline const SubMeshList& getSubMeshes() const;

    void setMaterial(::Hardware::MaterialPtr _material);

    bool load(const std::filesystem::path& _path);

private:

    Mesh(SceneManager* const _sceneManager, const std::string& _name);

    ~Mesh();

    void loadNode(const ::aiNode* const _node, const ::aiScene* const _scene);

    SubMeshList m_subMeshes {};

};

inline const Mesh::SubMeshList& Mesh::getSubMeshes() const
{
    return m_subMeshes;
}

}
