#pragma once

#include "OpenGLNgine/GL/VertexArrayBuffer.hpp"
#include "OpenGLNgine/Hardware/VertexElement.hpp"

#include <list>

namespace Hardware
{

class VertexData;

class VertexDeclaration final
{

    friend VertexData;

public:

    typedef std::list< VertexElement* > VertexElementList;

    VertexDeclaration(const VertexDeclaration&) = delete;

    VertexDeclaration(VertexDeclaration&&) = delete;

    VertexDeclaration& operator=(const VertexDeclaration&) = delete;

    VertexDeclaration& operator=(VertexDeclaration&&) = delete;

    inline void lock();

    inline void unlock();

    const VertexElement* addElement(unsigned short _source, int _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic);

    void removeAllElements();

    const VertexElement* findElementBySemantic(VERTEXELEMENT_SEMANTIC _semantic) const;

    inline const VertexElementList& getElements() const;

private:

    VertexDeclaration();

    ~VertexDeclaration();

    VertexElementList m_elements {};

    ::GL::VertexArrayBuffer m_vertexArrayBuffer {};

};

inline void VertexDeclaration::lock()
{
    m_vertexArrayBuffer.bind();
}

inline void VertexDeclaration::unlock()
{
    m_vertexArrayBuffer.unbind();
}

inline const VertexDeclaration::VertexElementList& VertexDeclaration::getElements() const
{
    return m_elements;
}

}
