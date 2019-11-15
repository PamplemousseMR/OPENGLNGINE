#pragma once

#include <string>

namespace Commun
{

class INameable
{

public:

    INameable();
    INameable(const std::string&);
    virtual ~INameable();

    inline const std::string& getName() const;

protected:

    std::string m_name {""};

};

inline const std::string& INameable::getName() const
{
    return m_name;
}

}
