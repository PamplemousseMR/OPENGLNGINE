#pragma once

#include <Scene/IMovable.hpp>
#include <Scene/IMovableObject.hpp>

#include <string>
#include <map>

namespace Scene
{

class SceneManager;

class SceneNode final:
        public IMovable
{

public:

    typedef std::map<std::string, SceneNode*> ChildMap;
    typedef std::map<std::string, IMovableObject*> ObjectMap;

    SceneNode(SceneManager* const);
    SceneNode(SceneManager* const, const std::string&);
    virtual ~SceneNode() final;

    SceneNode* createChild(const std::string&);
    SceneNode* createChild();
    void removeAndDestroyAllChildren();
    void removeAndDestroyChild(const SceneNode*);
    void removeAndDestroyChild(const std::string&);
    void removeAndDestroyChild(ChildMap::size_type);

    void addChild(SceneNode* const);
    void removeAllChildren();
    void removeChild(const SceneNode* const);
    SceneNode* removeChild(const std::string&);
    SceneNode* removeChild(ChildMap::size_type);

    inline ChildMap::size_type getNumChildren() const;
    SceneNode* getChild(const std::string&) const;
    SceneNode* getChild(ChildMap::size_type) const;

    void attachObject(IMovableObject* const);
    void detachAllObjects();
    void detachObject(const IMovableObject* const);
    IMovableObject* detachObject(const std::string&);
    IMovableObject* detachObject(ObjectMap::size_type);

    inline ObjectMap::size_type getNumAttachedObjects() const;
    IMovableObject* getAttachedObject(const std::string&) const;
    IMovableObject* getAttachedObject(ObjectMap::size_type) const;

    inline bool isRoot() const;
    void _notifyRoot();

private:

    SceneNode(const SceneNode&) = delete;
    SceneNode(SceneNode&&) = delete;
    SceneNode& operator=(const SceneNode&) = delete;
    SceneNode& operator=(SceneNode&&) = delete;

    void setInSceneGraph(bool);

    bool m_isRootSceneNode {false};
    SceneManager* const m_creator;

    ChildMap m_children;
    ObjectMap m_objects;

};

inline SceneNode::ChildMap::size_type SceneNode::getNumChildren() const
{
    return m_children.size();
}

inline SceneNode::ObjectMap::size_type SceneNode::getNumAttachedObjects() const
{
    return m_objects.size();
}

inline bool SceneNode::isRoot() const
{
    return m_isRootSceneNode;
}

}
