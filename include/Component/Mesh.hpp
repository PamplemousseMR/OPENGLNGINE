#pragma once

#include "Component.hpp"

#include <GL/glew.h>

#include <glm/vec3.hpp>

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <vector>

namespace Assets
{
    class Material;
}

namespace GL
{
    class Buffer;
}

namespace Component
{
class Mesh : public Component
{

public:

    static const GLuint S_VERTEXLOCATION;
    static const GLuint S_TEXTCOORDLOCATION;
    static const GLuint S_NORMALLOCATION;

public:

    Mesh(const std::string&) noexcept;
    ~Mesh() noexcept;
    Mesh(const Mesh&);
    Mesh& operator=(const Mesh&);

    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
    void bind() const noexcept;
    void unbind() const noexcept;
    inline void draw() const noexcept;

    inline const std::string& getName() const noexcept;
    inline GLuint getVertexLocation() const noexcept;
    inline GLuint getTextureCoordLocation() const noexcept;
    inline GLuint getNormalLocation() const noexcept;
    inline Assets::Material* getMaterial() const noexcept;
    inline bool hasTextureCoord() const noexcept;

    std::ostream& print(std::ostream&) const noexcept;

private:

    struct PackedVertex
    {
        glm::vec3 m_position;
        glm::vec2 m_uv;
        glm::vec3 m_normal;

        bool operator<(const PackedVertex _that) const
        {
            return std::memcmp(this, &_that, sizeof(PackedVertex))>0;
        }
    };

private:

    bool getSimilarVertexIndex(const PackedVertex&, const std::map<PackedVertex, unsigned int>&, unsigned int&) const noexcept;
    void indexVBO(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&, std::vector<unsigned int>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&) const noexcept;

private:

    int m_dataSize {0};
    GL::Buffer* m_vboVertex {nullptr};
    GL::Buffer* m_vboNormal {nullptr};
    GL::Buffer* m_vboTextCoord {nullptr};
    GL::Buffer* m_ebo {nullptr};
    GL::Buffer* m_vao {nullptr};
    bool m_textCoord {false};
    Assets::Material* m_material {nullptr};

};

std::ostream& operator<<(std::ostream&, const Mesh&) noexcept;

inline const std::string& Mesh::getName() const noexcept
{
    return m_name;
}

inline GLuint Mesh::getVertexLocation() const noexcept
{
    return S_VERTEXLOCATION;
}

inline GLuint Mesh::getTextureCoordLocation() const noexcept
{
    return m_textCoord;
}

inline GLuint Mesh::getNormalLocation() const noexcept
{
    return S_NORMALLOCATION;
}

inline Assets::Material* Mesh::getMaterial() const noexcept
{
    return m_material;
}

inline bool Mesh::hasTextureCoord() const noexcept
{
    return m_textCoord;
}

inline void Mesh::draw() const noexcept
{
    glDrawElements(GL_TRIANGLES, m_dataSize, GL_UNSIGNED_INT, static_cast< void* >(nullptr));
}

}
