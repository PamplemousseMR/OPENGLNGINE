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

    Mesh(const std::string&);
    ~Mesh();

    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&) throw();
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&) throw();
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&) throw();
    void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec3>&) throw();
    void bind() const;
    void unbind() const;
    void draw() const;

    GL::Buffer* getArrayBuffer() const;
    const std::string& getName() const;
    int getVertexLocation() const;
    int getTextureCoordLocation() const;
    int getNormalLocation() const;
    bool hasTextureCoord() const;
    bool hasNormal() const;

    std::ostream& print(std::ostream&) const;

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

    struct PackedVertex
    {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        bool operator<(const PackedVertex that) const
        {
            return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
        }
    };

    bool getSimilarVertexIndex(const PackedVertex&, const std::map<PackedVertex, unsigned int>&, unsigned int&);
    void indexVBO(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&, std::vector<unsigned int>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);


};

std::ostream& operator<<(std::ostream&, const Mesh&);

}
