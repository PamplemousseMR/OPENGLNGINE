#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/GL/DataBuffer.hpp"

#include <GL/glew.h>

namespace GL 
{

/// Manages all clear operations.
enum DRAWCALL_CLEAR : GLbitfield
{
    DC_COLOR = GL_COLOR_BUFFER_BIT,
    DC_DEPTH = GL_DEPTH_BUFFER_BIT,
    DC_STENCIL = GL_STENCIL_BUFFER_BIT,
    DC_COLOR_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
    DC_COLOR_STENCIL = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    DC_DEPTH_STENCIL = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    DC_ALL = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
};

/// Manages render operations.
enum DRAWCALL_MODE : GLenum
{
    DR_POINTS = GL_POINTS,
    DR_LINE_STRIP = GL_LINE_STRIP,
    DR_LINE_LOOP = GL_LINE_LOOP,
    DR_LINES = GL_LINES,
    DR_LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
    DR_LINES_ADJACENCY = GL_LINES_ADJACENCY,
    DR_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    DR_TRIANGLE_FAN = GL_TRIANGLE_FAN,
    DR_TRIANGLES = GL_TRIANGLES,
    DR_TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
    DR_TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY
};

/**
 * @brief Manages draw calls.
 */
class DrawCall final
{

public:

    /**
     * @brief Clears the buffers to preset values.
     * @param _mask Buffers to clear.
     */
    inline static void clear(DRAWCALL_CLEAR _mask);

    /**
     * @brief Renders primitives from element data.
     * @param _mode Specifies what kind of primitives to render.
     * @param _count Specifies the number of elements to be rendered.
     * @param _type Specifies the type of the values in indices.
     * @param _offset Specifies a pointer to the location where the indices are stored.
     */
    inline static void drawElements(DRAWCALL_MODE _mode, unsigned _count, DATABUFFER_TYPE _type, int _offset);

    /**
     * @brief Render primitives from array data.
     * @param _mode Specifies what kind of primitives to render.
     * @param _first Specifies the starting index in the enabled arrays.
     * @param _count Specifies the number of indices to be rendered.
     */
    inline static void drawArrays(DRAWCALL_MODE _mode, int _first, unsigned _count);

};

inline void DrawCall::clear(DRAWCALL_CLEAR _mask)
{
    glClear(_mask);
    GLNGINE_CHECK_GL;
}

inline void DrawCall::drawElements(DRAWCALL_MODE _mode, unsigned _count, DATABUFFER_TYPE _type, int _offset)
{
    glDrawElements(_mode, _count, _type, BUFFER_OFFSET(_offset));
    GLNGINE_CHECK_GL;
}

inline void DrawCall::drawArrays(DRAWCALL_MODE _mode, int _first, unsigned _count)
{
    glDrawArrays(_mode, _first, _count);
    GLNGINE_CHECK_GL;
}

}

