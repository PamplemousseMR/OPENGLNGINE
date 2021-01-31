#include "OpenGLNgine/Hardware/VertexElement.hpp"

namespace Hardware
{

int VertexElement::getTypeCount(VERTEXELEMENT_TYPE _type)
{
    switch(_type)
    {
    case VET_FLOAT2:
        return 2;
    case VET_FLOAT3:
        return 3;
    case VET_FLOAT4:
        return 4;
    default:
        GLNGINE_EXCEPTION("Unhandle vertex element type");
    }
}

GL::DATABUFFER_TYPE VertexElement::getType(VERTEXELEMENT_TYPE _type)
{
    switch(_type)
    {
    case VET_FLOAT2:
    case VET_FLOAT3:
    case VET_FLOAT4:
        return GL::DATABUFFER_TYPE::DT_FLOAT;
    default:
        GLNGINE_EXCEPTION("Unhandle vertex element type");
    }
}

VertexElement::VertexElement(unsigned short _source, int _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic, unsigned short _index):
    m_source(_source),
    m_offsetInBytes(_offsetInBytes),
    m_type(_type),
    m_semantic(_semantic),
    m_index(_index)
{
}

VertexElement::~VertexElement()
{
}

}
