/* file: collection.h */
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

#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <new>
#include "data_management/data/data_serialize.h"
#include "services/daal_shared_ptr.h"
#include "services/error_id.h"

namespace daal
{
namespace services
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 *  <a name="DAAL-CLASS-COLLECTION"></a>
 *  \brief   Class that implements functionality of the Collection container
 *  \tparam  T  Type of an object stored in the container
 */
template<class T>
class Collection
{
public:
    /**
     *  Default constructor. Sets the size and capacity to 0.
     */
    Collection() : _array(NULL), _size(0), _capacity(0)
    {}

    /**
     *  Constructor. Creates a collection with n empty elements
     *  \param[in] n Number of elements
     */
    Collection(size_t n) : _array(NULL), _size(0), _capacity(0)
    {
        resize(n);
        _size = n;
    }

    /**
     *  Copy constructor
     *  \param[in] other Copied collection
     */
    Collection(const Collection<T> &other) : _array(NULL), _size(0), _capacity(0)
    {
        resize(other.capacity());
        for(size_t i = 0; i < other.size(); i++)
        {
            this->push_back(other[i]);
        }
    }

    Collection &operator = (const Collection<T> &other)
    {
        resize(other.capacity());
        for(size_t i = 0; i < other.size(); i++)
        {
            this->push_back(other[i]);
        }
        return *this;
    }

    /**
     *  Destructor
     */
    virtual ~Collection()
    {
        for(size_t i = 0; i < _capacity; i++)
        {
            _array[i].~T();
        }

        services::daal_free(_array);
    }

    /**
     *  Size of a collection
     *  \return Size of the collection
     */
    size_t size() const {return _size;}

    /**
     *  Size of an allocated storage
     *  \return Size of the allocated storage
     */
    size_t capacity() const {return _capacity;}

    /**
     *  Element access
     *  \param[in] index Index of an accessed element
     *  \return    Reference to the element
     */
    T &operator [] (size_t index) const
    {
        return _array[index];
    }

    /**
     *  Element access
     *  \param[in] index Index of an accessed element
     *  \return    Reference to the element
     */
    T &get(size_t index) const
    {
        return _array[index];
    }


    /**
     *  Adds an element to the end of a collection
     *  \param[in] x Element to add
     */
    Collection &push_back(const T &x)
    {
        if(_size >= _capacity)
        {
            _resize();
        }
        _array[_size] = x;
        _size++;

        return *this;
    }

    /**
     *  Adds an element to the end of a collection
     *  \param[in] x Element to add
     */
    void operator << (const T &x)
    {
        this->push_back(x);
    }

    /**
     *  Changes the size of a storage
     *  \param[in] newCapacity Size of a new storage.
     */
    void resize(size_t newCapacity)
    {
        if(newCapacity <= _capacity) { return; }
        T *newArray = (T *)services::daal_malloc(sizeof(T) * newCapacity);
        for(size_t i = 0; i < newCapacity; i++)
        {
            T *elementMemory = &(newArray[i]);
            ::new(elementMemory) T;
        }

        size_t minSize = newCapacity < _size ? newCapacity : _size;
        for(size_t i = 0; i < minSize; i++)
        {
            newArray[i] = _array[i];
        }

        for(size_t i = 0; i < _capacity; i++)
        {
            _array[i].~T();
        }

        services::daal_free(_array);
        _array = newArray;
        _capacity = newCapacity;
    }

    /**
     *  Clears a collection: removes an array, sets the size and capacity to 0
     */
    void clear()
    {
        for(size_t i = 0; i < _capacity; i++)
        {
            _array[i].~T();
        }

        services::daal_free(_array);

        _array = NULL;
        _size = 0;
        _capacity = 0;
    }

    /**
     *  Insert an element into a position
     *  \param[in] pos Position to set
     *  \param[in] x   Element to set
     */
    void insert(const size_t pos, const T &x)
    {
        if(pos > this->size())
        {
            _error.setErrorID(ErrorIncorrectIndex);
            return;
        }

        size_t newSize = 1 + this->size();
        if(newSize > _capacity)
        {
            _resize();
        }

        size_t tail = _size - pos;
        for(size_t i = 0; i < tail; i++)
        {
            _array[_size - i] = _array[_size - 1 - i];
        }
        _array[pos] = x;
        _size = newSize;
    }

    /**
     *  Insert a collection to another collection into a position
     *  \param[in] pos   Position to see
     *  \param[in] other Collection to set
     */
    void insert(const size_t pos, Collection<T> &other)
    {
        if(pos > this->size())
        {
            _error.setErrorID(ErrorIncorrectIndex);
            return;
        }
        size_t newSize = other.size() + this->size();
        if(newSize > _capacity)
        {
            resize(newSize);
        }

        size_t length = other.size();
        size_t tail = _size - pos;
        for(size_t i = 0; i < tail; i++)
        {
            _array[_size + length - 1 - i] = _array[_size - 1 - i];
        }
        for(size_t i = 0; i < length; i++)
        {
            _array[pos + i] = other[i];
        }
        _size = newSize;
    }

    /**
     *  Erase an element from a position
     *  \param[in] pos Position to erase
     */
    void erase(size_t pos)
    {
        if(pos >= this->size())
        {
            _error.setErrorID(ErrorIncorrectIndex);
            return;
        }

        _size--;

        for(int i = 0; i < _size - pos; i++)
        {
            _array[pos + i] = _array[pos + 1 + i];
        }
        T element;
        _array[_size] = element;
    }

    ErrorID getErrorID() { return _error.getErrorID(); }

    void setErrorID(const ErrorID &errorID) { _error.setErrorID(errorID); }

private:
    static const size_t _default_capacity = 16;
    void _resize()
    {
        size_t newCapacity = 2 * _capacity;
        if(_capacity == 0) { newCapacity = _default_capacity; }
        resize(newCapacity);
    }

protected:
    T *_array;
    size_t _size;
    size_t _capacity;

    SingleError _error;
};
} // namespace interface1
using interface1::Collection;

} // namespace services
} // namespace daal

#endif
