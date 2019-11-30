#pragma once

namespace Hardware
{

class VertexElement
{

public:

    enum VERTEXELEMENT_TYPE
    {
        VET_FLOAT2,
        VET_FLOAT3
    };

    enum VERTEXELEMENT_SEMANTIC
    {
        VES_POSITION,
        VES_NORMAL,
        VES_TEXTURE_COORDINATES
    };

    VertexElement(unsigned short, size_t, VERTEXELEMENT_TYPE, VERTEXELEMENT_SEMANTIC);
    ~VertexElement();

    inline unsigned short getSource() const;
    inline size_t getOffsetInBytes() const;
    inline VERTEXELEMENT_TYPE getType() const;
    inline VERTEXELEMENT_SEMANTIC getSemantic() const;

private:

    const unsigned short m_source;
    const size_t m_offsetInBytes;
    const VERTEXELEMENT_TYPE m_type;
    const VERTEXELEMENT_SEMANTIC m_semantic;

};

unsigned short VertexElement::getSource() const
{
    return m_source;
}

size_t VertexElement::getOffsetInBytes() const
{
    return m_offsetInBytes;
}

VertexElement::VERTEXELEMENT_TYPE VertexElement::getType() const
{
    return m_type;
}

VertexElement::VERTEXELEMENT_SEMANTIC VertexElement::getSemantic() const
{
    return m_semantic;
}

}
