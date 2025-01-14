/* file: algorithm_quality_metric_set_types.h */
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
//  Interface for the quality metric set.
//--
*/

#ifndef __ALGORITHM_QUALITY_METRIC_SET_TYPES_H__
#define __ALGORITHM_QUALITY_METRIC_SET_TYPES_H__

#include "services/collection.h"
#include "algorithms/algorithm_quality_metric_batch.h"

namespace daal
{
namespace algorithms
{
namespace quality_metric_set
{

/**
 * \brief Contains version 1.0 of the Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__QUALITY_METRIC_SET__INPUTALGORITHMSCOLLECTION"></a>
 * \brief Class that implements functionality of the collection of quality metrics algorithms
 */
class InputAlgorithmsCollection
{
public:
    /**
     * Constructs the collection of quality metrics algorithms
     * \param[in] n     Number of elements in the collection
     */
    InputAlgorithmsCollection(size_t n = 0) : _qualityMetrics(n), _keys(n)
    {
        nullPtr = new services::SharedPtr<quality_metric::Batch>();
    }

    virtual ~InputAlgorithmsCollection()
    {
        delete nullPtr;
    }

    /**
     * Returns a reference to SharedPtr for a stored object with a given key if an object with such key is registered
     * \param[in] k     Key value
     * \return Reference to SharedPtr of the quality_metric::Batch type
     */
    services::SharedPtr<quality_metric::Batch>& operator[](size_t k) const
    {
        size_t i;
        for (i = 0; i < _keys.size(); i++)
        {
            if (_keys[i] == k)
            {
                return _qualityMetrics[i];
            }
        }
        return *nullPtr;
    }

    /**
     * Returns a reference to SharedPtr for a stored object with a given key if an object with such key is registered.
     * Otherwise, creates an empty SharedPtr and stores it under the requested key and returns a reference for this value
     * \param[in] k     Key value
     * \return Reference to SharedPtr of the quality_metric::Batch type
     */
    services::SharedPtr<quality_metric::Batch>& operator[](size_t k)
    {
        size_t i;
        for (i = 0; i < _keys.size(); i++)
        {
            if (_keys[i] == k)
            {
                return _qualityMetrics[i];
            }
        }
        _keys.push_back(0);
        _keys[i] = k;
        _qualityMetrics.push_back(services::SharedPtr<quality_metric::Batch>());
        return _qualityMetrics[i];
    }

    /**
     *  Returns the number of stored elements
     *  \return number of stored elements
     */
    size_t size() const { return _qualityMetrics.size(); };

    /**
     * Removes all elements from the container
     */
    void clear()
    {
        _keys.clear();
        _qualityMetrics.clear();
    }

    /**
     *  Returns a reference to SharedPtr for the stored key with a given index
     *  \param[in]  idx  Index of the requested key
     *  \return Reference to SharedPtr of the size_t type
     */
    size_t getKeyByIndex(int idx)
    {
        return _keys[idx];
    }

protected:
    services::Collection<services::SharedPtr<quality_metric::Batch> > _qualityMetrics;
    services::Collection<size_t> _keys;
    services::SharedPtr<quality_metric::Batch> *nullPtr;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__QUALITY_METRIC_SET__INPUTDATACOLLECTION"></a>
 * \brief Class that implements functionality of the collection of input objects of the quality metrics algorithm
 */
class InputDataCollection : public data_management::KeyValueDataCollection
{
public:
    InputDataCollection() : data_management::KeyValueDataCollection() {}

    /**
     * Adds an element with a key to the collection
     * \param[in] k     Key value
     * \param[in] ptr   Shared pointer to the element
     */
    void add(size_t k, const services::SharedPtr<algorithms::Input>& ptr)
    {
        (*this)[k] = ptr;
    }

    /**
     * Returns the element that matches the key
     * \param[in] key     Key value
     * \return Shared pointer to the element
     */
    services::SharedPtr<algorithms::Input> getInput(size_t key) const
    {
        return services::staticPointerCast<algorithms::Input, data_management::SerializationIface>((*this)[key]);
    }

    virtual ~InputDataCollection() {}
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__QUALITY_METRIC_SET__RESULTCOLLECTION"></a>
 * \brief Class that implements functionality of the collection of result objects of the quality metrics algorithm
 */
class ResultCollection : public data_management::KeyValueDataCollection
{
public:
    ResultCollection() : data_management::KeyValueDataCollection() {}

    void add(size_t key, const services::SharedPtr<algorithms::Result>& ptr)
    {
        (*this)[key] = ptr;
    }

    services::SharedPtr<algorithms::Result> getResult(size_t key) const
    {
        return services::staticPointerCast<algorithms::Result, data_management::SerializationIface>(this->operator[](key));
    }

    virtual ~ResultCollection() {}
};
} // namespace interface1
using interface1::InputAlgorithmsCollection;
using interface1::InputDataCollection;
using interface1::ResultCollection;

} // namespace quality_metric_set
} // namespace algorithms
} // namespace daal
#endif
