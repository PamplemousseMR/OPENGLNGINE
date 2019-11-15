#include "Commun/INameable.hpp"

#include <sstream>
#include <cassert>

using namespace std;

namespace Commun
{

INameable::INameable()
{
    ostringstream address;
    address << (const void*)this;
    m_name = address.str();
}

INameable::INameable(const string& _name):
    m_name(_name)
{
    assert(!_name.empty() && "The name of a nameable object can't be empty");
}

INameable::~INameable()
{
}

}
