#include "Scene/SceneNode.hpp"
#include "Scene/SceneManager.hpp"

using namespace std;
using namespace Commun;

namespace Scene
{

SceneNode::SceneNode(SceneManager* const _creator) :
    IMovable(),
    m_creator(_creator)
{
    assert(_creator && "The scene manager creator can't be nullptr");
}

SceneNode::SceneNode(SceneManager* const _creator, const string& _name) :
    IMovable(_name),
    m_creator(_creator)
{
    assert(_creator && "The scene manager creator can't be nullptr");
}

SceneNode::~SceneNode()
{
}

SceneNode* SceneNode::createChild(const string& _name)
{
    if(m_children.find(_name) != m_children.end())
    {
        throw invalid_argument("[SceneNode] A direct scene node with the same name already exist");
    }
    SceneNode* const sn = m_creator->createSceneNode(_name);
    this->addChild(sn);
    return sn;
}

SceneNode* SceneNode::createChild()
{
    SceneNode* const sn = m_creator->createSceneNode();
    assert(m_children.find(sn->getName()) == m_children.end() && "A direct scene node with the same name already exist");
    this->addChild(sn);
    return sn;
}

void SceneNode::removeAndDestroyAllChildren()
{
    while(m_children.size() != 0)
    {
        m_creator->destroySceneNode(m_children.begin()->second);
    }
    assert(m_children.size() == 0 && "The children list must be empty after had destroy all children");
}

void SceneNode::removeAndDestroyChild(const SceneNode* _sn)
{
    removeAndDestroyChild(_sn->getName());
    _sn = nullptr;
}

void SceneNode::removeAndDestroyChild(const string& _name)
{
    const ChildMap::const_iterator cIt = m_children.find(_name);
    if(cIt == m_children.end())
    {
        throw invalid_argument("[SceneNode] A direct scene node with this name doesn't exist");
    }
    m_creator->destroySceneNode(cIt->second);
}

void SceneNode::removeAndDestroyChild(ChildMap::size_type _index)
{
    if(_index >= m_children.size())
    {
        throw invalid_argument("[SceneNode] A direct scene node with this index doesn't exist");
    }
    ChildMap::const_iterator cIt = m_children.begin();
    while(_index--)
    {
        ++cIt;
    }
    m_creator->destroySceneNode(cIt->second);
}

void SceneNode::addChild(SceneNode* const _sn)
{
    if(_sn->m_parent != nullptr)
    {
        throw invalid_argument("[SceneNode] The scene node is already the child of another scene node");
    }
    if(m_children.find(_sn->getName()) != m_children.end())
    {
        throw invalid_argument("[SceneNode] A direct scene node with the same name already exist");
    }
    _sn->_notifyParent(this);
    m_children[_sn->getName()] = _sn;
    if(m_parent)
    {
        _sn->setInSceneGraph(m_parent->isInScene());
    }
    else if(m_isRootSceneNode)
    {
        _sn->setInSceneGraph(true);
    }
    else
    {
        _sn->setInSceneGraph(false);
    }
}

void SceneNode::removeAllChildren()
{
    ChildMap::const_iterator cIt, cEnd;
    cEnd = m_children.end();
    for(cIt=m_children.begin() ; cIt!=cEnd ; ++cIt)
    {
        cIt->second->_notifyParent(nullptr);
        cIt->second->setInSceneGraph(false);
    }
    m_children.clear();
}

void SceneNode::removeChild(const SceneNode* const _sn)
{
    removeChild(_sn->getName());
}

SceneNode* SceneNode::removeChild(const string& _name)
{
    const ChildMap::const_iterator cIt = m_children.find(_name);
    if(cIt == m_children.end())
    {
        throw invalid_argument("[SceneNode] A direct scene node with this name doesn't exist");
    }
    SceneNode* sn = cIt->second;
    sn->_notifyParent(nullptr);
    sn->setInSceneGraph(false);
    m_children.erase(cIt);
    return sn;
}

SceneNode* SceneNode::removeChild(ChildMap::size_type _index)
{
    if(_index >= m_children.size())
    {
        throw invalid_argument("[SceneNode] A direct scene node with this index doesn't exist");
    }
    ChildMap::const_iterator cIt = m_children.begin();
    while(_index--)
    {
        ++cIt;
    }
    SceneNode* sn = cIt->second;
    sn->_notifyParent(nullptr);
    sn->setInSceneGraph(false);
    m_children.erase(cIt);
    return sn;
}

SceneNode* SceneNode::getChild(const string& _name) const
{
    const ChildMap::const_iterator cIt = m_children.find(_name);
    if(cIt == m_children.end())
    {
        throw invalid_argument("[SceneNode] A direct scene node with this name doesn't exist");
    }
    return cIt->second;
}

SceneNode* SceneNode::getChild(ChildMap::size_type _index) const
{
    if(_index >= m_children.size())
    {
        throw invalid_argument("[SceneNode] A direct scene node with this index doesn't exist");
    }
    ChildMap::const_iterator cIt = m_children.begin();
    while(_index--)
    {
        ++cIt;
    }
    return cIt->second;
}

void SceneNode::attachObject(IMovableObject* const _mo)
{
    if(_mo->m_parent != nullptr)
    {
        throw invalid_argument("[SceneNode] The movable object is already the child of another scene node");
    }
    if(m_objects.find(_mo->getName()) != m_objects.end())
    {
        throw invalid_argument("[SceneNode] A direct movable object with the same name already exist");
    }
    _mo->_notifyParent(this);
    m_objects[_mo->getName()] = _mo;
    _mo->_notifyInSceneGraph(this->isInScene());
}

void SceneNode::detachAllObjects()
{
    ObjectMap::const_iterator moIt, moEnd;
    moEnd = m_objects.end();
    for(moIt=m_objects.begin() ; moIt!=moEnd ; ++moIt)
    {
        moIt->second->_notifyParent(nullptr);
        moIt->second->_notifyInSceneGraph(false);
    }
    m_objects.clear();
}

void SceneNode::detachObject(const IMovableObject* const _mo)
{
    detachObject(_mo->getName());
}

IMovableObject* SceneNode::detachObject(const std::string& _name)
{
    const ObjectMap::const_iterator moIt = m_objects.find(_name);
    if(moIt == m_objects.end())
    {
        throw invalid_argument("[SceneNode] A direct movable object with this name doesn't exist");
    }
    IMovableObject* mo = moIt->second;
    mo->_notifyParent(nullptr);
    mo->_notifyInSceneGraph(false);
    m_objects.erase(moIt);
    return mo;
}


IMovableObject* SceneNode::detachObject(ObjectMap::size_type _index)
{
    if(_index >= m_objects.size())
    {
        throw invalid_argument("[SceneNode] A direct movable object with this index doesn't exist");
    }
    ObjectMap::const_iterator moIt = m_objects.begin();
    while(_index--)
    {
        ++moIt;
    }
    IMovableObject* mo = moIt->second;
    mo->_notifyParent(nullptr);
    mo->_notifyInSceneGraph(false);
    m_objects.erase(moIt);
    return mo;
}

IMovableObject* SceneNode::getAttachedObject(const string& _name) const
{
    const ObjectMap::const_iterator moIt = m_objects.find(_name);
    if(moIt == m_objects.end())
    {
        throw invalid_argument("[SceneNode] A direct movable object with this name doesn't exist");
    }
    return moIt->second;
}

IMovableObject* SceneNode::getAttachedObject(ObjectMap::size_type _index) const
{
    if(_index >= m_objects.size())
    {
        throw invalid_argument("[SceneNode] A direct movable object with this index doesn't exist");
    }
    ObjectMap::const_iterator oIt = m_objects.begin();
    while(_index--)
    {
        ++oIt;
    }
    return oIt->second;
}

void SceneNode::_notifyRoot()
{
    m_isRootSceneNode = true;
    this->setInSceneGraph(true);
}

void SceneNode::setInSceneGraph(bool _isInScene)
{
    ObjectMap::const_iterator moIt, moEnd;
    moEnd = m_objects.end();
    for(moIt=m_objects.begin() ; moIt!=moEnd ; ++moIt)
    {
        moIt->second->_notifyInSceneGraph(_isInScene);
    }
    ChildMap::const_iterator cIt, cEnd;
    cEnd = m_children.end();
    for(cIt=m_children.begin() ; cIt!=cEnd ; ++cIt)
    {
        cIt->second->_notifyInSceneGraph(_isInScene);
    }
    this->_notifyInSceneGraph(_isInScene);
}

}
