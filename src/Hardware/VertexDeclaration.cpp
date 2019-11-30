#include "Hardware/VertexDeclaration.hpp"

#include <stdexcept>

using namespace std;

namespace Hardware
{

VertexDeclaration::VertexDeclaration()
{
}

VertexDeclaration::~VertexDeclaration()
{
    m_elements.clear();
}

const VertexElement* VertexDeclaration::getElement(unsigned short _index) const
{
    if(_index >= m_elements.size())
    {
        throw invalid_argument("[VertexDeclaration] A vertex element with this index doesn't exist");
    }

    VertexElementList::const_iterator it = m_elements.begin();
    for(unsigned short n = 0; n < _index; ++n)
    {
        ++it;
    }

    return &(*it);
}

const VertexElement& VertexDeclaration::addElement(unsigned short _source, size_t _offsetInBytes, VertexElement::VERTEXELEMENT_TYPE _type, VertexElement::VERTEXELEMENT_SEMANTIC _semantic)
{
    m_elements.push_back(VertexElement(_source, _offsetInBytes, _type, _semantic));
    return m_elements.back();
}

const VertexElement& VertexDeclaration::insertElement(unsigned short _position, unsigned short _source, size_t _offsetInBytes, VertexElement::VERTEXELEMENT_TYPE _type, VertexElement::VERTEXELEMENT_SEMANTIC _semantic)
{
    if(_position >= m_elements.size())
    {
        return this->addElement(_source, _offsetInBytes, _type, _semantic);
    }

    VertexElementList::iterator it = m_elements.begin();
    for (unsigned short n = 0; n < _position; ++n)
    {
        ++it;
    }

    it = m_elements.insert(it, VertexElement(_source, _offsetInBytes, _type, _semantic));

    return *it;
}

void VertexDeclaration::removeElement(unsigned short _index)
{
    if(_index >= m_elements.size())
    {
        throw invalid_argument("[VertexDeclaration] A vertex element with this index doesn't exist");
    }

    VertexElementList::iterator it = m_elements.begin();
    for (unsigned short n = 0; n < _index; ++n)
    {
        ++it;
    }

    m_elements.erase(it);
}

void VertexDeclaration::removeElement(VertexElement::VERTEXELEMENT_SEMANTIC _semantic)
{
    VertexElementList::const_iterator itBeg, itEnd;
    itEnd = m_elements.end();
    for(itBeg=m_elements.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        if (itBeg->getSemantic() == _semantic)
        {
            m_elements.erase(itBeg);
            break;
        }
    }
}

const VertexElement* VertexDeclaration::findElementBySemantic(VertexElement::VERTEXELEMENT_SEMANTIC _semantic) const
{
    VertexElementList::const_iterator itBeg, itEnd;
    itEnd = m_elements.end();
    for(itBeg=m_elements.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        if (itBeg->getSemantic() == _semantic)
        {
            return &(*itBeg);
        }
    }
    return nullptr;
}

}
