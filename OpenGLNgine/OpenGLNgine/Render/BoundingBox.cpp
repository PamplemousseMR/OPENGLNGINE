#include "OpenGLNgine/Render/BoundingBox.hpp"

#include <algorithm>

namespace Render
{

void BoundingBox::merge(const BoundingBox& _box)
{
    m_min.x = std::min(m_min.x, _box.m_min.x);
    m_min.y = std::min(m_min.y, _box.m_min.y);
    m_min.z = std::min(m_min.z, _box.m_min.z);

    m_max.x = std::max(m_max.x, _box.m_max.x);
    m_max.y = std::max(m_max.y, _box.m_max.y);
    m_max.z = std::max(m_max.z, _box.m_max.z);
}

}
