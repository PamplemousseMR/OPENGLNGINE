#pragma once

#include "Drawable.hpp"

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
    class VertexBuffer;
    class VertexArrayBuffer;
    class ElementsBuffer;
}

namespace Component
{

class Mesh : public Drawable
{

public:

    Mesh(const std::string&);
    ~Mesh();
    Mesh(const Mesh&);
    Mesh(Mesh&&);
    Mesh& operator=(const Mesh&);
    Mesh& operator=(Mesh&&);

    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&);
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
    void bind() const;
    void unbind() const;
    inline void draw() const;

    inline Assets::Material* getMaterial() const;
    inline bool hasTextureCoord() const;

    std::ostream& print(std::ostream&) const;

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

    bool getSimilarVertexIndex(const PackedVertex&, const std::map<PackedVertex, unsigned int>&, unsigned int&) const;
    void indexVBO(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&, std::vector<unsigned int>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&) const;

private:

    int m_dataSize {0};
    GL::VertexBuffer* m_vboVertex {nullptr};
    GL::VertexBuffer* m_vboNormal {nullptr};
    GL::VertexBuffer* m_vboTextCoord {nullptr};
    GL::ElementsBuffer* m_ebo {nullptr};
    GL::VertexArrayBuffer* m_vao {nullptr};
    bool m_textCoord {false};
    Assets::Material* m_material {nullptr};

};

std::ostream& operator<<(std::ostream&, const Mesh&);

inline Assets::Material* Mesh::getMaterial() const
{
    return m_material;
}

inline bool Mesh::hasTextureCoord() const
{
    return m_textCoord;
}

inline void Mesh::draw() const
{
    glDrawElements(GL_TRIANGLES, m_dataSize, GL_UNSIGNED_INT, static_cast< void* >(nullptr));
    assert(glGetError() == GL_NO_ERROR);
}

}
