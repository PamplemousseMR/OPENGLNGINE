#include "OpenGLNgine/Hardware/VertexDeclaration.hpp"

namespace Hardware
{

const VertexElement& VertexDeclaration::addElement(unsigned short _source, int _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic)
{
    m_elements.push_back(VertexElement(_source, _offsetInBytes, _type, _semantic));
    return m_elements.back();
}

const VertexElement* VertexDeclaration::findElementBySemantic(VERTEXELEMENT_SEMANTIC _semantic) const
{
    VertexElementList::const_iterator itBeg, itEnd;
    itEnd = m_elements.end();
    for(itBeg=m_elements.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        if(itBeg->m_semantic == _semantic)
        {
            return &(*itBeg);
        }
    }
    return nullptr;
}

VertexDeclaration::VertexDeclaration()
{
}

VertexDeclaration::~VertexDeclaration()
{
    m_elements.clear();
}

}
