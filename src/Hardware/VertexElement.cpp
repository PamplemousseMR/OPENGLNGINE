#include "Hardware/VertexElement.hpp"

using namespace std;

namespace Hardware
{

unsigned short VertexElement::getTypeCount(VERTEXELEMENT_TYPE _type)
{
    switch(_type)
    {
    case VET_FLOAT2:
        return 2;
    case VET_FLOAT3:
        return 3;
    }
    return 0;
}

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
