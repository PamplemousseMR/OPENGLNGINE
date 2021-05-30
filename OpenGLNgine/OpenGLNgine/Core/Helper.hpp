#pragma once

#include <assimp/types.h>
#include <glm/glm.hpp>

namespace Core
{

::glm::vec3 fromAI(const ::aiColor3D& _data)
{
    return ::glm::vec3(_data[0], _data[1], _data[2]);
}

::aiColor3D toAI(const ::glm::vec3& _data)
{
    return ::aiColor3D(_data[0], _data[1], _data[2]);
}

}
