#include "OpenGLNgine/Render/Mesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Core/Helper.hpp"
#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"
#include <OpenGLNgine/Hardware/MaterialManager.hpp>
#include <OpenGLNgine/Hardware/TextureManager.hpp>
#include "OpenGLNgine/Render/Render.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

::Hardware::TEXTUREUNITSTATE_SEMANTIC fromAI(::aiTextureType _type)
{
    switch (_type) {
    case ::aiTextureType::aiTextureType_DIFFUSE:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_DIFFUSE;
        break;
    case ::aiTextureType::aiTextureType_SPECULAR:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_SPECULAR;
        break;
    case ::aiTextureType::aiTextureType_AMBIENT:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_AMBIENT;
        break;
    case ::aiTextureType::aiTextureType_EMISSIVE:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_EMISSIVE;
        break;
    case ::aiTextureType::aiTextureType_HEIGHT:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_HEIGHT;
        break;
    case ::aiTextureType::aiTextureType_NORMALS:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_NORMALS;
        break;
    case ::aiTextureType::aiTextureType_SHININESS:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_SHININESS;
        break;
    case ::aiTextureType::aiTextureType_OPACITY:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_OPACITY;
        break;
    case ::aiTextureType::aiTextureType_DISPLACEMENT:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_DISPLACEMENT;
        break;
    case ::aiTextureType::aiTextureType_LIGHTMAP:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_LIGHTMAP;
        break;
    case ::aiTextureType::aiTextureType_REFLECTION:
        return ::Hardware::TEXTUREUNITSTATE_SEMANTIC::TS_REFLECTION;
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
}

::aiTextureMapMode toAI(::Hardware::TEXTURE_WRAP _mode)
{
    switch (_mode) {
    case ::Hardware::TEXTURE_WRAP::TW_REPEAT:
        return ::aiTextureMapMode::aiTextureMapMode_Wrap;
    case ::Hardware::TEXTURE_WRAP::TW_CLAMP:
        return ::aiTextureMapMode::aiTextureMapMode_Clamp;
    case ::Hardware::TEXTURE_WRAP::TW_BORDER:
        return ::aiTextureMapMode::aiTextureMapMode_Decal;
    case ::Hardware::TEXTURE_WRAP::TW_MIRROR:
        return ::aiTextureMapMode::aiTextureMapMode_Mirror;
    default:
        GLNGINE_EXCEPTION("Unhandle wrapping mode");
    }
}

::Hardware::TEXTURE_WRAP fromAI(::aiTextureMapMode _mode)
{
    switch (_mode) {
    case ::aiTextureMapMode::aiTextureMapMode_Wrap:
        return ::Hardware::TEXTURE_WRAP::TW_REPEAT;
    case ::aiTextureMapMode::aiTextureMapMode_Clamp:
        return ::Hardware::TEXTURE_WRAP::TW_CLAMP;
    case ::aiTextureMapMode::aiTextureMapMode_Decal:
        return ::Hardware::TEXTURE_WRAP::TW_BORDER;
    case ::aiTextureMapMode::aiTextureMapMode_Mirror:
        return ::Hardware::TEXTURE_WRAP::TW_MIRROR;
    default:
        GLNGINE_EXCEPTION("Unhandle wrapping mode");
    }
}

void Mesh::_notifyMeshAttached(SceneNode* const _node)
{
    GLNGINE_ASSERT_IF(!_node, "The scene node mustn't be null");

    m_parents.emplace(_node->getName(), _node);
}

void Mesh::_notifyMeshDettached(SceneNode* const _node)
{
    GLNGINE_ASSERT_IF(!_node, "The scene node mustn't be null");
    ParentList::const_iterator it = m_parents.find(_node->getName());
    if(it == m_parents.end())
    {
        GLNGINE_EXCEPTION("A scene node with the name '" + _node->getName() + "' doesn't exists");
    }

    m_parents.erase(it);
}

SubMesh* Mesh::createSubMesh(const std::string& _name)
{
    SubMesh* const ptr = new SubMesh(this, _name);
    m_subMeshes.insert(ptr);
    return ptr;
}

void Mesh::destroySubMesh(SubMesh* _subMesh)
{
    GLNGINE_ASSERT_IF(!_subMesh, "The sub mesh mustn't be null");

    m_subMeshes.erase(_subMesh);
    delete _subMesh;
}

void Mesh::destroyAllSubMeshes()
{
    SubMeshList::const_iterator itBeg = m_subMeshes.begin();
    const SubMeshList::const_iterator itEnd = m_subMeshes.end();
    for(; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_subMeshes.clear();
}

void Mesh::setMaterial(::Hardware::MaterialPtr _material)
{
    SubMeshList::const_iterator itBeg = m_subMeshes.begin();
    const SubMeshList::const_iterator itEnd = m_subMeshes.end();
    for(; itBeg!=itEnd ; ++itBeg)
    {
        (*itBeg)->m_material = _material;
    }
}

bool Mesh::load(const std::filesystem::path& _path)
{
    GLNGINE_ASSERT_IF(!std::filesystem::exists(_path), std::filesystem::is_regular_file(_path));

    ::Assimp::Importer importer;
    const ::aiScene* const scene = importer.ReadFile(_path.u8string(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs | aiProcess_SortByPType | aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return false;
    }

    this->loadNode(scene->mRootNode, scene, _path.parent_path());
    return true;
}

void Mesh::loadNode(const ::aiNode* const _node, const ::aiScene* const _scene, const std::filesystem::path& _directory)
{
    GLNGINE_ASSERT_IF(!_node, "The node mustn't be null");
    GLNGINE_ASSERT_IF(!_scene, "The scene mustn't be null");

    ::Hardware::HardwareBufferManager& manager = ::Hardware::HardwareBufferManager::getInstance();

    for(unsigned i=0; i<_node->mNumMeshes; ++i)
    {
        const aiMesh* const mesh = _scene->mMeshes[_node->mMeshes[i]];

        std::vector< ::glm::vec3 > vertices;
        std::vector< unsigned int > indices;
        std::array< std::vector< ::glm::vec4 >, 8 > colors;
        std::vector< ::glm::vec3 > normals;
        std::array< std::vector< ::glm::vec2 >, 8 > textCoords;
        std::vector< ::glm::vec3 > tangents;
#pragma omp parallel sections
        {
#pragma omp section
            {
                if(mesh->HasPositions())
                {
                    vertices.reserve(mesh->mNumVertices);
                    for(unsigned idx=0; idx<mesh->mNumVertices; ++idx)
                    {
                        const glm::vec3 vertex(mesh->mVertices[idx].x, mesh->mVertices[idx].y, mesh->mVertices[idx].z);
                        vertices.push_back(vertex);
                    }
                }
            }
#pragma omp section
            {
                if(mesh->HasFaces())
                {
                    indices.reserve(mesh->mNumFaces);
                    for(unsigned idx=0; idx<mesh->mNumFaces; ++idx)
                    {
                        aiFace face = mesh->mFaces[idx];
                        for(unsigned int j = 0; j < face.mNumIndices; j++)
                        {
                            indices.push_back(face.mIndices[j]);
                        }
                    }
                }
            }
#pragma omp section
            {
                for(unsigned col=0; col< mesh->GetNumColorChannels() ; ++col)
                {
                    colors[col].reserve(mesh->mNumVertices);
                    for(unsigned idx=0; idx<mesh->mNumVertices; ++idx)
                    {
                        const glm::vec4 color(mesh->mColors[col][idx].r, mesh->mColors[col][idx].g, mesh->mColors[col][idx].b, mesh->mColors[col][idx].a);
                        colors[col].push_back(color);
                    }
                }
            }
#pragma omp section
            {
                if(mesh->HasNormals())
                {
                    normals.reserve(mesh->mNumVertices);
                    for(unsigned idx=0; idx<mesh->mNumVertices; ++idx)
                    {
                        const glm::vec3 normal(mesh->mNormals[idx].x, mesh->mNormals[idx].y, mesh->mNormals[idx].z);
                        normals.push_back(normal);
                    }
                }
            }
#pragma omp section
            {
                for(unsigned uv=0; uv< mesh->GetNumUVChannels() ; ++uv)
                {
                    textCoords[uv].reserve(mesh->mNumVertices);
                    for(unsigned idx=0; idx<mesh->mNumVertices; ++idx)
                    {
                        const glm::vec2 textCoord(mesh->mTextureCoords[uv][idx].x, mesh->mTextureCoords[uv][idx].y);
                        textCoords[uv].push_back(textCoord);
                    }
                }
            }
#pragma omp section
            {
                if(mesh->HasTangentsAndBitangents())
                {
                    tangents.reserve(mesh->mNumVertices * 2);
                    for(unsigned idx=0; idx<mesh->mNumVertices; ++idx)
                    {
                        const glm::vec3 tangent(mesh->mTangents[idx].x, mesh->mTangents[idx].y, mesh->mTangents[idx].z);
                        tangents.push_back(tangent);
                        const glm::vec3 bitangent(mesh->mBitangents[idx].x, mesh->mBitangents[idx].y, mesh->mBitangents[idx].z);
                        tangents.push_back(bitangent);
                    }
                }
            }
        }

        ::Render::SubMesh* const subMesh = this->createSubMesh(mesh->mName.C_Str());

        subMesh->m_vertexData = manager.createVertexData();
        switch (mesh->mPrimitiveTypes) {
        case ::aiPrimitiveType::aiPrimitiveType_POINT:
            subMesh->m_vertexData->m_renderOperation = ::Hardware::VR_POINTS;
            break;
        case ::aiPrimitiveType::aiPrimitiveType_LINE:
            subMesh->m_vertexData->m_renderOperation = ::Hardware::VR_LINES;
            break;
        case ::aiPrimitiveType::aiPrimitiveType_TRIANGLE:
            subMesh->m_vertexData->m_renderOperation = ::Hardware::VR_TRIANGLES;
            break;
        default:
            GLNGINE_EXCEPTION("Unhandle primitive type");
        }

        subMesh->m_vertexData->m_vertexStart = 0;
        subMesh->m_vertexData->m_vertexCount = mesh->mNumVertices;

        if(mesh->HasPositions())
        {
            const ::Hardware::HardwareVertexBufferPtr vertexBuffer = manager.createVertexBuffer(::Hardware::HT_FLOAT, vertices.size()*3, ::Hardware::HU_STATIC_DRAW);
            vertexBuffer->lock();
            vertexBuffer->writeData(0, vertexBuffer->getSizeInBytes(), vertices.data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_POSITION, 0, ::Hardware::VET_FLOAT3, ::Hardware::VES_POSITION);

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_POSITION, vertexBuffer);
        }

        if(mesh->HasFaces())
        {
            subMesh->m_indexData = manager.createIndexData();

            const ::Hardware::HardwareIndexBufferPtr indexBuffer = manager.createIndexBuffer(::Hardware::HT_UNSIGNED_INT, indices.size(), ::Hardware::HU_STATIC_DRAW);
            subMesh->m_indexData->m_indexBuffer = indexBuffer;
            indexBuffer->lock();
            indexBuffer->writeData(0, indexBuffer->getSizeInBytes(), indices.data(), false);
            subMesh->m_indexData->m_indexCount = static_cast< unsigned >(indices.size());
            subMesh->m_indexData->m_indexStart = 0;
        }

        for(unsigned col=0; col<mesh->GetNumColorChannels() && col<6; ++col)
        {
            const ::Hardware::HardwareVertexBufferPtr colorBuffer = manager.createVertexBuffer(::Hardware::HT_FLOAT, colors[col].size()*4, ::Hardware::HU_STATIC_DRAW);
            colorBuffer->lock();
            colorBuffer->writeData(0, colorBuffer->getSizeInBytes(), colors[col].data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_COLOR_0+col, 0, ::Hardware::VET_FLOAT4, ::Hardware::VERTEXELEMENT_SEMANTIC(::Hardware::VES_COLOR_0+col));

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_COLOR_0+col, colorBuffer);
        }

        if(mesh->HasNormals())
        {
            const ::Hardware::HardwareVertexBufferPtr normalBuffer = manager.createVertexBuffer(::Hardware::HT_FLOAT, normals.size()*3, ::Hardware::HU_STATIC_DRAW);
            normalBuffer->lock();
            normalBuffer->writeData(0, normalBuffer->getSizeInBytes(), normals.data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_NORMAL, 0, ::Hardware::VET_FLOAT3, ::Hardware::VES_NORMAL);

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_NORMAL, normalBuffer);
        }

        for(unsigned uv=0; uv<mesh->GetNumUVChannels() && uv<6; ++uv)
        {
            const ::Hardware::HardwareVertexBufferPtr textCoordBuffer = manager.createVertexBuffer(::Hardware::HT_FLOAT, textCoords[uv].size()*2, ::Hardware::HU_STATIC_DRAW);
            textCoordBuffer->lock();
            textCoordBuffer->writeData(0, textCoordBuffer->getSizeInBytes(), textCoords[uv].data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_TEXTURE_COORDINATES_0+uv, 0, ::Hardware::VET_FLOAT2, ::Hardware::VERTEXELEMENT_SEMANTIC(::Hardware::VES_TEXTURE_COORDINATES_0+uv));

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_TEXTURE_COORDINATES_0+uv, textCoordBuffer);
        }

        if(mesh->HasTangentsAndBitangents())
        {
            const ::Hardware::HardwareVertexBufferPtr tangentBuffer = manager.createVertexBuffer(::Hardware::HT_FLOAT, vertices.size()*3*2, ::Hardware::HU_STATIC_DRAW);
            tangentBuffer->lock();
            tangentBuffer->writeData(0, tangentBuffer->getSizeInBytes(), tangents.data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_BITANGENT, 0, ::Hardware::VET_FLOAT3, ::Hardware::VES_TANGENT);
            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_BITANGENT, sizeof(float)*3, ::Hardware::VET_FLOAT3, ::Hardware::VES_BITANGENT);

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_BITANGENT, tangentBuffer);
        }

        if(mesh->mMaterialIndex >= 0)
        {
            this->loadMaterial(subMesh, _scene, mesh, _directory);
        }
    }

    for(unsigned i=0; i<_node->mNumChildren; ++i)
    {
        this->loadNode(_node->mChildren[i], _scene, _directory);
    }
}

void Mesh::loadMaterial(::Render::SubMesh* const _subMesh, const ::aiScene* const _scene, const aiMesh* const _mesh, const std::filesystem::path& _directory)
{
    GLNGINE_ASSERT_IF(!_subMesh, "The sub mesh mustn't be null");
    GLNGINE_ASSERT_IF(!_scene, "The scene mustn't be null");
    GLNGINE_ASSERT_IF(!_mesh, "The mesh mustn't be null");

    ::aiMaterial* const aiMaterial = _scene->mMaterials[_mesh->mMaterialIndex];

    ::Hardware::MaterialManager& materialMng = ::Hardware::MaterialManager::getInstance();
    ::Hardware::MaterialPtr material = materialMng.getByName(aiMaterial->GetName().C_Str());
    if(!material)
    {
        material = materialMng.create(aiMaterial->GetName().C_Str());
        ::Hardware::Pass* pass = material->getPasses()[0];

        aiMaterial->Get(AI_MATKEY_OPACITY, pass->m_opacity);
        aiMaterial->Get(AI_MATKEY_TRANSPARENCYFACTOR, pass->m_transparencyfactor);
        aiMaterial->Get(AI_MATKEY_BUMPSCALING, pass->m_bumpScaling);
        aiMaterial->Get(AI_MATKEY_SHININESS, pass->m_shininess);
        aiMaterial->Get(AI_MATKEY_REFLECTIVITY, pass->m_reflectivity);
        aiMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, pass->m_shininessStrenght);
        aiMaterial->Get(AI_MATKEY_REFRACTI, pass->m_refracti);
        //aiMaterial->Get(AI_MATKEY_TWOSIDED, pass->m_culling);
        //aiMaterial->Get(AI_MATKEY_SHADING_MODEL, pass->m_shadingModel);
        //aiMaterial->Get(AI_MATKEY_ENABLE_WIREFRAME, pass->m_wireframe);
        //aiMaterial->Get(AI_MATKEY_BLEND_FUNC, pass->m_blendFunc);

        ::aiColor3D data = ::Core::toAI(pass->m_ambient);
        aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, data);
        pass->m_ambient = ::Core::fromAI(data);

        data = ::Core::toAI(pass->m_diffuse);
        aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, data);
        pass->m_diffuse = ::Core::fromAI(data);

        data = ::Core::toAI(pass->m_specular);
        aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, data);
        pass->m_specular = ::Core::fromAI(data);

        data = ::Core::toAI(pass->m_emissive);
        aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, data);
        pass->m_emissive = ::Core::fromAI(data);

        data = ::Core::toAI(pass->m_transparent);
        aiMaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, data);
        pass->m_transparent = ::Core::fromAI(data);

        data = ::Core::toAI(pass->m_colorReflective);
        aiMaterial->Get(AI_MATKEY_COLOR_REFLECTIVE, data);
        pass->m_colorReflective = ::Core::fromAI(data);

        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_DIFFUSE, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_SPECULAR, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_AMBIENT, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_EMISSIVE, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_HEIGHT, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_NORMALS, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_SHININESS, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_OPACITY, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_DISPLACEMENT, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_LIGHTMAP, pass, _directory);
        loadTexture(aiMaterial, ::aiTextureType::aiTextureType_REFLECTION, pass, _directory);
    }

    _subMesh->m_material = material;
}

void Mesh::loadTexture(const aiMaterial* const _aiMaterial, ::aiTextureType _type, ::Hardware::Pass* const _pass, const std::filesystem::path& _directory)
{
    GLNGINE_ASSERT_IF(!_aiMaterial, "The aiMaterial mustn't be null");
    GLNGINE_ASSERT_IF(!_pass, "The pass mustn't be null");

    GLNGINE_ASSERT_IF(_aiMaterial->GetTextureCount(_type) > 1, "Unhandle multiple textures");

    ::Hardware::TextureManager& textureManager = ::Hardware::TextureManager::getInstance();

    for(unsigned int i = 0; i < _aiMaterial->GetTextureCount(_type); i++)
    {
        ::Hardware::TextureUnitState* textUnitState = _pass->createTextureUnitState(fromAI(_type));

        ::aiTextureMapMode data = toAI(textUnitState->m_uWrap);
        _aiMaterial->Get(_AI_MATKEY_MAPPINGMODE_U_BASE, _type, i, data);
        textUnitState->m_uWrap = fromAI(data);

        data = toAI(textUnitState->m_vWrap);
        _aiMaterial->Get(_AI_MATKEY_MAPPINGMODE_V_BASE, _type, i, data);
        textUnitState->m_vWrap = fromAI(data);

        // _material->Get(_AI_MATKEY_UVWSRC_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXOP_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_MAPPING_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXBLEND_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXMAP_AXIS_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXFLAGS_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_UVTRANSFORM_BASE, _type, i, data);

        ::aiString aiPath;
        _aiMaterial->Get(_AI_MATKEY_TEXTURE_BASE, _type, i, aiPath);

        std::filesystem::path path(aiPath.C_Str());
        if(path.is_relative())
        {
            path = _directory/path;
        }

        const std::string textName = path.stem().u8string();
        ::Hardware::TexturePtr texture = textureManager.getByName(textName);
        if(!texture)
        {
            texture = textureManager.create(textName, ::Hardware::TT_2D);
            texture->lock();
            texture->load(path, ::Hardware::TIF_RGBA);
        }

        textUnitState->setTexture(texture);
    }
}

Mesh::Mesh(SceneManager* const _sceneManager, const std::string& _name):
    Component(_sceneManager, _name)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");
}

Mesh::~Mesh()
{
    this->destroyAllSubMeshes();
    for(const auto& node : m_parents)
    {
        node.second->_notifyMeshDestroyed(m_name);
    }
}

}
