#pragma once

#include <iostream>

namespace Commun
{

template<typename T>
class IPrintable
{

public:

    IPrintable();
    virtual ~IPrintable();

    virtual std::ostream& print(std::ostream&) const = 0;

    friend std::ostream& operator<<(std::ostream& _o, const T& _p)
    {
        _p.print(_o);
        return _o;
    }

};

template<typename T>
IPrintable<T>::IPrintable()
{
}

template<typename T>
IPrintable<T>::~IPrintable()
{
}

}
