#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <vector>

namespace GL
{
    class Buffer;
}

namespace Component
{
class Mesh
{

public:

    static const int S_VERTEXLOCATION;
    static const int S_TEXTCOORDLOCATION;
    static const int S_NORMALLOCATION;

public:

    Mesh(const std::string&) noexcept;
    ~Mesh() noexcept;

    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
    void bind() const noexcept;
    void unbind() const noexcept;
    void draw() const noexcept;

    const std::string& getName() const noexcept;
    int getVertexLocation() const noexcept;
    int getTextureCoordLocation() const noexcept;
    int getNormalLocation() const noexcept;
    bool hasTextureCoord() const noexcept;
    bool hasNormal() const noexcept;

    std::ostream& print(std::ostream&) const noexcept;

private:

    struct PackedVertex
    {
        glm::vec3 m_position;
        glm::vec2 m_uv;
        glm::vec3 m_normal;

        bool operator<(const PackedVertex _that) const
        {
            return memcmp((void*)this, (void*)&_that, sizeof(PackedVertex))>0;
        }
    };

    bool getSimilarVertexIndex(const PackedVertex&, const std::map<PackedVertex, unsigned int>&, unsigned int&) const noexcept;
    void indexVBO(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&, std::vector<unsigned int>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&) const noexcept;

private:

    int m_dataSize;
    GL::Buffer* m_vboVertex;
    GL::Buffer* m_vboNormal;
    GL::Buffer* m_vboTextCoord;
    GL::Buffer* m_ebo;
    GL::Buffer* m_vao;
    std::string m_name;
    bool m_normal;
    bool m_textCoord;

};

std::ostream& operator<<(std::ostream&, const Mesh&) noexcept;

}
