#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <string>

namespace Component
{
class Component
{

public :

    Component(const std::string&);
    virtual ~Component();
    Component(const Component&);
    Component(Component&&);
    Component& operator=(const Component&);
    Component& operator=(Component&&);

    inline const std::string& getName() const;
    inline const glm::mat4& getPositionMatrix() const noexcept;
    inline const glm::mat4& getRotationMatrix() const noexcept;
    inline const glm::mat4& getScaleMatrix() const noexcept;
    inline const glm::vec3& getPositionData() const noexcept;
    inline const glm::vec3& getRotationData() const noexcept;
    inline const glm::vec3& getScaleData() const noexcept;

    void setPosition(const glm::vec3&) noexcept;
    void setRotation(const glm::vec3&) noexcept;
    void setScale(const glm::vec3&) noexcept;

protected:

    std::string m_name {};

private:

    glm::mat4 m_positionMatrix {1.0};
    glm::vec3 m_positionData {0, 0, 0};
    glm::mat4 m_rotationMatrix {1.0};
    glm::vec3 m_rotationData {0, 0, 0};
    glm::mat4 m_scaleMatrix {1.0};
    glm::vec3 m_scaleData {1, 1, 1};

};

inline const std::string& Component::getName() const
{
    return m_name;
}

inline const glm::mat4& Component::getPositionMatrix() const noexcept
{
    return m_positionMatrix;
}

inline const glm::mat4& Component::getRotationMatrix() const noexcept
{
    return m_rotationMatrix;
}

inline const glm::mat4& Component::getScaleMatrix() const noexcept
{
    return m_scaleMatrix;
}

inline const glm::vec3& Component::getPositionData() const noexcept
{
    return m_positionData;
}

inline const glm::vec3& Component::getRotationData() const noexcept
{
    return m_rotationData;
}

inline const glm::vec3& Component::getScaleData() const noexcept
{
    return m_scaleData;
}

}
