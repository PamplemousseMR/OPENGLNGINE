#include "Component/Mesh.hpp"
#include "GL/Buffer.hpp"

#define BUFFER_OFFSET(i) ((GLfloat *)nullptr + (i))

using namespace std;
using namespace glm;
using namespace GL;

namespace Component
{
    const int Mesh::S_VERTEXLOCATION = 0;
    const int Mesh::S_TEXTCOORDLOCATION = 1;
    const int Mesh::S_NORMALLOCATION = 2;

    Mesh::Mesh(const string& name) noexcept :
        m_name(name),
        m_normal(false),
        m_textCoord(false),
        m_dataSize(0)
    {
        m_vboVertex = new Buffer(BUFFER_TYPE::VBO);
        m_vboNormal = new Buffer(BUFFER_TYPE::VBO);
        m_vboTextCoord = new Buffer(BUFFER_TYPE::VBO);
        m_ebo = new Buffer(BUFFER_TYPE::EBO);
        m_vao = new Buffer(BUFFER_TYPE::VAO);
    }

    Mesh::~Mesh() noexcept
    {
        delete m_vao;
        delete m_ebo;
        delete m_vboVertex;
        delete m_vboNormal;
        delete m_vboTextCoord;
    }

    bool Mesh::getSimilarVertexIndex(const PackedVertex& packed, const map<PackedVertex, unsigned int>& VertexToOutIndex, unsigned int& result) const noexcept
    {
        std::map<PackedVertex, unsigned int>::const_iterator it = VertexToOutIndex.find(packed);
        if (it == VertexToOutIndex.end())
        {
            return false;
        }
        else
        {
            result = it->second;
            return true;
        }
    }

    void Mesh::indexVBO(const vector<vec3>& in_vertices, const vector<vec2>& in_uvs, const vector<vec3>& in_normals, vector<unsigned int>& out_indices, vector<vec3>& out_vertices, vector<vec2>& out_uvs, vector<vec3>& out_normals) const noexcept
    {
        map<PackedVertex, unsigned int> VertexToOutIndex;

        for (unsigned int i = 0; i<in_vertices.size(); i++)
        {
            PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

            unsigned int index;
            bool found = getSimilarVertexIndex(packed, VertexToOutIndex, index);

            if (found)
            {
                out_indices.push_back(index);
            }
            else
            {
                out_vertices.push_back(in_vertices[i]);
                out_uvs.push_back(in_uvs[i]);
                out_normals.push_back(in_normals[i]);
                unsigned int newindex = (unsigned int)out_vertices.size() - 1;
                out_indices.push_back(newindex);
                VertexToOutIndex[packed] = newindex;
            }
        }
    }

    void Mesh::loadMesh(const vector<vec3>& vertex, const vector<vec3>& normal, const vector<vec2>& textCoord, const vector<vec3>& index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : index)
        {
            int pos = (int)elem[0];

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = (int)vertex.size() + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= vertex.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = vertex[pos];
            int coord = (int)elem[1];

            if (coord == 0)
            {
                throw invalid_argument("[Mesh] value of texture coord can't be 0");
            }
            else if (coord < 0)
            {
                coord = (int)textCoord.size() + coord;
            }
            else
            {
                coord -= 1;
            }

            if (coord >= (int)textCoord.size())
            {
                throw invalid_argument("[Mesh ] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec2 coordo = textCoord[coord];

            int norm = (int)elem[2];

            if (norm == 0)
            {
                throw invalid_argument("[Mesh] value of normal can't be 0");
            }
            else if (norm < 0)
            {
                norm = (int)normal.size() + norm;
            }
            else
            {
                norm -= 1;
            }

            if (norm >= (int)normal.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec3 norma = normal[norm];

            newVertex.push_back(posi);
            newTextCoord.push_back(coordo);
            newNormal.push_back(norma);
        }

        vector<vec3> indexedVertex;
        vector<vec2> indexedTextCoord;
        vector<vec3> indexedNormal;
        vector<unsigned int> indexedIndex;

        indexVBO(newVertex, newTextCoord, newNormal, indexedIndex, indexedVertex, indexedTextCoord, indexedNormal);

        m_normal = true;
        m_textCoord = true;
        m_dataSize = (int)indexedIndex.size();

        m_vboVertex->bind();
        m_vboVertex->setData(indexedVertex);
        m_vboVertex->unbind();

        m_vboNormal->bind();
        m_vboNormal->setData(indexedNormal);
        m_vboNormal->unbind();

        m_vboTextCoord->bind();
        m_vboTextCoord->setData(indexedTextCoord);
        m_vboTextCoord->unbind();

        m_ebo->bind();
        m_ebo->setData(indexedIndex);
        m_ebo->unbind();

        m_vao->bind();
        {
            m_vboVertex->bind();
            glEnableVertexAttribArray(S_VERTEXLOCATION);
            glVertexAttribPointer(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_vboTextCoord->bind();
            glEnableVertexAttribArray(S_TEXTCOORDLOCATION);
            glVertexAttribPointer(S_TEXTCOORDLOCATION, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_vboNormal->bind();
            glEnableVertexAttribArray(S_NORMALLOCATION);
            glVertexAttribPointer(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_ebo->bind();
        }
        m_vao->unbind();

    }

    void Mesh::loadMesh(const vector<vec3>& vertex, const vector<vec3>& index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : index)
        {
            int pos = (int)elem[0];

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = (int)vertex.size() + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= vertex.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = vertex[pos];

            newVertex.push_back(posi);
            newTextCoord.push_back(vec2(0, 0));
        }

        //calcules des normales
        for (int i = 0; i < newVertex.size(); i += 3)
        {
            vec3 A = newVertex[i];
            vec3 B = newVertex[i + 1];
            vec3 C = newVertex[i + 2];

            vec3 AB = B - A;
            vec3 AC = C - A;

            vec3 normal = normalize(cross(AB, AC));

            newNormal.push_back(normal);
            newNormal.push_back(normal);
            newNormal.push_back(normal);
        }
        // fin des calcules

        vector<vec3> indexedVertex;
        vector<vec2> indexedTextCoord;
        vector<vec3> indexedNormal;
        vector<unsigned int> indexedIndex;

        indexVBO(newVertex, newTextCoord, newNormal, indexedIndex, indexedVertex, indexedTextCoord, indexedNormal);

        m_normal = true;
        m_textCoord = false;
        m_dataSize = (int)indexedIndex.size();

        m_vboVertex->bind();
        m_vboVertex->setData(indexedVertex);
        m_vboVertex->unbind();

        m_vboNormal->bind();
        m_vboNormal->setData(indexedNormal);
        m_vboNormal->unbind();

        m_ebo->bind();
        m_ebo->setData(indexedIndex);
        m_ebo->unbind();

        m_vao->bind();
        {
            m_vboVertex->bind();
            glEnableVertexAttribArray(S_VERTEXLOCATION);
            glVertexAttribPointer(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_vboNormal->bind();
            glEnableVertexAttribArray(S_NORMALLOCATION);
            glVertexAttribPointer(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_ebo->bind();
        }
        m_vao->unbind();

    }

    void Mesh::loadMesh(const vector<vec3>& vertex, const vector<vec2>& textCoord, const vector<vec3>& index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : index)
        {
            int pos = (int)elem[0];

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = (int)vertex.size() + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= vertex.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = vertex[pos];

            int coord = (int)elem[1];

            if (coord == 0)
            {
                throw invalid_argument("[Mesh] value of texture coord can't be 0");
            }
            else if (coord < 0)
            {
                coord = (int)textCoord.size() + coord;
            }
            else
            {
                coord -= 1;
            }

            if (coord >= (int)textCoord.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec2 coordo = textCoord[coord];

            newVertex.push_back(posi);
            newTextCoord.push_back(coordo);
        }

        //calcules des normales
        for (int i = 0; i < newVertex.size(); i += 3)
        {
            vec3 A = newVertex[i];
            vec3 B = newVertex[i + 1];
            vec3 C = newVertex[i + 2];

            vec3 AB = B - A;
            vec3 AC = C - A;

            vec3 normal = normalize(cross(AB, AC));

            newNormal.push_back(normal);
            newNormal.push_back(normal);
            newNormal.push_back(normal);
        }
        // fin des calcules

        vector<vec3> indexedVertex;
        vector<vec2> indexedTextCoord;
        vector<vec3> indexedNormal;
        vector<unsigned int> indexedIndex;

        indexVBO(newVertex, newTextCoord, newNormal, indexedIndex, indexedVertex, indexedTextCoord, indexedNormal);

        m_normal = true;
        m_textCoord = true;
        m_dataSize = (int)indexedIndex.size();

        m_vboVertex->bind();
        m_vboVertex->setData(indexedVertex);
        m_vboVertex->unbind();

        m_vboNormal->bind();
        m_vboNormal->setData(indexedNormal);
        m_vboNormal->unbind();

        m_vboTextCoord->bind();
        m_vboTextCoord->setData(indexedTextCoord);
        m_vboTextCoord->unbind();

        m_ebo->bind();
        m_ebo->setData(indexedIndex);
        m_ebo->unbind();

        m_vao->bind();
        {
            m_vboVertex->bind();
            glEnableVertexAttribArray(S_VERTEXLOCATION);
            glVertexAttribPointer(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_vboTextCoord->bind();
            glEnableVertexAttribArray(S_TEXTCOORDLOCATION);
            glVertexAttribPointer(S_TEXTCOORDLOCATION, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_vboNormal->bind();
            glEnableVertexAttribArray(S_NORMALLOCATION);
            glVertexAttribPointer(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_ebo->bind();
        }
        m_vao->unbind();
    }

    void Mesh::loadMesh(const vector<vec3>& vertex, const vector<vec3>& normal, const std::vector<vec3>& index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : index)
        {
            int pos = (int)elem[0];

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = (int)vertex.size() + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= vertex.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = vertex[pos];

            int norm = (int)elem[2];

            if (norm == 0)
            {
                throw invalid_argument("[Mesh] value of normal can't be 0");
            }
            else if (norm < 0)
            {
                norm = (int)normal.size() + norm;
            }
            else
            {
                norm -= 1;
            }

            if (norm >= (int)normal.size())
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec3 norma = normal[norm];

            newVertex.push_back(posi);
            newTextCoord.push_back(vec2(0,0));
            newNormal.push_back(norma);
        }

        vector<vec3> indexedVertex;
        vector<vec2> indexedTextCoord;
        vector<vec3> indexedNormal;
        vector<unsigned int> indexedIndex;

        indexVBO(newVertex, newTextCoord, newNormal, indexedIndex, indexedVertex, indexedTextCoord, indexedNormal);

        m_normal = true;
        m_textCoord = false;
        m_dataSize = (int)indexedIndex.size();

        m_vboVertex->bind();
        m_vboVertex->setData(indexedVertex);
        m_vboVertex->unbind();

        m_vboNormal->bind();
        m_vboNormal->setData(indexedNormal);
        m_vboNormal->unbind();

        m_ebo->bind();
        m_ebo->setData(indexedIndex);
        m_ebo->unbind();

        m_vao->bind();
        {
            m_vboVertex->bind();
            glEnableVertexAttribArray(S_VERTEXLOCATION);
            glVertexAttribPointer(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_vboNormal->bind();
            glEnableVertexAttribArray(S_NORMALLOCATION);
            glVertexAttribPointer(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

            m_ebo->bind();
        }
        m_vao->unbind();
    }

    const string& Mesh::getName() const noexcept
    {
        return m_name;
    }

    int Mesh::getVertexLocation() const noexcept
    {
        return S_VERTEXLOCATION;
    }

    int Mesh::getTextureCoordLocation() const noexcept
    {
        return m_textCoord;
    }

    int Mesh::getNormalLocation() const noexcept
    {
        return S_NORMALLOCATION;
    }

    bool Mesh::hasTextureCoord() const noexcept
    {
        return m_textCoord;
    }

    bool Mesh::hasNormal() const noexcept
    {
        return m_normal;
    }

    ostream& Mesh::print(ostream& o) const noexcept
    {
        o << "[Mesh " << m_name << "]\n";
        o << "\tnormal : " << m_normal << "\n";
        o << "\ttextCoord : " << m_textCoord << "\n";
        return o;
    }

    void Mesh::bind() const noexcept
    {
        m_vao->bind();
    }

    void Mesh::unbind() const noexcept
    {
        m_vao->unbind();
    }

    void Mesh::draw() const noexcept
    {
        glDrawElements(GL_TRIANGLES, m_dataSize, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    }

    ostream& operator<<(ostream& o, const Mesh& m) noexcept
    {
        m.print(o);
        return o;
    }
}
