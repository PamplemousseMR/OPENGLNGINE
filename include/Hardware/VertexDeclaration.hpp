#pragma once

#include "Hardware/VertexElement.hpp"

#include <list>

namespace Hardware
{

class VertexDeclaration
{

public:

    typedef std::list<VertexElement> VertexElementList;

    VertexDeclaration();
    ~VertexDeclaration();

    inline size_t getElementCount() const;
    inline const VertexElementList& getElements() const;
    const VertexElement* getElement(unsigned short) const;

    const VertexElement& addElement(unsigned short, size_t, VertexElement::VERTEXELEMENT_TYPE, VertexElement::VERTEXELEMENT_SEMANTIC);
    const VertexElement& insertElement(unsigned short, unsigned short, size_t, VertexElement::VERTEXELEMENT_TYPE, VertexElement::VERTEXELEMENT_SEMANTIC);

    void removeElement(unsigned short);
    void removeElement(VertexElement::VERTEXELEMENT_SEMANTIC);
    inline void removeAllElements();

    const VertexElement* findElementBySemantic(VertexElement::VERTEXELEMENT_SEMANTIC) const;

private:

    VertexElementList m_elements;

};

size_t VertexDeclaration::getElementCount() const
{
    return m_elements.size();
}

const VertexDeclaration::VertexElementList& VertexDeclaration::getElements() const
{
    return m_elements;
}

void VertexDeclaration::removeAllElements()
{
    m_elements.clear();
}

}
