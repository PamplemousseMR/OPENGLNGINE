#include "OpenGLNgine/Hardware/VertexBufferBinding.hpp"

namespace Hardware
{

const HardwareVertexBufferPtr& VertexBufferBinding::getBuffer(unsigned _index) const
{
    const VertexBufferBindingMap::const_iterator it = m_bindingMap.find(_index);
    if(it == m_bindingMap.end())
    {
        GLNGINE_EXCEPTION("A vertex buffer with this index doesn't exist");
    }
    return it->second;
}

VertexBufferBinding::VertexBufferBinding()
{
}

VertexBufferBinding::~VertexBufferBinding()
{
    m_bindingMap.clear();
}

}
