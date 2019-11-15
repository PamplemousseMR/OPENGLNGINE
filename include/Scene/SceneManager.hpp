#pragma once

#include "Scene/SceneNode.hpp"
#include "Scene/IMovableObject.hpp"
#include "Scene/Light.hpp"

#include <map>
#include <string>

namespace Scene
{

class SceneManager final
{

public:

    typedef std::map<std::string, SceneNode*> SceneNodeMap;
    typedef std::map<std::string, IMovableObject*> MovableObjectMap;
    typedef std::map<std::string, MovableObjectMap*> MovableObjectCollectionMap;

    static SceneManager& getInstance();
    static SceneManager* getInstancePtr();

    inline SceneNode* const getRootSceneNode() const;

    SceneNode* createSceneNode();
    SceneNode* createSceneNode(const std::string&);
    void destroySceneNode(const SceneNode*);
    void destroySceneNode(const std::string&);
    SceneNode* getSceneNode(const std::string&);

    Light* createLight();
    Light* createLight(const std::string&);
    void destroyLight(const Light*);
    void destroyLight(const std::string&);
    Light* getLight(const std::string&);

    void destroyMovableObject(const IMovableObject*);
    void destroyMovableObject(const std::string&, const std::string&);
    IMovableObject* getMovableObject(const std::string&, const std::string&);

private:

    class MemGuard final
    {

    public:

        ~MemGuard()
        {
            delete SceneManager::s_INSTANCE;
            SceneManager::s_INSTANCE = nullptr;
        }

    };

    static SceneManager* s_INSTANCE;

    SceneManager();
    ~SceneManager();

    SceneManager(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    MovableObjectMap* getMovableObjectMap(const std::string&);

    SceneNode* m_root {nullptr};
    SceneNodeMap m_sceneNodes;
    MovableObjectCollectionMap m_movableObjectCollections;

};

inline SceneNode* const SceneManager::getRootSceneNode() const
{
    return m_root;
}

}
