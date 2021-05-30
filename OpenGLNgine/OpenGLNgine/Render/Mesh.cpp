#include "OpenGLNgine/Render/Mesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

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
    const ::aiScene* const scene = importer.ReadFile(_path.u8string(), aiProcess_SortByPType | aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return false;
    }

    this->loadNode(scene->mRootNode, scene);
    return true;
}

void Mesh::loadNode(const ::aiNode* const _node, const ::aiScene* const _scene)
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
    }

    for(unsigned i=0; i<_node->mNumChildren; ++i)
    {
        this->loadNode(_node->mChildren[i], _scene);
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
