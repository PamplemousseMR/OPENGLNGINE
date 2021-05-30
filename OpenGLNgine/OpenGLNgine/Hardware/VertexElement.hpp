#pragma once

#include "OpenGLNgine/GL/DataBuffer.hpp"

namespace Hardware
{

class VertexDeclaration;

enum VERTEXELEMENT_TYPE
{
    VET_FLOAT2,
    VET_FLOAT3,
    VET_FLOAT4
};

enum VERTEXELEMENT_SEMANTIC : unsigned
{
    VES_POSITION = 0,
    VES_COLOR,
    VES_NORMAL,
    VES_TEXTURE_COORDINATES
};

class VertexElement final
{

    friend VertexDeclaration;

public:

    static int getTypeCount(VERTEXELEMENT_TYPE _type);

    static ::GL::DATABUFFER_TYPE getType(VERTEXELEMENT_TYPE _type);

    VertexElement(const VertexElement&) = delete;

    VertexElement(VertexElement&&) = delete;

    VertexElement& operator=(const VertexElement&) = delete;

    VertexElement& operator=(VertexElement&&) = delete;

    inline int getTypeCount() const;

    inline ::GL::DATABUFFER_TYPE getType() const;

    const unsigned short m_source;

    const int m_offsetInBytes;

    const VERTEXELEMENT_TYPE m_type;

    const VERTEXELEMENT_SEMANTIC m_semantic;

private:

    VertexElement(unsigned short _source, int _offsetInBytes, VERTEXELEMENT_TYPE _type, VERTEXELEMENT_SEMANTIC _semantic);

    ~VertexElement();

};

inline int VertexElement::getTypeCount() const
{
    return VertexElement::getTypeCount(m_type);
}

inline ::GL::DATABUFFER_TYPE VertexElement::getType() const
{
    return VertexElement::getType(m_type);
}

}
