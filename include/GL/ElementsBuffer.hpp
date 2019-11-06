#pragma once

#include <vector>
#include <assert.h>

#include "GL/IBindable.hpp"

namespace GL
{

class ElementsBuffer : public IBindable
{

public:

    ElementsBuffer();
    ~ElementsBuffer() noexcept final;
    ElementsBuffer(const ElementsBuffer&) noexcept;
    ElementsBuffer(ElementsBuffer&&) = delete;
    ElementsBuffer& operator=(const ElementsBuffer&) noexcept;
    ElementsBuffer& operator=(ElementsBuffer&&) = delete;

    template<typename T>
    inline void setData(const std::vector<T>&) const noexcept;

    inline virtual void bind() const noexcept final;
    inline virtual void unbind() const noexcept final;

};

template<typename T>
inline void ElementsBuffer::setData(const std::vector<T>& _arr) const noexcept
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _arr.size() * sizeof(T), &_arr[0], GL_STATIC_DRAW);
    assert(glGetError() == GL_NO_ERROR);
}

inline void ElementsBuffer::bind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void ElementsBuffer::unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}

