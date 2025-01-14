/* file: svm_predict.h */
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
//  Implementation of the SVM prediction algorithm interface.
//--
*/

#ifndef __SVM_PREDICT_H__
#define __SVM_PREDICT_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "algorithms/classifier/classifier_predict.h"
#include "algorithms/svm/svm_predict_types.h"

namespace daal
{
namespace algorithms
{
namespace svm
{
namespace prediction
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__SVM__PREDICTION__PREDICTIONCONTAINER"></a>
 * \brief Provides methods to run implementations of the SVM algorithm.
 *        It is associated with the Prediction class
 *        and supports methods to run predictions based on the SVM model
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the SVM prediction algorithm, double or float
 * \tparam method           SVM model-based prediction method, \ref Method
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
 * <a name="DAAL-CLASS-ALGORITHMS__SVM__PREDICTION__BATCH"></a>
 * \brief %Algorithm class for making predictions based on the SVM model
 *
 * \par Enumerations
 *      - \ref Method                                       Prediction methods
 *      - \ref classifier::prediction::NumericTableInputId  Input Numeric Table objects
 *                                                          for the SVM prediction algorithm
 *      - \ref classifier::prediction::ModelInputId         Identifiers of input Model objects
 *                                                          for the SVM prediction algorithm
 *      - \ref classifier::prediction::ResultId             Identifiers of prediction results
 *
 * \par References
 *      - <a href="DAAL-REF-SVM-ALGORITHM">SVM algorithm description and usage models</a>
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref interface1::Input "Input" class
 *      - \ref interface1::Model "Model" class
 *      - \ref interface1::Result "Result" class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class Batch : public classifier::prediction::Batch
{
public:
    /** Default constructor */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs an SVM prediction algorithm by copying input objects and parameters
     * of another SVM prediction algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other) : classifier::prediction::Batch(other)
    {
        initialize();
        parameter = other.parameter;
    }

    virtual ~Batch() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    Parameter parameter;

    /**
     * Returns a pointer to the newly allocated SVM prediction algorithm with a copy of input objects
     * and parameters of this SVM prediction algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

protected:

    virtual Batch<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void allocateResult() DAAL_C11_OVERRIDE
    {
        _result->allocate<algorithmFPType>(&input, 0, 0);
        _res = _result.get();
    }

    void initialize()
    {
        _ac  = new __DAAL_ALGORITHM_CONTAINER(batch, PredictionContainer, algorithmFPType, method)(&_env);
        _par = &parameter;
    }
};
} // namespace interface1
using interface1::PredictionContainer;
using interface1::Batch;

} // namespace prediction
} // namespace svm
} // namespace algorithms
} // namespace daal
#endif
