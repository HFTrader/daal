/* file: multinomial_naive_bayes_training_online.h */
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
//  Implementation of Naive Bayes algorithm interface
//--
*/

#ifndef __NAIVE_BAYES_TRAINING_ONLINE_H__
#define __NAIVE_BAYES_TRAINING_ONLINE_H__

#include "algorithms/algorithm.h"
#include "multinomial_naive_bayes_training_types.h"
#include "algorithms/classifier/classifier_training_online.h"

namespace daal
{
namespace algorithms
{
namespace multinomial_naive_bayes
{
namespace training
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTINOMIAL_NAIVE_BAYES__TRAINING__ONLINEONTAINER"></a>
 *  \brief Class containing computation methods for naive Bayes training in the online processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the naive Bayes in the online processing mode, double or float
 * \tparam method           Naive Bayes computation method, \ref Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT OnlineContainer : public TrainingContainerIface<online>
{
public:
    /** \brief Constructor */
    OnlineContainer(daal::services::Environment::env *daalEnv);
    ~OnlineContainer();

    /**
     * Computes a partial result of naive Bayes model-based training
     * in the online processing mode.
     */
    void compute();
    /**
     * Computes the result of naive Bayes model-based training
     * in the online processing mode.
     */
    void finalizeCompute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTINOMIAL_NAIVE_BAYES__TRAINING__ONLINE"></a>
 *  \brief Algorithm class for training naive Bayes model
 *
 *  \tparam algorithmFPType  Data type to use in intermediate computations for multinomial naive Bayes training in the online processing mode,
 *                           double or float
 *  \tparam method           Computation method, \ref Method
 *
 *  \par Enumerations
 *      - \ref Method Training methods for the multinomial naive Bayes algorithm
 *
 *  \par References
 *      - <a href="DAAL-REF-MULTINOMNAIVEBAYES-ALGORITHM">Multinomial naive Bayes algorithm description and usage models</a>
 *
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Online : public classifier::training::Online
{
public:

    /**
     * Default constructor
     * \param nClasses  Number of classes
     */
    Online(size_t nClasses) : parameter(nClasses)
    {
        initialize();
    }

    /**
     * Constructs multinomial naive Bayes training algorithm by copying input objects and parameters
     * of another multinomial naive Bayes training algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Online(const Online<algorithmFPType, method> &other) :
        classifier::training::Online(other), parameter(other.parameter.nClasses)
    {
        initialize();
        parameter = other.parameter;
    }

    virtual ~Online() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Returns the structure that contains results of Naive Bayes training
     * \return Structure that contains results of Naive Bayes training
     */
    services::SharedPtr<Result> getResult()
    {
        return services::staticPointerCast<Result, classifier::training::Result>(_result);
    }

    /**
     * Registers user-allocated memory to store results of Naive Bayes training
     * \param[in] result  Structure to store  results of Naive Bayes training
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
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
     * Returns a pointer to the newly allocated multinomial naive Bayes training algorithm
     * with a copy of input objects and parameters of this multinomial naive Bayes training algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Online<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Online<algorithmFPType, method> >(cloneImpl());
    }

    Parameter parameter;                /*!< Parameters of the training */

protected:

    virtual Online<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Online<algorithmFPType, method>(*this);
    }

    void allocateResult()
    {
        services::SharedPtr<PartialResult> pres = services::staticPointerCast<PartialResult, classifier::training::PartialResult>(_partialResult);
        services::SharedPtr<Result> res = services::staticPointerCast<Result, classifier::training::Result>(_result);
        res->template allocate<algorithmFPType>(pres.get(), &parameter, (int)method);
        _res = _result.get();
    }

    void allocatePartialResult()
    {
        services::SharedPtr<PartialResult> pres = services::staticPointerCast<PartialResult, classifier::training::PartialResult>(_partialResult);
        pres->template allocate<algorithmFPType>((classifier::training::InputIface *)(&input), &parameter, (int)method);
        _pres = _partialResult.get();
    }

    void initializePartialResult() {}

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(online, OnlineContainer, algorithmFPType, method)(&_env);
        _par = &parameter;
        _result = services::SharedPtr<Result>(new Result());
        _partialResult = services::SharedPtr<PartialResult>(new PartialResult());
    }
};
} // namespace interface1
using interface1::OnlineContainer;
using interface1::Online;

} // namespace training
} // namespace multinomial_naive_bayes
} // namespace algorithms
} // namespace daal
#endif
