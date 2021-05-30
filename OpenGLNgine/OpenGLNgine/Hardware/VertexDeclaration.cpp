#include "OpenGLNgine/Hardware/VertexDeclaration.hpp"

namespace Hardware
{

const VertexElement* VertexDeclaration::addElement(unsigned short _source, int _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic)
{
    VertexElementList::const_iterator it, itEnd;
    itEnd = m_elements.end();
    for(it=m_elements.begin() ; it!=itEnd ; ++it)
    {
        if((*it)->m_semantic == _semantic)
        {
            delete *it;
            m_elements.erase(it);
            break;
        }
    }

    m_elements.push_back(new VertexElement(_source, _offsetInBytes, _type, _semantic));
    return m_elements.back();
}

void VertexDeclaration::removeAllElements()
{
    VertexElementList::const_iterator it, itEnd;
    itEnd = m_elements.end();
    for(it=m_elements.begin() ; it!=itEnd ; ++it)
    {
        delete *it;
    }
    m_elements.clear();
}

const VertexElement* VertexDeclaration::findElementBySemantic(VERTEXELEMENT_SEMANTIC _semantic) const
{
    VertexElementList::const_iterator it, itEnd;
    itEnd = m_elements.end();
    for(it=m_elements.begin() ; it!=itEnd ; ++it)
    {
        if((*it)->m_semantic == _semantic)
        {
            return *it;
        }
    }
    return nullptr;
}

VertexDeclaration::VertexDeclaration()
{
}

VertexDeclaration::~VertexDeclaration()
{
    this->removeAllElements();
}

}
