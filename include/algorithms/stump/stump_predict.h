/* file: stump_predict.h */
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
//  Implementation of the interface of the decision stump prediction algorithm.
//--
*/

#ifndef __STUMP_PREDICT_H__
#define __STUMP_PREDICT_H__

#include "algorithms/algorithm.h"
#include "algorithms/weak_learner/weak_learner_predict.h"

namespace daal
{
namespace algorithms
{
namespace stump
{
/**
 * \brief Contains classes to make prediction based on the decision stump model
 */
namespace prediction
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__STUMP__PREDICTION__METHOD"></a>
 * Available methods to make prediction based on the decision stump model
 */
enum Method
{
    defaultDense = 0        /*!< Default method */
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__STUMP__PREDICTION__PREDICTIONCONTAINER"></a>
 * \brief Provides methods to run implementations of the decision stump prediction algorithm.
 *        It is associated with the daal::algorithms::stump::prediction::Batch class
 *        and supports methods to run based on the decision stump model
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the decision stump prediction algorithm, double or float
 * \tparam method           Decision stump model-based prediction method, \ref Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT PredictionContainer : public PredictionContainerIface
{
public:
    PredictionContainer(daal::services::Environment::env *daalEnv);
    ~PredictionContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__STUMP__PREDICTION__BATCH"></a>
 * \brief Predicts results of the decision stump classification
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the decision stump prediction algorithm, double or float
 * \tparam method           Decision stump model-based prediction method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method                                       Decision stump prediction methods
 *      - \ref classifier::prediction::NumericTableInputId  Identifiers of input Numeric Table objects
 *                                                          for the decision stump prediction algorithm
 *      - \ref classifier::prediction::ModelInputId         Identifiers of input %Model objects
 *                                                          for the decision stump prediction algorithm
 *      - \ref classifier::prediction::ResultId             Identifiers of the results of the decision stump prediction algorithm
 *
 * \par References
 *      - \ref interface1::Model "Model" class
 *      - \ref classifier::prediction::interface1::Input "classifier::prediction::Input" class
 *      - \ref classifier::prediction::interface1::Result "classifier::prediction::Result" class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class Batch : public weak_learner::prediction::Batch
{
public:
    Batch()
    {
        initialize();
    }

    /**
     * Constructs decision stump classification algorithm by copying input objects
     * of another decision stump classification algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other) : weak_learner::prediction::Batch(other)
    {
        initialize();
    }

    ~Batch() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Returns a pointer to the newly allocated decision stump classification algorithm
     * with a copy of input objects and parameters of this decision stump classification algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

protected:
    using weak_learner::prediction::Batch::_result;

    virtual Batch<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void allocateResult()
    {
        _result->allocate<algorithmFPType>(&input, 0, 0);
        _res = _result.get();
    }

    void initialize()
    {
        _ac  = new __DAAL_ALGORITHM_CONTAINER(batch, PredictionContainer, algorithmFPType, method)(&_env);
        _par = NULL;
    }
};
} // namespace interface1
using interface1::PredictionContainer;
using interface1::Batch;

} // namespace daal::algorithms::stump::prediction
}
}
} // namespace daal
#endif
