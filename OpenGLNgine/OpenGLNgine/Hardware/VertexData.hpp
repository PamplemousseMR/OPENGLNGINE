#pragma once

#include "OpenGLNgine/GL/DrawCall.hpp"
#include "OpenGLNgine/Hardware/VertexBufferBinding.hpp"
#include "OpenGLNgine/Hardware/VertexDeclaration.hpp"

namespace Hardware
{

enum VERTEXDATA_RENDERTYPE
{
    VR_POINTS,
    VR_LINE_STRIP,
    VR_LINE_LOOP,
    VR_LINES,
    VR_LINE_STRIP_ADJACENCY,
    VR_LINES_ADJACENCY,
    VR_TRIANGLE_STRIP,
    VR_TRIANGLE_FAN,
    VR_TRIANGLES,
    VR_TRIANGLE_STRIP_ADJACENCY,
    VR_TRIANGLES_ADJACENCY
};

class HardwareBufferManager;

class VertexData final
{

    friend HardwareBufferManager;

public:

    VertexData(const VertexData&) = delete;

    VertexData(VertexData&&) = delete;

    VertexData& operator=(const VertexData&) = delete;

    VertexData& operator=(VertexData&&) = delete;

    inline ::GL::DRAWCALL_MODE getRenderType() const;

    int m_vertexStart {0};

    int m_vertexCount {0};

    VERTEXDATA_RENDERTYPE m_renderOperation { VR_TRIANGLES };

    VertexDeclaration* const m_vertexDeclaration { nullptr };

    VertexBufferBinding* const m_vertexBufferBinding { nullptr };

private:

    static ::GL::DRAWCALL_MODE getRenderType(VERTEXDATA_RENDERTYPE _type);

    VertexData(HardwareBufferManager* const _manager);

    ~VertexData();

    HardwareBufferManager* const m_manager;

};

inline ::GL::DRAWCALL_MODE VertexData::getRenderType() const
{
    return getRenderType(m_renderOperation);
}

}
