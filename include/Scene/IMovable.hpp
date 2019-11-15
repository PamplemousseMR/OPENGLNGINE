#pragma once

#include "Commun/INameable.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <string>

namespace Scene
{

class SceneNode;

class IMovable :
        public Commun::INameable
{

public:

    friend class SceneNode;

    inline SceneNode* const getParent() const;
    inline bool const isInScene() const;

    inline const glm::mat4& getPositionMatrix() const;
    inline const glm::mat4& getRotationMatrix() const;
    inline const glm::mat4& getScaleMatrix() const;
    inline const glm::vec3& getPositionData() const;
    inline const glm::vec3& getRotationData() const;
    inline const glm::vec3& getScaleData() const;

    void setPosition(const glm::vec3&);
    void setRotation(const glm::vec3&);
    void setScale(const glm::vec3&);

protected:

    IMovable();
    IMovable(const std::string&);
    virtual ~IMovable();

private:

    inline void _notifyParent(SceneNode* const);
    inline void _notifyInSceneGraph(bool);

    SceneNode* m_parent {nullptr};
    bool m_isInSceneGraph {false};

    glm::mat4 m_positionMatrix {1.0};
    glm::vec3 m_positionData {0, 0, 0};
    glm::mat4 m_rotationMatrix {1.0};
    glm::vec3 m_rotationData {0, 0, 0};
    glm::mat4 m_scaleMatrix {1.0};
    glm::vec3 m_scaleData {1, 1, 1};

};

inline SceneNode* const IMovable::getParent() const
{
    return m_parent;
}

inline bool const IMovable::isInScene() const
{
    return m_isInSceneGraph;
}

inline const glm::mat4& IMovable::getPositionMatrix() const
{
    return m_positionMatrix;
}

inline const glm::mat4& IMovable::getRotationMatrix() const
{
    return m_rotationMatrix;
}

inline const glm::mat4& IMovable::getScaleMatrix() const
{
    return m_scaleMatrix;
}

inline const glm::vec3& IMovable::getPositionData() const
{
    return m_positionData;
}

inline const glm::vec3& IMovable::getRotationData() const
{
    return m_rotationData;
}

inline const glm::vec3& IMovable::getScaleData() const
{
    return m_scaleData;
}

inline void IMovable::_notifyParent(SceneNode* const _node)
{
    m_parent = _node;
}

inline void IMovable::_notifyInSceneGraph(bool _isInScene)
{
    m_isInSceneGraph = _isInScene;
}

}
