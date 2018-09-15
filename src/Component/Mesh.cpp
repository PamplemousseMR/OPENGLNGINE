#include "Component/Mesh.hpp"
#include "GL/Buffer.hpp"
#include "Assets/Material.hpp"

using namespace std;
using namespace glm;
using namespace GL;

namespace Component
{
    const GLuint Mesh::S_VERTEXLOCATION = 0;
    const GLuint Mesh::S_TEXTCOORDLOCATION = 1;
    const GLuint Mesh::S_NORMALLOCATION = 2;

    Mesh::Mesh(const string& _name) noexcept :
        Component(_name)
    {
        m_vboVertex = new Buffer(Buffer::VBO);
        m_vboNormal = new Buffer(Buffer::VBO);
        m_vboTextCoord = new Buffer(Buffer::VBO);
        m_ebo = new Buffer(Buffer::EBO);
        m_vao = new Buffer(Buffer::VAO);
        m_material = new Assets::Material(_name);
    }

    Mesh::~Mesh() noexcept
    {
        delete m_vao;
        delete m_ebo;
        delete m_vboVertex;
        delete m_vboNormal;
        delete m_vboTextCoord;
        delete m_material;
    }

    bool Mesh::getSimilarVertexIndex(const PackedVertex& _packed, const map<PackedVertex, unsigned int>& _vertexToOutIndex, unsigned int& _result) const noexcept
    {
        std::map<PackedVertex, unsigned int>::const_iterator it = _vertexToOutIndex.find(_packed);
        if (it == _vertexToOutIndex.end())
        {
            return false;
        }
        else
        {
            _result = it->second;
            return true;
        }
    }

    void Mesh::indexVBO(const vector<vec3>& _in_vertices, const vector<vec2>& _in_uvs, const vector<vec3>& _in_normals, vector<unsigned int>& _out_indices, vector<vec3>& _out_vertices, vector<vec2>& _out_uvs, vector<vec3>& _out_normals) const noexcept
    {
        map<PackedVertex, unsigned int> vertexToOutIndex;

        for (unsigned int i = 0; i<_in_vertices.size(); ++i)
        {
            PackedVertex packed = { _in_vertices[i], _in_uvs[i], _in_normals[i] };

            unsigned int index;
            bool found = getSimilarVertexIndex(packed, vertexToOutIndex, index);

            if (found)
            {
                _out_indices.push_back(index);
            }
            else
            {
                _out_vertices.push_back(_in_vertices[i]);
                _out_uvs.push_back(_in_uvs[i]);
                _out_normals.push_back(_in_normals[i]);
                unsigned int newindex = static_cast< unsigned int >(_out_vertices.size() - 1);
                _out_indices.push_back(newindex);
                vertexToOutIndex[packed] = newindex;
            }
        }
    }

    void Mesh::loadMesh(const vector<vec3>& _vertex, const vector<vec3>& _normal, const vector<vec2>& _textCoord, const vector<vec3>& _index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : _index)
        {
            int pos = int(elem[0]);

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = int(_vertex.size()) + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= int(_vertex.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = _vertex[size_t(pos)];
            int coord = int(elem[1]);

            if (coord == 0)
            {
                throw invalid_argument("[Mesh] value of texture coord can't be 0");
            }
            else if (coord < 0)
            {
                coord = int(_textCoord.size()) + coord;
            }
            else
            {
                coord -= 1;
            }

            if (coord >= int(_textCoord.size()))
            {
                throw invalid_argument("[Mesh ] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec2 coordo = _textCoord[size_t(coord)];

            int norm = int(elem[2]);

            if (norm == 0)
            {
                throw invalid_argument("[Mesh] value of normal can't be 0");
            }
            else if (norm < 0)
            {
                norm = int(_normal.size()) + norm;
            }
            else
            {
                norm -= 1;
            }

            if (norm >= int(_normal.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec3 norma = _normal[size_t(norm)];

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
        m_dataSize = int(indexedIndex.size());

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
            m_vboVertex->setLocation(S_VERTEXLOCATION);
            m_vboVertex->setAttrib(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_vboTextCoord->bind();
            m_vboTextCoord->setLocation(S_TEXTCOORDLOCATION);
            m_vboTextCoord->setAttrib(S_TEXTCOORDLOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

            m_vboNormal->bind();
            m_vboNormal->setLocation(S_NORMALLOCATION);
            m_vboNormal->setAttrib(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_ebo->bind();
        }
        m_vao->unbind();

    }

    void Mesh::loadMesh(const vector<vec3>& _vertex, const vector<vec3>& _index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : _index)
        {
            int pos = int(elem[0]);

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = int(_vertex.size()) + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= int(_vertex.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = _vertex[size_t(pos)];

            newVertex.push_back(posi);
            newTextCoord.push_back(vec2(0, 0));
        }

        //compute normals
        for (size_t i = 0; i < newVertex.size(); i += 3)
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
        //end

        vector<vec3> indexedVertex;
        vector<vec2> indexedTextCoord;
        vector<vec3> indexedNormal;
        vector<unsigned int> indexedIndex;

        indexVBO(newVertex, newTextCoord, newNormal, indexedIndex, indexedVertex, indexedTextCoord, indexedNormal);

        m_normal = true;
        m_textCoord = false;
        m_dataSize = int(indexedIndex.size());

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
            m_vboVertex->setLocation(S_VERTEXLOCATION);
            m_vboVertex->setAttrib(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_vboNormal->bind();
            m_vboNormal->setLocation(S_NORMALLOCATION);
            m_vboNormal->setAttrib(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_ebo->bind();
        }
        m_vao->unbind();

    }

    void Mesh::loadMesh(const vector<vec3>& _vertex, const vector<vec2>& _textCoord, const vector<vec3>& _index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : _index)
        {
            int pos = int(elem[0]);

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = int(_vertex.size()) + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= int(_vertex.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = _vertex[size_t(pos)];

            int coord = int(elem[1]);

            if (coord == 0)
            {
                throw invalid_argument("[Mesh] value of texture coord can't be 0");
            }
            else if (coord < 0)
            {
                coord = int(_textCoord.size()) + coord;
            }
            else
            {
                coord -= 1;
            }

            if (coord >= int(_textCoord.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec2 coordo = _textCoord[size_t(coord)];

            newVertex.push_back(posi);
            newTextCoord.push_back(coordo);
        }

        for (size_t i = 0; i < newVertex.size(); i += 3)
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

        vector<vec3> indexedVertex;
        vector<vec2> indexedTextCoord;
        vector<vec3> indexedNormal;
        vector<unsigned int> indexedIndex;

        indexVBO(newVertex, newTextCoord, newNormal, indexedIndex, indexedVertex, indexedTextCoord, indexedNormal);

        m_normal = true;
        m_textCoord = true;
        m_dataSize = int(indexedIndex.size());

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
            m_vboVertex->setLocation(S_VERTEXLOCATION);
            m_vboVertex->setAttrib(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_vboTextCoord->bind();
            m_vboTextCoord->setLocation(S_TEXTCOORDLOCATION);
            m_vboTextCoord->setAttrib(S_TEXTCOORDLOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

            m_vboNormal->bind();
            m_vboNormal->setLocation(S_NORMALLOCATION);
            m_vboNormal->setAttrib(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_ebo->bind();
        }
        m_vao->unbind();
    }

    void Mesh::loadMesh(const vector<vec3>& _vertex, const vector<vec3>& _normal, const std::vector<vec3>& _index)
    {
        vector<vec3> newVertex;
        vector<vec2> newTextCoord;
        vector<vec3> newNormal;

        for (vec3 elem : _index)
        {
            int pos = int(elem[0]);

            if (pos == 0)
            {
                throw invalid_argument("[Mesh] value of vertex can't be 0");
            }
            else if (pos < 0)
            {
                pos = int(_vertex.size()) + pos;
            }
            else
            {
                pos -= 1;
            }

            if (pos >= int(_vertex.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for vertex doesn't exist");
            }

            vec3 posi = _vertex[size_t(pos)];

            int norm = int(elem[2]);

            if (norm == 0)
            {
                throw invalid_argument("[Mesh] value of normal can't be 0");
            }
            else if (norm < 0)
            {
                norm = int(_normal.size()) + norm;
            }
            else
            {
                norm -= 1;
            }

            if (norm >= int(_normal.size()))
            {
                throw invalid_argument("[Mesh] value " + to_string(elem[0]) + " for texture coord doesn't exist");
            }

            vec3 norma = _normal[size_t(norm)];

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
        m_dataSize = int(indexedIndex.size());

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
            m_vboVertex->setLocation(S_VERTEXLOCATION);
            m_vboVertex->setAttrib(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_vboNormal->bind();
            m_vboNormal->setLocation(S_NORMALLOCATION);
            m_vboNormal->setAttrib(S_NORMALLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            m_ebo->bind();
        }
        m_vao->unbind();
    }

    void Mesh::bind() const noexcept
    {
        m_vao->bind();
    }

    void Mesh::unbind() const noexcept
    {
        m_vao->unbind();
    }

    ostream& Mesh::print(ostream& _o) const noexcept
    {
        _o << "[Mesh " << m_name << "]\n";
        _o << "\tnormal : " << m_normal << "\n";
        _o << "\ttextCoord : " << m_textCoord << "\n";
        return _o;
    }

    ostream& operator<<(ostream& _o, const Mesh& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
