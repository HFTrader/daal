/* file: factory.h */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of service features used by the library components.
//--
*/

#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "services/daal_defines.h"
#include "data_management/data/data_serialize.h"
#include "data_management/data/data_collection.h"

namespace daal
{
namespace data_management
{

namespace interface1
{
/**
 *  <a name="DAAL-CLASS-PAIR"></a>
 *  \brief Pair container
 *  \tparam  FirstType   Type of the first argument in the pair
 *  \tparam  SecondType  Type of the second argument in the pair
 */
template<class FirstType, class SecondType>
class Pair
{
public:
    /**
     *  Constructor
     *  \param[in]  first  Reference to the first element in the pair
     *  \param[in]  second Reference to the second element in the pair
     */
    Pair(const FirstType &first, const SecondType &second) : _first(first), _second(second) {};

    /** \private */
    virtual ~Pair() {};

    /**
     *  Returns the first element in the pair
     *  \return The first element the the pair
     */
    const FirstType first() { return _first; }

    /**
     *  Returns the second element in the pair
     *  \return The second element in the pair
     */
    const SecondType second() { return _second; }

protected:
    FirstType  _first;
    SecondType _second;
};

/**
 *  <a name="DAAL-CLASS-ABSTRACTCREATOR"></a>
 *  \brief Interface class used by the Factory class to register and create objects of a specific class
 */
class AbstractCreator
{
public:
    /** Default constructor */
    AbstractCreator() {}

    /** \private */
    virtual ~AbstractCreator() {}

    /**
     *  Creates a new object of a class
     *  \return Pointer to the new object
     */
    virtual SerializationIface *create() const = 0;

    /**
     *  Returns a unique class identifier associated with a class
     *  \return Class identifier
     */
    virtual int getTag() = 0;
};


/**
 *  <a name="DAAL-CLASS-CREATOR"></a>
 *  \brief Main class used by the Factory class to register and create objects of a class derived from SerializationIface
 *  and the default constructor without arguments
 *  \tparam  Derived  Object of this class is created by the create() function
 */
template <class Derived>
class Creator : public AbstractCreator
{
public:
    /** Default constructor */
    Creator() {}

    /** \private */
    virtual ~Creator() {}

    SerializationIface *create() const DAAL_C11_OVERRIDE
    {
        return new Derived();
    }

    int getTag() DAAL_C11_OVERRIDE
    {
        Derived d;
        return d.getSerializationTag();
    }
};

/**
 *  <a name="DAAL-CLASS-CSRCREATOR"></a>
 *  \brief Class used by the Factory class to register and create objects of a class derived from SerializationIface
 *  and a constructor with one argument of the T* type
 *  \tparam  Derived  Object of this class is created by the create() function
 *  \tparam  T        NULL pointer to the object of this type is used as the constructor argument
 */
template <class Derived, typename T>
class CSRCreator : public AbstractCreator
{
public:
    /** Default constructor */
    CSRCreator() {}

    virtual ~CSRCreator() {}

    SerializationIface *create() const DAAL_C11_OVERRIDE
    {
        T *ptr = NULL;
        return new Derived(ptr);
    }

    int getTag() DAAL_C11_OVERRIDE
    {
        T *ptr = NULL;
        Derived d(ptr);
        return d.getSerializationTag();
    }
};

/**
 *  <a name="DAAL-CLASS-FACTORY"></a>
 *  \brief Class that provides factory functionality for objects implementing the SerializationIface interface.
 *  Used within deserialization functionality.
 */
class DAAL_EXPORT Factory
{
public:
    /**
     *  Static function that returns an instance of the Factory class
     *  \return Reference to the Factory object
     */
    static Factory &instance();

    /**
     *  Registers the %Creator object for an additional class
     *  \param[in]  creator  Object that implements the AbstractCreator interface to create an instance of a class
     */
    void registerObject(AbstractCreator *creator);

    /**
     *  Creates a new object of a class described by an identifier
     *  \param[in]  objectId  Identifier of the class
     */
    SerializationIface *createObject(int objectId);

private:
    Factory();
    Factory(const Factory &);
    Factory &operator = (const Factory &);
    ~Factory();

    typedef Pair<int, AbstractCreator *> AbstractCreatorPair;

    class FactoryList : public services::Collection<services::SharedPtr<AbstractCreatorPair> >
    {
    public:
        int find(int id)
        {
            for(size_t i = 0; i < size(); i++)
            {
                if(_array[i]->first() == id)
                {
                    return (int)i;
                }
            }
            return -1;
        }
    };

    typedef FactoryList MapType;
    MapType _map;
};
} // namespace interface1
using interface1::Pair;
using interface1::AbstractCreator;
using interface1::Creator;
using interface1::CSRCreator;
using interface1::Factory;

}
} // namespace daal
#endif
