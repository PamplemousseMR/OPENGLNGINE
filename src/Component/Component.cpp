#include "Component/Component.hpp"

using namespace std;
using namespace glm;

namespace Component
{
    Component::Component(const string& _name) :
        m_name(_name)
    {
    }

    Component::~Component()
    {
    }

    const mat4& Component::getPositionMatrix() const
    {
        return m_positionMatrix;
    }

    const mat4& Component::getRotationMatrix() const
    {
        return m_rotationMatrix;
    }

    const mat4& Component::getScaleMatrix() const
    {
        return m_scaleMatrix;
    }

    const vec3& Component::getPositionData() const
    {
        return m_positionData;
    }

    const vec3& Component::getRotationData() const
    {
        return m_rotationData;
    }

    const vec3& Component::getScaleData() const
    {
        return m_scaleData;
    }

    void Component::setPosition(const vec3& _position)
    {
        m_positionData = _position;
        m_positionMatrix = glm::translate(mat4(), m_positionData);
    }

    void Component::setRotation(const vec3& rotation)
    {
        m_rotationData = rotation;
        m_rotationMatrix = glm::rotate(mat4(), m_rotationData.x, vec3(1, 0, 0));
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.y, vec3(0, 1, 0));
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.z, vec3(0, 0, 1));
    }
    void Component::setScale(const vec3& _scaleData)
    {
        m_scaleData = _scaleData;
        m_scaleMatrix = scale(mat4(), m_scaleData);
    }

    void Component::addPosition(const vec3& _position)
    {
        m_positionData += _position;
        m_positionMatrix = glm::translate(m_positionMatrix, m_positionData);
    }

    void Component::addRotation(const vec3& _rotation)
    {
        m_rotationData = _rotation;
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.x, vec3(1, 0, 0));
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.y, vec3(0, 1, 0));
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.z, vec3(0, 0, 1));
    }
    void Component::addScale(const vec3& _scaleData)
    {
        m_scaleData += _scaleData;
        m_scaleMatrix = scale(m_scaleMatrix, m_scaleData);
    }
}
