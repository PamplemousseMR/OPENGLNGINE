#include "Component/Component.hpp"

#include <glm/gtc/matrix_transform.hpp>

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

    Component::Component(const Component& _component) :
        m_name(_component.m_name),
        m_positionMatrix(_component.m_positionMatrix),
        m_positionData(_component.m_positionData),
        m_rotationMatrix(_component.m_rotationMatrix),
        m_rotationData(_component.m_rotationData),
        m_scaleMatrix(_component.m_scaleMatrix),
        m_scaleData(_component.m_scaleData)
    {
    }

    Component::Component(Component&& _component) :
        m_name(std::move(_component.m_name)),
        m_positionMatrix(std::move(_component.m_positionMatrix)),
        m_positionData(std::move(_component.m_positionData)),
        m_rotationMatrix(std::move(_component.m_rotationMatrix)),
        m_rotationData(std::move(_component.m_rotationData)),
        m_scaleMatrix(std::move(_component.m_scaleMatrix)),
        m_scaleData(std::move(_component.m_scaleData))
    {
    }

    Component& Component::operator=(const Component& _component)
    {
        if(this != &_component)
        {
            m_name = _component.m_name;
            m_positionMatrix = _component.m_positionMatrix;
            m_positionData = _component.m_positionData;
            m_rotationMatrix = _component.m_rotationMatrix;
            m_rotationData = _component.m_rotationData;
            m_scaleMatrix = _component.m_scaleMatrix;
            m_scaleData = _component.m_scaleData;
        }
        return *this;
    }

    Component& Component::operator=(Component&& _component)
    {
        if(this != &_component)
        {
            m_name = std::move(_component.m_name);
            m_positionMatrix = std::move(_component.m_positionMatrix);
            m_positionData = std::move(_component.m_positionData);
            m_rotationMatrix = std::move(_component.m_rotationMatrix);
            m_rotationData = std::move(_component.m_rotationData);
            m_scaleMatrix = std::move(_component.m_scaleMatrix);
            m_scaleData = std::move(_component.m_scaleData);
        }
        return *this;
    }

    void Component::setPosition(const vec3& _position) noexcept
    {
        m_positionData = _position;
        m_positionMatrix = glm::translate(mat4(1.0), m_positionData);
    }

    void Component::setRotation(const vec3& rotation) noexcept
    {
        m_rotationData = rotation;
        m_rotationMatrix = glm::rotate(mat4(1.0), m_rotationData.x, vec3(1, 0, 0));
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.y, vec3(0, 1, 0));
        m_rotationMatrix = glm::rotate(m_rotationMatrix, m_rotationData.z, vec3(0, 0, 1));
    }

    void Component::setScale(const vec3& _scaleData) noexcept
    {
        m_scaleData = _scaleData;
        m_scaleMatrix = scale(mat4(1.0), m_scaleData);
    }
}
