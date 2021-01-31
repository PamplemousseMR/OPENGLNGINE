#pragma once

#include "OpenGLNgine/GL/VertexArrayBuffer.hpp"
#include "OpenGLNgine/Hardware/VertexElement.hpp"

#include <list>

namespace Hardware
{

class HardwareBufferManager;

class VertexDeclaration final
{

    friend HardwareBufferManager;

public:

    typedef std::list<VertexElement> VertexElementList;

    inline void lock();

    inline void unlock();

    const VertexElement& addElement(unsigned short _source, int _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic, unsigned short _index = 0);

    inline void removeAllElements();

    const VertexElement* findElementBySemantic(VERTEXELEMENT_SEMANTIC _semantic) const;

    inline const VertexElementList& getElements() const;

private:

    VertexDeclaration();

    ~VertexDeclaration();

    VertexElementList m_elements {};

    GL::VertexArrayBuffer m_vertexArrayBuffer {};

};

inline void VertexDeclaration::lock()
{
    m_vertexArrayBuffer.bind();
}

inline void VertexDeclaration::unlock()
{
    m_vertexArrayBuffer.unbind();
}

inline void VertexDeclaration::removeAllElements()
{
    m_elements.clear();
}

inline const VertexDeclaration::VertexElementList& VertexDeclaration::getElements() const
{
    return m_elements;
}

}
