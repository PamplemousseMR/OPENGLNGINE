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
    VES_COLOR_0 = 1,
    VES_COLOR_1 = 2,
    VES_COLOR_2 = 3,
    VES_COLOR_3 = 4,
    VES_COLOR_4 = 5,
    VES_COLOR_5 = 6,
    VES_NORMAL = 7,
    VES_TEXTURE_COORDINATES_0 = 8,
    VES_TEXTURE_COORDINATES_1 = 9,
    VES_TEXTURE_COORDINATES_2 = 10,
    VES_TEXTURE_COORDINATES_3 = 11,
    VES_TEXTURE_COORDINATES_4 = 12,
    VES_TEXTURE_COORDINATES_5 = 13,
    VES_TANGENT = 14,
    VES_BITANGENT = 15,
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
