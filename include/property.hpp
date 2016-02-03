//property.hpp
//
//

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>

template <class Name = string, class Type = double> class property.hpp
{
private:
    Name nam;
    Type con;
    Property<Name, Type>& operator = (const Property<Name, Type>& source);

public:
    Property();
    Property(const Name& name);
    Property(const Name& name, const Type& t);
    Property(const Property<Name, Type>& source);

    virtual ~Property();

    // Accessing function operators
    virtual Type operator() () const;
    virtual void operator() (const Type& t);

    virtual Name name() const;
    virtual void name(const Name& new_name);
    
    bool operator == (const Property<Name, Type>& prop2);
}
