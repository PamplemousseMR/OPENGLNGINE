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
    ~Component();

    inline const glm::mat4& getPositionMatrix() const;
    inline const glm::mat4& getRotationMatrix() const;
    inline const glm::mat4& getScaleMatrix() const;
    inline const glm::vec3& getPositionData() const;
    inline const glm::vec3& getRotationData() const;
    inline const glm::vec3& getScaleData() const;

    void setPosition(const glm::vec3&);
    void setRotation(const glm::vec3&);
    void setScale(const glm::vec3&);

    void addPosition(const glm::vec3&);
    void addRotation(const glm::vec3&);
    void addScale(const glm::vec3&);

protected:

    std::string m_name {};

private:

    glm::mat4 m_positionMatrix {};
    glm::vec3 m_positionData {0, 0, 0};
    glm::mat4 m_rotationMatrix {};
    glm::vec3 m_rotationData {0, 0, 0};
    glm::mat4 m_scaleMatrix {};
    glm::vec3 m_scaleData {1, 1, 1};

};

inline const glm::mat4& Component::getPositionMatrix() const
{
    return m_positionMatrix;
}

inline const glm::mat4& Component::getRotationMatrix() const
{
    return m_rotationMatrix;
}

inline const glm::mat4& Component::getScaleMatrix() const
{
    return m_scaleMatrix;
}

inline const glm::vec3& Component::getPositionData() const
{
    return m_positionData;
}

inline const glm::vec3& Component::getRotationData() const
{
    return m_rotationData;
}

inline const glm::vec3& Component::getScaleData() const
{
    return m_scaleData;
}

}
