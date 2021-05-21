#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/GL/IBindable.hpp"

#include <vector>

namespace GL
{

#define BUFFER_OFFSET(i) (reinterpret_cast< void* >(GLintptr(i)))

/// Manages the data store target.
enum DATABUFFER_TARGET : GLenum
{
    DT_ARRAY = GL_ARRAY_BUFFER,
    DT_ELEMENT = GL_ELEMENT_ARRAY_BUFFER
};

/// Manage all supported type.
enum DATABUFFER_TYPE : GLenum
{
    DT_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    DT_BYTE = GL_BYTE,
    DT_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    DT_SHORT = GL_SHORT,
    DT_UNSIGNED_INT = GL_UNSIGNED_INT,
    DT_INT = GL_INT,
    DT_FLOAT = GL_FLOAT
};

/// Manages all expected usage pattern of the data store.
enum DATABUFFER_USAGE : GLenum
{
    DT_STREAM_DRAW = GL_STREAM_DRAW,
    DT_STREAM_READ = GL_STREAM_READ,
    DT_STREAM_COPY = GL_STREAM_COPY,
    DT_STATIC_DRAW = GL_STATIC_DRAW,
    DT_STATIC_READ = GL_STATIC_READ,
    DT_STATIC_COPY = GL_STATIC_COPY,
    DT_DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DT_DYNAMIC_READ = GL_DYNAMIC_READ,
    DT_DYNAMIC_COPY = GL_DYNAMIC_COPY
};

/**
 * @brief Manages a buffer object.
 */
class DataBuffer final : public IBindable
{

public:

    /**
    * @brief Enables the generic vertex attribute array.
    * @param _location Index of the genereric vertex attribute to be enabled.
    */
    static inline void setLocation(unsigned _location);

    /**
    * @brief Defines an array of generic vertex attribute data.
    * @param _location Index of the generic vertex attribute to be modified.
    * @param _size Number of components per generic vertex attribute. Must be 1, 2, 3, 4.
    * @param _type Data type of each component in the array.
    * @param _normalize Whether fixed-point data values should be normalized or converted directly as fixed-point values when they are accessed.
    * @param _stride Byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array.
    * @param _offset Offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently.
    */
    static inline void setAttrib(unsigned _location, int _size, DATABUFFER_TYPE _type, bool _normalize, int _stride, int _offset);

    /// Creates a buffer.
    DataBuffer(DATABUFFER_TARGET _target);

    /// Destroys buffer.
    ~DataBuffer();

    /**
     * @brief Generates a new buffer and copy the contents of the parameter to the generated one.
     * @param _buffer The buffer to copy.
     */
    DataBuffer(const DataBuffer& _buffer);

    /**
     * @brief Copies the contents of the buffer to the current one.
     * @param _buffer The buffer to copy.
     */
    DataBuffer& operator=(const DataBuffer& _buffer);

    /// Deleted move constructor.
    DataBuffer(DataBuffer&&) = delete;

    /// Deleted move operator.
    DataBuffer& operator=(DataBuffer&&) = delete;

    /**
     * @brief Creates and initializes the buffer object's data store.
     * @param _arr Data to be copied into the data store.
     * @param _usage Expected usage pattern.
     */
    template<typename T>
    inline void writeData(const std::vector<T>& _arr, DATABUFFER_USAGE _usage) const;

    /**
     * @brief Creates and initializes the buffer object's data store.
     * @param _sizeInBytes Size in bytes of the buffer object's new data store.
     * @param _src Pointer to data that will be copied into the data store for initialization.
     * @param _usage Expected usage pattern.
     */
    inline void writeData(size_t _sizeInBytes, const void* _src, DATABUFFER_USAGE _usage) const;

    /**
     * @brief Creates and initializes the buffer object's data store.
     * @param _offset Offset into the buffer object's data store where data replacement will begin.
     * @param _sizeInBytes Size in bytes of the buffer object's new data store.
     * @param _src Pointer to data that will be copied into the data store for initialization.
     */
    inline void writeData(size_t _offset, size_t _sizeInBytes, const void* _src) const;

    /// Binds the buffer.
    inline virtual void bind() const override;

    /// Unbinds the buffer.
    inline virtual void unbind() const override;

private:

    /// Defines the buffer target.
    const GLenum m_target;

    /// Defines the bind status.
    mutable bool m_isBinded { false };

};

inline void DataBuffer::setLocation(unsigned _location)
{
    glEnableVertexAttribArray(_location);
    GLNGINE_CHECK_GL;
}

inline void DataBuffer::setAttrib(unsigned _location, int _size, DATABUFFER_TYPE _type, bool _normalize, int _stride, int _offset)
{
    glVertexAttribPointer(_location, _size, _type, _normalize, _stride, BUFFER_OFFSET(_offset));
    GLNGINE_CHECK_GL;
}

template<typename T>
inline void DataBuffer::writeData(const std::vector<T>& _arr, DATABUFFER_USAGE _usage) const
{
    glBufferData(m_target, _arr.size() * sizeof(T), &_arr[0], _usage);
    GLNGINE_CHECK_GL;
}

inline void DataBuffer::writeData(size_t _sizeInBytes, const void* _src, DATABUFFER_USAGE _usage) const
{
    glBufferData(m_target, _sizeInBytes, _src, _usage);
    GLNGINE_CHECK_GL;
}

inline void DataBuffer::writeData(size_t _offset, size_t _sizeInBytes, const void* _src) const
{
    glBufferSubData(m_target, _offset, _sizeInBytes, _src);
    GLNGINE_CHECK_GL;
}

inline void DataBuffer::bind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || !m_isBinded)
    {
        s_cache = add;
        m_isBinded = true;
        glBindBuffer(m_target, m_id);
    }
}

inline void DataBuffer::unbind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_isBinded)
    {
        s_cache = add;
        m_isBinded = false;
        glBindBuffer(m_target, 0);
    }
}

}

