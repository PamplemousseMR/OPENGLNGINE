#include "Scene/IMovableObject.hpp"

using namespace std;

namespace Scene
{

IMovableObject::IMovableObject():
    IMovable()
{
}

IMovableObject::IMovableObject(const string& _name):
    IMovable(_name)
{
}

IMovableObject::~IMovableObject()
{
}

}
