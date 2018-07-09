#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

namespace Component
{
class Component
{

public :

    Component(const std::string&);
    ~Component();

    const glm::mat4& getPositionMatrix() const;
    const glm::mat4& getRotationMatrix() const;
    const glm::mat4& getScaleMatrix() const;
    const glm::vec3& getPositionData() const;
    const glm::vec3& getRotationData() const;
    const glm::vec3& getScaleData() const;

    void setPosition(const glm::vec3&);
    void setRotation(const glm::vec3&);
    void setScale(const glm::vec3&);

    void addPosition(const glm::vec3&);
    void addRotation(const glm::vec3&);
    void addScale(const glm::vec3&);

private:

    std::string m_name;
    glm::mat4 m_positionMatrix;
    glm::vec3 m_positionData;
    glm::mat4 m_rotationMatrix;
    glm::vec3 m_rotationData;
    glm::mat4 m_scaleMatrix;
    glm::vec3 m_scaleData;

};
}
