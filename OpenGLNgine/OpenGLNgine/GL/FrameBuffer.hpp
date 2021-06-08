#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/GL/IBindable.hpp"
#include "OpenGLNgine/GL/RenderBuffer.hpp"
#include "OpenGLNgine/GL/Texture.hpp"

#include <vector>

namespace GL
{


/// Manages all frame buffer types.
enum FRAMBUFFER_MASK : GLbitfield
{
    FM_COLOR = GL_COLOR_BUFFER_BIT,
    FM_DEPTH = GL_DEPTH_BUFFER_BIT,
    FM_STENCIL = GL_STENCIL_BUFFER_BIT,
    FM_COLOR_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
    FM_COLOR_STENCIL = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    FM_DEPTH_STENCIL = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    FM_ALL = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
};

/// Manages all frame buffer filters.
enum FRAMBUFFER_FILTER : GLenum
{
    FF_LINEAR = GL_LINEAR,
    FF_NEAREST = GL_NEAREST
};

/**
 * @brief Manages a frame buffer object.
 */
class FrameBuffer final : public IBindable
{

public:

    /// Binds the current render frame buffer.
    static inline void bindDefault();

    /// Binds the current render frame buffer to as draw buffer.
    static inline void bindDrawDefault();

    /// Binds the current render frame buffer to as read buffer.
    static inline void bindReadDefault();

    /**
     * @brief Copy a block of pixels from a readable frame buffer to a drawable frame buffer.
     * @param _srcX0 X bounds of the source rectangle within the read buffer of the read framebuffer.
     * @param _srcY0 Y bounds of the source rectangle within the read buffer of the read framebuffer.
     * @param _srcX1
     * @param _srcY1
     * @param _dstX0 X bounds of the destination rectangle within the read buffer of the read framebuffer.
     * @param _dstY0 Y bounds of the destination rectangle within the read buffer of the read framebuffer.
     * @param _dstX1
     * @param _dstY1
     * @param _mask Bitwise OR of the flags indicating which buffers are to be copied.
     * @param _filter Interpolation to be applied if the image is stretched.
     */
    static inline void blit(int _srcX0, int _srcY0, int _srcX1, int _srcY1, int _dstX0, int _dstY0, int _dstX1, int _dstY1, FRAMBUFFER_MASK _mask, FRAMBUFFER_FILTER _filter);

    /// Creates a frame buffer.
    FrameBuffer();

    /// Destroys the frame buffer.
    ~FrameBuffer();

    /// Deleted copy constructor.
    FrameBuffer(const FrameBuffer&) = delete;

    /// Deleted move constructor.
    FrameBuffer(FrameBuffer&&) = delete;

    /// Deleted copy operator.
    FrameBuffer& operator=(const FrameBuffer&) = delete;

    /// Deleted move operator.
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    /**
     * @brief Attachs a texture image to a framebuffer object.
     * @param _texture Texture to attach.
     * @param _attach Attachment point to which an image from texture should be attached.
     */
    void attachColorTexture(const Texture& _texture, unsigned _attach);

    /**
     * @brief Attachs a depth texture to a framebuffer object.
     * @param _texture Depth texture to attach.
     */
    void attachDepthTexture(const Texture& _texture) const;

    /**
     * @brief Attachs a depth stencil texture to a framebuffer object.
     * @param _texture Depth stencil texture to attach.
     */
    void attachDepthStencilTexture(const Texture& _texture) const;

    /**
     * @brief Attachs an image buffer to a framebuffer object.
     * @param _buffer Buffer to attach.
     * @param _attach Attachment point to which an image from texture should be attached.
     */
    void attachColorBuffer(const RenderBuffer& _buffer, unsigned _attach);

    /**
     * @brief Attachs a depth buffer to a framebuffer object.
     * @param _buffer Depth buffer to attach.
     */
    inline void attachDepthBuffer(const RenderBuffer& _buffer) const;

    /**
     * @brief Attachs a depth stencil buffer to a framebuffer object.
     * @param _buffer Depth stencil buffer to attach.
     */
    inline void attachDepthStencilBuffer(const RenderBuffer& _buffer) const;

    /// Checks the completeness status of a framebuffer.
    void checkStatus() const;

    /// Specifies a list of color buffers to be drawn into.
    void attachDrawBuffers() const;

    /// Binds the draw frame buffer.
    void bindDraw() const;

    /// Binds the read frame buffer.
    void bindRead() const;

    /// Binds the frame buffer.
    void bind() const override;

    /// Unbinds the frame buffer.
    void unbind() const override;

private:

    /// Automaticaly called one time.
    struct Initializer final
    {
        /// Gets the max size of the viewport.
        Initializer();
    };

    /// Defines the maximum value where attach a color texture or buffer:
    static GLint s_MAX_ATTACHEMENT;

    /// Defines the maximum number of attachd color texture or buffer:
    static GLint s_MAX_DRAW;

    /// Stores all attached color buffer.
    std::vector< unsigned > m_colorAttachement {};

#ifdef GLNGINE_USE_STATE_CACHE    
    static ptrdiff_t s_defaultCache;

    static ptrdiff_t s_drawCache;

    static ptrdiff_t s_readCache;
#endif

};

inline void FrameBuffer::bindDefault()
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_defaultCache != add)
    {
        s_defaultCache = add;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
#else
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}

inline void FrameBuffer::bindDrawDefault()
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_drawCache != add)
    {
        s_drawCache = add;
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }
#else
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
#endif
}

inline void FrameBuffer::bindReadDefault()
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_readCache != add)
    {
        s_readCache = add;
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    }
#else
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
#endif
}

inline void FrameBuffer::blit(int _srcX0, int _srcY0, int _srcX1, int _srcY1, int _dstX0, int _dstY0, int _dstX1, int _dstY1, FRAMBUFFER_MASK _mask, FRAMBUFFER_FILTER _filter)
{
    glBlitFramebuffer(_srcX0, _srcY0, _srcX1, _srcY1, _dstX0, _dstY0, _dstX1, _dstY1, _mask, _filter);
    GLNGINE_CHECK_GL;
}

inline void FrameBuffer::attachDepthBuffer(const RenderBuffer& _buffer) const
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    GLNGINE_CHECK_GL;
}

inline void FrameBuffer::attachDepthStencilBuffer(const RenderBuffer& _buffer) const
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    GLNGINE_CHECK_GL;
}

}

