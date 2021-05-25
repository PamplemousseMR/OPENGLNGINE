#include "OpenGLNgine/Render/SceneNode.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

#include <glm/gtx/transform.hpp>

namespace Render
{

SceneNode* SceneNode::createChild(const std::string& _name)
{
    if(m_children.find(_name) != m_children.end())
    {
        GLNGINE_EXCEPTION("A scene node with the name '" + _name + "' already exists");
    }

    SceneNode* sn = new SceneNode(m_sceneManager, this, _name);
    m_children.emplace(_name, sn);
    return sn;
}

void SceneNode::removeAndDestroyChild(SceneNode* const _child)
{
    GLNGINE_ASSERT_IF(!_child, "The scene node mustn't be null");

    SceneNodeList::const_iterator it = m_children.find(_child->getName());
    if(it == m_children.end())
    {
        GLNGINE_EXCEPTION("A scene node with the name '" + _child->getName() + "' doesn't exists");
    }

    m_children.erase(it);
    delete _child;
}

void SceneNode::removeAndDestroyAllChildren()
{
    SceneNodeList::iterator it = m_children.begin();
    while(it != m_children.end())
    {
        this->removeAndDestroyChild(it->second);
        it = m_children.begin();
    }
}

void SceneNode::attach(Component* const _component)
{
    GLNGINE_ASSERT_IF(!_component, "The component mustn't be null");

    if(m_attachedComponents.find(_component->getName()) != m_attachedComponents.end())
    {
        GLNGINE_EXCEPTION("A component with the name '" + _component->getName() + "' is already attached");
    }

    m_attachedComponents.emplace(_component->getName(), _component);
    _component->setParent(this);
}

void SceneNode::dettach(Component* const _component)
{
    GLNGINE_ASSERT_IF(!_component, "The component mustn't be null");

    ComponentList::const_iterator it = m_attachedComponents.find(_component->getName());
    if(it == m_attachedComponents.end())
    {
        GLNGINE_EXCEPTION("A component with the name '" + _component->getName() + "' is not attached");
    }

    m_attachedComponents.erase(it);
    _component->setParent(nullptr);
}

void SceneNode::dettachAll()
{
    ComponentList::iterator it = m_attachedComponents.begin();
    while(it != m_attachedComponents.end())
    {
        this->dettach(it->second);
        it = m_attachedComponents.begin();
    }
}

void SceneNode::setOrientation(const ::glm::vec3& _orientation)
{
    m_orientation = ::glm::radians(_orientation);
    setNeedUpdate();
}

void SceneNode::setPosition(const ::glm::vec3& _position)
{

    m_positon = _position;
    setNeedUpdate();
}

void SceneNode::setScale(const ::glm::vec3& _scale)
{
    m_scale = _scale;
    setNeedUpdate();
}

const ::glm::mat4 SceneNode::getFullTransform() const
{
    if(m_needUpdate)
    {
        ::glm::mat4 orientation(1.f);
        orientation = ::glm::rotate(orientation, m_orientation.y, ::glm::vec3(0.f, 1.f, 0.f));
        orientation = ::glm::rotate(orientation, m_orientation.x, ::glm::vec3(1.f, 0.f, 0.f));
        orientation = ::glm::rotate(orientation, m_orientation.z, ::glm::vec3(0.f, 0.f, 1.f));
        m_fullTransform = orientation * ::glm::scale(m_scale);
        if(!m_isRootSCeneNode)
        {
            m_fullTransform = m_parent->getFullTransform() * m_fullTransform;
        }
        m_needUpdate = false;
    }
    return m_fullTransform;
}

SceneNode::SceneNode(SceneManager* const _sceneManager):
    IResource("OpenGLNgine/Root"),
    m_sceneManager(_sceneManager),
    m_isRootSCeneNode(true)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");
}

SceneNode::SceneNode(SceneManager* const _sceneManager, SceneNode* const _parent, const std::string& _name):
    IResource(_name),
    m_sceneManager(_sceneManager),
    m_isRootSCeneNode(false),
    m_parent(_parent)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");
}

SceneNode::SceneNode(SceneManager* const _sceneManager, const std::string& _name):
    SceneNode(_sceneManager, nullptr, _name)
{
}

SceneNode::~SceneNode()
{
    this->removeAndDestroyAllChildren();
    this->dettachAll();
}

void SceneNode::setNeedUpdate()
{
    m_needUpdate = true;
    for(auto& child : m_children)
    {
        child.second->setNeedUpdate();
    }
}

}
