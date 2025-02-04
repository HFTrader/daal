/* file: multi_class_classifier_predict.h */
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
//  Implementation of Multi-class classifier prediction algorithm interface.
//--
*/

#ifndef __MULTI_CLASS_CLASSIFIER_PREDICT_H__
#define __MULTI_CLASS_CLASSIFIER_PREDICT_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/classifier/classifier_predict.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_predict_types.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_train_types.h"

namespace daal
{
namespace algorithms
{
namespace multi_class_classifier
{
/**
 * \brief Contains classes for prediction based on multi-class classifier models
 */
namespace prediction
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTI_CLASS_CLASSIFIER__PREDICTION__PREDICTIONCONTAINER"></a>
 * \brief Provides methods to run implementations of the  multi-class classifier prediction algorithm
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the multi-class classifier algorithm, double or float
 * \tparam pmethod          Computation method for the algorithm, \ref prediction::Method
 * \tparam tmethod          Computation method that was used to train the multi-class classifier model, \ref training::Method
 */
template<typename algorithmFPType, prediction::Method pmethod, training::Method tmethod, CpuType cpu>
class DAAL_EXPORT PredictionContainer : public PredictionContainerIface
{
public:
    PredictionContainer(daal::services::Environment::env *daalEnv);
    ~PredictionContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTI_CLASS_CLASSIFIER__PREDICTION__PREDICTION"></a>
 *  \brief Provides methods to run implementations of the multi-class classifier prediction algorithm
 *
 *  \tparam algorithmFPType  Data type to use in intermediate computations for multi-class classifier prediction algorithm, double or float
 *  \tparam pmethod          Computation method for the algorithm, \ref prediction::Method
 *  \tparam tmethod          Computation method that was used to train the multi-class classifier model, \ref training::Method
 *
 *  \par Enumerations
 *      - \ref Method Computation methods for the multi-class classifier prediction algorithm
 *      - \ref classifier::prediction::NumericTableInputId  Identifiers of input NumericTable objects
 *                                                          for the multi-class classifier prediction algorithm
 *      - \ref classifier::prediction::ModelInputId         Identifiers of input Model objects
 *                                                          for the multi-class classifier prediction algorithm
 *      - \ref classifier::prediction::ResultId             Identifiers of the results of the multi-class classifier prediction algorithm
 *
 * \par References
 *      - <a href="DAAL-REF-MULTICLASSCLASSIFIER-ALGORITHM">Multi-class classifier algorithm description and usage models</a>
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref interface1::Model "Model" class
 *      - \ref classifier::prediction::interface1::Input "classifier::prediction::Input" class
 *      - \ref classifier::prediction::interface1::Result "classifier::prediction::Result" class
 */
template<typename algorithmFPType = double, prediction::Method pmethod = defaultDense, training::Method tmethod = training::oneAgainstOne>
class Batch : public classifier::prediction::Batch
{
public:
    /** Default constructor */
    Batch() : parameter(0)
    {
        initialize();
    }

    /**
     * Constructs multi-class classifier prediction algorithm by copying input objects and parameters
     * of another multi-class classifier prediction algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, pmethod, tmethod> &other) : classifier::prediction::Batch(other), parameter(0)
    {
        initialize();
        parameter = other.parameter;
    }

    virtual ~Batch() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)pmethod; }

    /**
     * Returns a pointer to the newly allocated multi-class classifier prediction algorithm
     * with a copy of input objects and parameters of this multi-class classifier prediction algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, pmethod, tmethod> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, pmethod, tmethod> >(cloneImpl());
    }

    Parameter parameter;    /*!< Parameters of the algorithm */

protected:

    virtual Batch<algorithmFPType, pmethod, tmethod> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, pmethod, tmethod>(*this);
    }

    void allocateResult()
    {
        _result->allocate<algorithmFPType>(&input, &parameter, (int) pmethod);
        _res = _result.get();
    }

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(batch, PredictionContainer, algorithmFPType, pmethod, tmethod)(&_env);
        _par = &parameter;
    }
};
} // namespace interface1
using interface1::PredictionContainer;
using interface1::Batch;

} // namespace prediction
} // namespace multi_class_classifier
} // namespace algorithms
} // namespace daal
#endif
