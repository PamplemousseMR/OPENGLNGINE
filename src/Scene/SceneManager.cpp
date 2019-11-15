#include "Scene/SceneManager.hpp"

using namespace std;

namespace Scene
{

SceneManager* SceneManager::s_INSTANCE = nullptr;

SceneManager& SceneManager::getInstance()
{
    SceneManager* instance = SceneManager::getInstancePtr();
    return *instance;
}

SceneManager* SceneManager::getInstancePtr()
{
    const static MemGuard memGuard;
    if(!s_INSTANCE)
    {
        s_INSTANCE = new SceneManager();
    }
    return s_INSTANCE;
}

SceneManager::SceneManager()
{
    m_root = new SceneNode(this);
    m_root->_notifyRoot();
}

SceneManager::~SceneManager()
{
    while(m_sceneNodes.size() != 0)
    {
        destroySceneNode(m_sceneNodes.begin()->second);
    }
    while(m_movableObjectCollections.size() != 0)
    {
        MovableObjectCollectionMap::const_iterator mocIt = m_movableObjectCollections.begin();
        MovableObjectMap* movableObjects = mocIt->second;
        while(movableObjects->size() != 0)
        {
            MovableObjectMap::const_iterator moIt = movableObjects->begin();
            delete moIt->second;
            movableObjects->erase(moIt);
        }
        delete mocIt->second;
        m_movableObjectCollections.erase(mocIt);
    }
    delete m_root;
}

SceneNode* SceneManager::createSceneNode()
{
    SceneNode* sn = new SceneNode(this);
    assert(m_sceneNodes.find(sn->getName()) == m_sceneNodes.end() && "A scene node with the same name already exist");
    m_sceneNodes[sn->getName()] = sn;
    return sn;
}

SceneNode* SceneManager::createSceneNode(const std::string& _name)
{
    if(m_sceneNodes.find(_name) != m_sceneNodes.end())
    {
        throw invalid_argument("[SceneManager] A scene node with the same name already exist");
    }
    SceneNode* sn = new SceneNode(this, _name);
    m_sceneNodes[sn->getName()] = sn;
    return sn;
}

void SceneManager::destroySceneNode(const SceneNode* _sn)
{
    destroySceneNode(_sn->getName());
    _sn = nullptr;
}

void SceneManager::destroySceneNode(const std::string& _name)
{
    const SceneNodeMap::const_iterator snIt = m_sceneNodes.find(_name);
    if(snIt == m_sceneNodes.end())
    {
        throw invalid_argument("[SceneManager] A scene node with this name doesn't exist");
    }
    if(snIt->second == m_root)
    {
        throw invalid_argument("[SceneManager] Can't destroy the root scene node");
    }
    SceneNode* sn = snIt->second;
    sn->removeAndDestroyAllChildren();
    sn->detachAllObjects();
    SceneNode* parent = sn->getParent();
    if(parent)
    {
        parent->removeChild(sn);
    }
    m_sceneNodes.erase(snIt);
    delete sn;
}

SceneNode* SceneManager::getSceneNode(const std::string& _name)
{
    const SceneNodeMap::const_iterator snIt = m_sceneNodes.find(_name);
    if(snIt == m_sceneNodes.end())
    {
        throw invalid_argument("[SceneManager] A scene node with this name doesn't exist");
    }
    return snIt->second;
}

Light* SceneManager::createLight()
{
    Light* l = new Light();
    MovableObjectMap* lights = this->getMovableObjectMap(Light::s_FACTORY_TYPE_NAME);
    assert(lights->find(l->getName()) == lights->end() && "A light with the same name already exist");
    (*lights)[l->getName()] = l;
    return l;
}

Light* SceneManager::createLight(const std::string& _name)
{
    Light* l = new Light(_name);
    MovableObjectMap* lights = this->getMovableObjectMap(Light::s_FACTORY_TYPE_NAME);
    if(lights->find(_name) != lights->end())
    {
        throw invalid_argument("[SceneManager] A light with the same name already exist");
    }
    (*lights)[l->getName()] = l;
    return l;
}

void SceneManager::destroyLight(const Light* _l)
{
    destroyLight(_l->getName());
    _l = nullptr;
}

void SceneManager::destroyLight(const std::string& _name)
{
    this->destroyMovableObject(_name, Light::s_FACTORY_TYPE_NAME);
}

Light* SceneManager::getLight(const std::string& _name)
{
    IMovableObject* mo = this->getMovableObject(_name, Light::s_FACTORY_TYPE_NAME);
    return static_cast<Light*>(mo);
}

void SceneManager::destroyMovableObject(const IMovableObject* _mo)
{
    destroyMovableObject(_mo->getName(), _mo->s_FACTORY_TYPE_NAME);
    _mo = nullptr;
}

void SceneManager::destroyMovableObject(const std::string& _name, const std::string& _typeName)
{
    MovableObjectMap* objects = this->getMovableObjectMap(_typeName);
    const MovableObjectMap::const_iterator moIt = objects->find(_name);
    if(moIt == objects->end())
    {
        throw invalid_argument("[SceneManager] A movable object with this name doesn't exist");
    }
    IMovableObject* mo = moIt->second;
    SceneNode* parent = mo->getParent();
    if(parent)
    {
        parent->detachObject(mo);
    }
    objects->erase(moIt);
    delete mo;
}

IMovableObject* SceneManager::getMovableObject(const std::string& _name, const std::string& _typeName)
{
    MovableObjectMap* objects = this->getMovableObjectMap(_typeName);
    const MovableObjectMap::const_iterator moIt = objects->find(_name);
    if(moIt == objects->end())
    {
        throw invalid_argument("[SceneManager] A movable object with this name doesn't exist");
    }
    return moIt->second;
}

SceneManager::MovableObjectMap* SceneManager::getMovableObjectMap(const std::string& _typeName)
{
    MovableObjectCollectionMap::iterator mocIt = m_movableObjectCollections.find(_typeName);
    if(mocIt == m_movableObjectCollections.end())
    {
        MovableObjectMap* newCollection = new MovableObjectMap();
        m_movableObjectCollections[_typeName] = newCollection;
        return newCollection;
    }
    else
    {
        return mocIt->second;
    }
}

}
