#include "OpenGLNgine/Render/Mesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Core/Helper.hpp"
#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"
#include "OpenGLNgine/Render/Render.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

TEXTURE_TYPE fromAI(::aiTextureType _type)
{
    switch (_type) {
    case ::aiTextureType::aiTextureType_DIFFUSE:
        return TEXTURE_TYPE::TT_DIFFUSE;
        break;
    case ::aiTextureType::aiTextureType_SPECULAR:
        return TEXTURE_TYPE::TT_SPECULAR;
        break;
    case ::aiTextureType::aiTextureType_AMBIENT:
        return TEXTURE_TYPE::TT_AMBIENT;
        break;
    case ::aiTextureType::aiTextureType_EMISSIVE:
        return TEXTURE_TYPE::TT_EMISSIVE;
        break;
    case ::aiTextureType::aiTextureType_HEIGHT:
        return TEXTURE_TYPE::TT_HEIGHT;
        break;
    case ::aiTextureType::aiTextureType_NORMALS:
        return TEXTURE_TYPE::TT_NORMALS;
        break;
    case ::aiTextureType::aiTextureType_SHININESS:
        return TEXTURE_TYPE::TT_SHININESS;
        break;
    case ::aiTextureType::aiTextureType_OPACITY:
        return TEXTURE_TYPE::TT_OPACITY;
        break;
    case ::aiTextureType::aiTextureType_DISPLACEMENT:
        return TEXTURE_TYPE::TT_DISPLACEMENT;
        break;
    case ::aiTextureType::aiTextureType_LIGHTMAP:
        return TEXTURE_TYPE::TT_LIGHTMAP;
        break;
    case ::aiTextureType::aiTextureType_REFLECTION:
        return TEXTURE_TYPE::TT_REFLECTION;
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
}

WRAP_MODE fromAI(::aiTextureMapMode _mode)
{
    switch (_mode) {
    case ::aiTextureMapMode::aiTextureMapMode_Wrap:
        return WRAP_MODE::WM_REPEAT;
    case ::aiTextureMapMode::aiTextureMapMode_Clamp:
        return WRAP_MODE::WM_CLAMP;
    case ::aiTextureMapMode::aiTextureMapMode_Decal:
        return WRAP_MODE::WM_BORDER;
    case ::aiTextureMapMode::aiTextureMapMode_Mirror:
        return WRAP_MODE::WM_MIRROR;
    default:
        GLNGINE_EXCEPTION("Unhandle wrapping mode");
    }
}

SubMesh* Mesh::createSubMesh(const std::string& _name)
{
    SubMesh* ptr = new SubMesh(this, _name);
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
    SubMeshList::const_iterator itBeg, itEnd;
    itEnd = m_subMeshes.end();
    for(itBeg=m_subMeshes.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_subMeshes.clear();
}

void Mesh::setMaterial(::Hardware::MaterialPtr _material)
{
    SubMeshList::const_iterator itBeg, itEnd;
    itEnd = m_subMeshes.end();
    for(itBeg=m_subMeshes.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        (*itBeg)->m_material = _material;
    }
}

bool Mesh::load(const std::filesystem::path& _path)
{
    GLNGINE_ASSERT_IF(!std::filesystem::exists(_path), std::filesystem::is_regular_file(_path));

    ::Assimp::Importer importer;
    const ::aiScene* const scene = importer.ReadFile(_path.u8string(), aiProcess_FlipUVs | aiProcess_SortByPType | aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return false;
    }

    this->loadNode(scene->mRootNode, scene, _path.parent_path());
    return true;
}

void Mesh::loadNode(const ::aiNode* const _node, const ::aiScene* const _scene, const std::filesystem::path& _directory)
{
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
            const ::Hardware::HardwareVertexBufferPtr vertexBuffer = manager.createVertexBuffer(::Hardware::VT_FLOAT, vertices.size()*3, ::Hardware::HU_STATIC_DRAW);
            vertexBuffer->writeData(0, vertexBuffer->getSizeInBytes(), vertices.data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_POSITION, 0, ::Hardware::VET_FLOAT3, ::Hardware::VES_POSITION);

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_POSITION, vertexBuffer);
        }

        if(mesh->HasFaces())
        {
            subMesh->m_indexData = manager.createIndexData();

            const ::Hardware::HardwareIndexBufferPtr indexBuffer = manager.createIndexBuffer(::Hardware::IT_UNSIGNED_INT, indices.size(), ::Hardware::HU_STATIC_DRAW);
            subMesh->m_indexData->m_indexBuffer = indexBuffer;

            indexBuffer->writeData(0, indexBuffer->getSizeInBytes(), indices.data(), false);
            subMesh->m_indexData->m_indexCount = indices.size();
            subMesh->m_indexData->m_indexStart = 0;
        }

        for(unsigned col=0; col<mesh->GetNumColorChannels() && col<6; ++col)
        {
            const ::Hardware::HardwareVertexBufferPtr colorBuffer = manager.createVertexBuffer(::Hardware::VT_FLOAT, colors[col].size()*4, ::Hardware::HU_STATIC_DRAW);
            colorBuffer->writeData(0, colorBuffer->getSizeInBytes(), colors[col].data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_COLOR_0+col, 0, ::Hardware::VET_FLOAT4, ::Hardware::VERTEXELEMENT_SEMANTIC(::Hardware::VES_COLOR_0+col));

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_COLOR_0+col, colorBuffer);
        }

        if(mesh->HasNormals())
        {
            const ::Hardware::HardwareVertexBufferPtr normalBuffer = manager.createVertexBuffer(::Hardware::VT_FLOAT, normals.size()*3, ::Hardware::HU_STATIC_DRAW);
            normalBuffer->writeData(0, normalBuffer->getSizeInBytes(), normals.data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_NORMAL, 0, ::Hardware::VET_FLOAT3, ::Hardware::VES_NORMAL);

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_NORMAL, normalBuffer);
        }

        for(unsigned uv=0; uv<mesh->GetNumUVChannels() && uv<6; ++uv)
        {
            const ::Hardware::HardwareVertexBufferPtr textCoordBuffer = manager.createVertexBuffer(::Hardware::VT_FLOAT, textCoords[uv].size()*2, ::Hardware::HU_STATIC_DRAW);
            textCoordBuffer->writeData(0, textCoordBuffer->getSizeInBytes(), textCoords[uv].data(), false);

            subMesh->m_vertexData->m_vertexDeclaration->addElement(::Hardware::VES_TEXTURE_COORDINATES_0+uv, 0, ::Hardware::VET_FLOAT2, ::Hardware::VERTEXELEMENT_SEMANTIC(::Hardware::VES_TEXTURE_COORDINATES_0+uv));

            subMesh->m_vertexData->m_vertexBufferBinding->setBinding(::Hardware::VES_TEXTURE_COORDINATES_0+uv, textCoordBuffer);
        }

        if(mesh->HasTangentsAndBitangents())
        {
            const ::Hardware::HardwareVertexBufferPtr tangentBuffer = manager.createVertexBuffer(::Hardware::VT_FLOAT, vertices.size()*3*2, ::Hardware::HU_STATIC_DRAW);
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
    ::aiMaterial* const material = _scene->mMaterials[_mesh->mMaterialIndex];

    MaterialInfo* matInfo = Render::getInstance().createMaterialInfo(material->GetName().C_Str());
    _subMesh->m_materialInfo = matInfo;

    material->Get(AI_MATKEY_TWOSIDED, matInfo->m_twoSided);
    material->Get(AI_MATKEY_OPACITY, matInfo->m_opacity);
    material->Get(AI_MATKEY_TRANSPARENCYFACTOR, matInfo->m_transparencyfactor);
    material->Get(AI_MATKEY_BUMPSCALING, matInfo->m_bumpScaling);
    material->Get(AI_MATKEY_SHININESS, matInfo->m_shininess);
    material->Get(AI_MATKEY_REFLECTIVITY, matInfo->m_reflectivity);
    material->Get(AI_MATKEY_SHININESS_STRENGTH, matInfo->m_shininessStrenght);
    material->Get(AI_MATKEY_REFRACTI, matInfo->m_refracti);
    //material->Get(AI_MATKEY_SHADING_MODEL, matInfo->m_shadingModel);
    //material->Get(AI_MATKEY_ENABLE_WIREFRAME, matInfo->m_wireframe);
    //material->Get(AI_MATKEY_BLEND_FUNC, matInfo->m_blendFunc);

    ::aiColor3D data = ::Core::toAI(matInfo->m_ambient);
    material->Get(AI_MATKEY_COLOR_AMBIENT, data);
    matInfo->m_ambient = ::Core::fromAI(data);

    data = ::Core::toAI(matInfo->m_diffuse);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, data);
    matInfo->m_diffuse = ::Core::fromAI(data);

    data = ::Core::toAI(matInfo->m_specular);
    material->Get(AI_MATKEY_COLOR_SPECULAR, data);
    matInfo->m_specular = ::Core::fromAI(data);

    data = ::Core::toAI(matInfo->m_emissive);
    material->Get(AI_MATKEY_COLOR_EMISSIVE, data);
    matInfo->m_emissive = ::Core::fromAI(data);

    data = ::Core::toAI(matInfo->m_transparent);
    material->Get(AI_MATKEY_COLOR_TRANSPARENT, data);
    matInfo->m_transparent = ::Core::fromAI(data);

    data = ::Core::toAI(matInfo->m_colorReflective);
    material->Get(AI_MATKEY_COLOR_REFLECTIVE, data);
    matInfo->m_colorReflective = ::Core::fromAI(data);

    loadTexture(material, ::aiTextureType::aiTextureType_DIFFUSE, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_SPECULAR, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_AMBIENT, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_EMISSIVE, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_HEIGHT, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_NORMALS, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_SHININESS, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_OPACITY, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_DISPLACEMENT, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_LIGHTMAP, matInfo, _directory);
    loadTexture(material, ::aiTextureType::aiTextureType_REFLECTION, matInfo, _directory);
}

void Mesh::loadTexture(const ::aiMaterial* const _material, ::aiTextureType _type, MaterialInfo* const _matInfo, const std::filesystem::path& _directory)
{
    GLNGINE_ASSERT_IF(_material->GetTextureCount(_type) > 1, "Unhandle multiple textures");
    for(unsigned int i = 0; i < _material->GetTextureCount(_type); i++)
    {
        TextureInfo* const textInfo = _matInfo->addTextureInfo(fromAI(_type));

        ::aiTextureMapMode data = ::aiTextureMapMode::aiTextureMapMode_Wrap;
        _material->Get(_AI_MATKEY_MAPPINGMODE_U_BASE, _type, i, data);
        textInfo->m_uWrap = fromAI(data);

        data = ::aiTextureMapMode::aiTextureMapMode_Wrap;
        _material->Get(_AI_MATKEY_MAPPINGMODE_V_BASE, _type, i, data);
        textInfo->m_vWrap = fromAI(data);

        ::aiString path;
        _material->Get(_AI_MATKEY_TEXTURE_BASE, _type, i, path);
        textInfo->m_path = _directory/path.C_Str();

        // _material->Get(_AI_MATKEY_UVWSRC_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXOP_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_MAPPING_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXBLEND_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXMAP_AXIS_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_TEXFLAGS_BASE, _type, i, data);
        // _material->Get(_AI_MATKEY_UVTRANSFORM_BASE, _type, i, data);
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
}

}
