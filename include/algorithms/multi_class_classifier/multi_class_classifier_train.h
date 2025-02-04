/* file: multi_class_classifier_train.h */
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
//  Implementation of Multi-class classifier training algorithm interface.
//--
*/

#ifndef __MULTI_CLASS_CLASSIFIER_TRAIN_H__
#define __MULTI_CLASS_CLASSIFIER_TRAIN_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/classifier/classifier_training_batch.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_train_types.h"

namespace daal
{
namespace algorithms
{
namespace multi_class_classifier
{
/**
 * \brief Contains classes for training the multi-class classifier model
 */
namespace training
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTI_CLASS_CLASSIFIER__TRAINING__BATCHCONTAINER"></a>
 *  \brief Class containing methods to compute the results of the multi-class classifier training algorithm
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the multi-class classifier, double or float
 * \tparam method           Computation method of the algprithm, \ref daal::algorithms::multi_class_classifier::training::Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public TrainingContainerIface<batch>
{
public:
    /** \brief Constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTI_CLASS_CLASSIFIER__TRAINING__BATCH"></a>
 * \brief Algorithm for the multi-class classifier model training
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the multi-class classifier training algorithm, double or float
 * \tparam method           Computation method for the algorithm, \ref Method
 *
 * \par Enumerations
 *      - \ref Method   Multi-class classifier training methods
 *      - \ref classifier::training::InputId  Identifiers of input objects for the multi-class classifier algprithm
 *      - \ref classifier::training::ResultId Identifiers of multi-class classifier training results
 *
 * \par References
 *      - <a href="DAAL-REF-MULTICLASSCLASSIFIER-ALGORITHM">Multi-class classifier algorithm description and usage models</a>
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref interface1::Model "Model" class
 *      - \ref classifier::training::interface1::Input "classifier::training::Input" class
 *      - Result class
 */
template<typename algorithmFPType = double, Method method = oneAgainstOne>
class DAAL_EXPORT Batch : public classifier::training::Batch
{
public:
    /** Default constructor */
    Batch() : parameter(0)
    {
        initialize();
    }

    /**
     * Constructs multi-class classifier training algorithm by copying input objects and parameters
     * of another multi-class classifier training algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other) : classifier::training::Batch(other), parameter(0)
    {
        initialize();
        parameter = other.parameter;
    }

    ~Batch() {}

    /**
     * Returns method of the algorithm
     * \return Method of the algorithm
     */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Registers user-allocated memory to store the results of the multi-class classifier algorithm
     * \param[in] res    Structure for storing the training results of the multi-class classifier algorithm
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns the structure that contains the training results of the multi-class classifier algorithm
     * \return Structure that contains the training results of the multi-class classifier algorithm
     */
    services::SharedPtr<Result> getResult()
    {
        return services::staticPointerCast<Result, classifier::training::Result>(_result);
    }

    /**
     * Resets the training results of the classification algorithm
     */
    void resetResult()
    {
        _result = services::SharedPtr<Result>(new Result());
        _res = NULL;
    }

    /**
     * Returns a pointer to the newly allocated multi-class classifier training algorithm
     * with a copy of input objects and parameters of this multi-class classifier training algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    Parameter parameter;    /*!< Parameters of the algorithm */

protected:
    virtual Batch<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void allocateResult()
    {
        services::SharedPtr<Result> res = services::staticPointerCast<Result, classifier::training::Result>(_result);
        res->template allocate<algorithmFPType>(&input, _par, method);
        _res = _result.get();
    }

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _par = &parameter;
        _result = services::SharedPtr<Result>(new Result());
    }
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // namespace training
} // namespace multi_class_classifier
} // namespace algorithms
} //namespace daal
#endif
