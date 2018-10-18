#include "Component/Quad.hpp"
#include "GL/VertexBuffer.hpp"
#include "GL/VertexArrayBuffer.hpp"

using namespace std;
using namespace GL;

namespace Component
{

    Quad::Quad(const string& _name) :
        Drawable(_name)
    {
        m_vboVertex = new VertexBuffer();
        m_vao = new VertexArrayBuffer();

        m_vboVertex->bind();
        m_vboVertex->setData(s_VERTICES);
        m_vboVertex->unbind();

        m_vao->bind();
        {
            m_vboVertex->bind();
            m_vboVertex->setLocation(S_VERTEXLOCATION);
            m_vboVertex->setAttrib(S_VERTEXLOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }
        m_vao->unbind();
    }

    Quad::~Quad() noexcept
    {
        delete m_vao;
        delete m_vboVertex;
    }

    Quad::Quad(const Quad& _quad) :
        Drawable(_quad),
        m_vboVertex(new VertexBuffer(*_quad.m_vboVertex)),
        m_vao(new VertexArrayBuffer())
    {
        m_vao->bind();
        m_vboVertex->bind();
        m_vboVertex->setLocation(0);
        m_vboVertex->setAttrib(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        m_vao->unbind();
    }

    Quad::Quad(Quad&& _quad) :
        Drawable(std::move(_quad))
    {
        m_vboVertex = _quad.m_vboVertex;
        _quad.m_vboVertex = nullptr;
        m_vao = _quad.m_vao;
        _quad.m_vao = nullptr;
    }

    Quad& Quad::operator=(const Quad& _quad)
    {
        if(this != &_quad)
        {
            delete m_vao;
            delete m_vboVertex;

            Component::operator=(_quad);
            m_vboVertex = new VertexBuffer(*_quad.m_vboVertex);
            m_vao = new VertexArrayBuffer();

            m_vao->bind();
            m_vboVertex->bind();
            m_vboVertex->setLocation(0);
            m_vboVertex->setAttrib(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            m_vao->unbind();
        }
        return *this;
    }

    Quad& Quad::operator=(Quad&& _quad)
    {
        if(this != &_quad)
        {
            delete m_vao;
            delete m_vboVertex;

            Component::operator=(std::move(_quad));

            m_vboVertex = _quad.m_vboVertex;
            _quad.m_vboVertex = nullptr;
            m_vao = _quad.m_vao;
            _quad.m_vao = nullptr;
        }
        return *this;
    }

    void Quad::bind() const noexcept
    {
        m_vao->bind();
    }

    void Quad::unbind() const noexcept
    {
        m_vao->unbind();
    }

    ostream& Quad::print(ostream& _o) const noexcept
    {
        _o << "[Quad " << m_name << "]\n";
        return _o;
    }

    ostream& operator<<(ostream& _o, const Quad& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
