#pragma once

#include <glm/glm.hpp>

namespace Render
{

class BoundingBox final
{

public:

    BoundingBox() = default;

    ~BoundingBox() = default;

    BoundingBox(const BoundingBox&) = default;

    BoundingBox(BoundingBox&&) = default;

    BoundingBox& operator=(const BoundingBox&) = default;

    BoundingBox& operator=(BoundingBox&&) = default;

    ::glm::vec3 m_min { 0.f };

    ::glm::vec3 m_max { 0.f };

    void merge(const BoundingBox& _box);

};

}
