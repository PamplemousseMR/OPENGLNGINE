#pragma once

#include "Component.hpp"

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
class Mesh : public Component
{

public:

    static const GLuint S_VERTEXLOCATION;
    static const GLuint S_TEXTCOORDLOCATION;
    static const GLuint S_NORMALLOCATION;

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

    int m_dataSize {0};
    GL::Buffer* m_vboVertex {nullptr};
    GL::Buffer* m_vboNormal {nullptr};
    GL::Buffer* m_vboTextCoord {nullptr};
    GL::Buffer* m_ebo {nullptr};
    GL::Buffer* m_vao {nullptr};
    std::string m_name {};
    bool m_normal {false};
    bool m_textCoord {false};

};

std::ostream& operator<<(std::ostream&, const Mesh&) noexcept;

}
