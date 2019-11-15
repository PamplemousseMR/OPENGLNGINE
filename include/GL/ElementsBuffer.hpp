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
    ~ElementsBuffer() final;
    ElementsBuffer(const ElementsBuffer&);
    ElementsBuffer(ElementsBuffer&&) = delete;
    ElementsBuffer& operator=(const ElementsBuffer&);
    ElementsBuffer& operator=(ElementsBuffer&&) = delete;

    template<typename T>
    inline void setData(const std::vector<T>&) const;

    inline virtual void bind() const final;
    inline virtual void unbind() const final;

};

template<typename T>
inline void ElementsBuffer::setData(const std::vector<T>& _arr) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _arr.size() * sizeof(T), &_arr[0], GL_STATIC_DRAW);
    assert(glGetError() == GL_NO_ERROR);
}

inline void ElementsBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void ElementsBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}

