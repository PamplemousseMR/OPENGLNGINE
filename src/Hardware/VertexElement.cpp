#include "Hardware/VertexElement.hpp"

using namespace std;

namespace Hardware
{

VertexElement::VertexElement(unsigned short _source, size_t _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic):
    m_source(_source),
    m_offsetInBytes(_offsetInBytes),
    m_type(_type),
    m_semantic(_semantic)
{
}

VertexElement::~VertexElement()
{
}

}
