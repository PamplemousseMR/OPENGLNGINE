#include "Scene/IMovable.hpp"
#include "Scene/SceneNode.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace Commun;
using namespace glm;
using namespace std;

namespace Scene
{

IMovable::IMovable():
    INameable()
{
}

IMovable::IMovable(const string& _name):
    INameable(_name)
{
}

IMovable::~IMovable()
{
}

void IMovable::setPosition(const vec3& _position)
{
    m_positionData = _position;
    m_positionMatrix = glm::translate(mat4(1.0), m_positionData);
}

void IMovable::setRotation(const vec3& rotation)
{
    m_rotationData = rotation;
    m_rotationMatrix = glm::rotate(mat4(1.0), m_rotationData.x, vec3(1, 0, 0));
    m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.y, vec3(0, 1, 0));
    m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.z, vec3(0, 0, 1));
}

void IMovable::setScale(const vec3& _scaleData)
{
    m_scaleData = _scaleData;
    m_scaleMatrix = scale(mat4(1.0), m_scaleData);
}

}
