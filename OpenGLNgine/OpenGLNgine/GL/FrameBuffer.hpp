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
    FM_STENCIL = GL_STENCIL_BUFFER_BIT
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
    void attachColorTexture(const GL::Texture& _texture, unsigned _attach);

    /**
     * @brief Attachs a depth texture to a framebuffer object.
     * @param _texture Depth texture to attach.
     */
    void attachDepthTexture(const GL::Texture& _texture) const;

    /**
     * @brief Attachs a depth stencil texture to a framebuffer object.
     * @param _texture Depth stencil texture to attach.
     */
    void attachDepthStencilTexture(const GL::Texture& _texture) const;

    /**
     * @brief Attachs an image buffer to a framebuffer object.
     * @param _buffer Buffer to attach.
     * @param _attach Attachment point to which an image from texture should be attached.
     */
    void attachColorBuffer(const GL::RenderBuffer& _buffer, unsigned _attach);

    /**
     * @brief Attachs a depth buffer to a framebuffer object.
     * @param _buffer Depth buffer to attach.
     */
    inline void attachDepthBuffer(const GL::RenderBuffer& _buffer) const;

    /**
     * @brief Attachs a depth stencil buffer to a framebuffer object.
     * @param _buffer Depth stencil buffer to attach.
     */
    inline void attachDepthStencilBuffer(const GL::RenderBuffer& _buffer) const;

    /// Checks the completeness status of a framebuffer.
    void checkStatus() const;

    /// Specifies a list of color buffers to be drawn into.
    void attachDrawBuffers() const;

    /// Binds the draw frame buffer.
    inline void bindDraw() const;

    /// Binds the read frame buffer.
    inline void bindRead() const;

    /// Binds the frame buffer.
    inline void bind() const override;

    /// Unbinds the frame buffer.
    inline void unbind() const override;

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

    /// Defines the bind status.
    mutable bool m_isBinded { false };

};

inline void FrameBuffer::bindDefault()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline void FrameBuffer::bindDrawDefault()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

inline void FrameBuffer::bindReadDefault()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

inline void FrameBuffer::blit(int _srcX0, int _srcY0, int _srcX1, int _srcY1, int _dstX0, int _dstY0, int _dstX1, int _dstY1, FRAMBUFFER_MASK _mask, FRAMBUFFER_FILTER _filter)
{
    glBlitFramebuffer(_srcX0, _srcY0, _srcX1, _srcY1, _dstX0, _dstY0, _dstX1, _dstY1, _mask, _filter);
    GLNGINE_CHECK_GL;
}

inline void FrameBuffer::attachDepthBuffer(const GL::RenderBuffer& _buffer) const
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    GLNGINE_CHECK_GL;
}

inline void FrameBuffer::attachDepthStencilBuffer(const GL::RenderBuffer& _buffer) const
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    GLNGINE_CHECK_GL;
}

inline void FrameBuffer::bind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || !m_isBinded)
    {
        s_cache = add;
        m_isBinded = true;
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }
}

inline void FrameBuffer::unbind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add)
    {
        s_cache = add;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

inline void FrameBuffer::bindDraw() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_isBinded)
    {
        s_cache = add;
        m_isBinded = false;
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
    }
}

inline void FrameBuffer::bindRead() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add)
    {
        s_cache = add;
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
    }
}

}

