/* file: linear_regression_training_distributed.h */
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
//  Implementation of the linear regression algorithm interface
//--
*/

#ifndef __LINEAR_REGRESSION_TRAINING_DISTRIBUTED_H__
#define __LINEAR_REGRESSION_TRAINING_DISTRIBUTED_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "services/daal_memory.h"
#include "algorithms/linear_regression/linear_regression_training_types.h"

#include "algorithms/linear_regression/linear_regression_model.h"
#include <typeinfo>

namespace daal
{
namespace algorithms
{
namespace linear_regression
{
namespace training
{

namespace interface1
{
/**
 * \brief Class containing methods for linear regression model-based training in the distributed processing mode
 */
template<ComputeStep step, typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT DistributedContainer
{};

/**
 * \brief Class containing methods for linear regression model-based training
 *  in the first step of the distributed processing mode
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT DistributedContainer<step1Local, algorithmFPType, method, cpu> : public
    TrainingContainerIface<distributed>
{
public:
    /** \brief Constructor */
    DistributedContainer(daal::services::Environment::env *daalEnv);
    ~DistributedContainer();

    /**
     * Computes a partial result of linear regression model-based training
     * in the first step of the distributed processing mode.
     */
    void compute();
    /**
     * Computes the result of linear regression model-based training
     * in the first step of the distributed processing mode.
     */
    void finalizeCompute();
};

/**
 * \brief Class containing methods for linear regression model-based training
 * in the second step of the distributed processing mode
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT DistributedContainer<step2Master, algorithmFPType, method, cpu> : public
    TrainingContainerIface<distributed>
{
public:
    /** \brief Constructor */
    DistributedContainer(daal::services::Environment::env *daalEnv);
    ~DistributedContainer();

    /**
     * Computes a partial result of linear regression model-based training
     * in the second step of the distributed processing mode.
     */
    void compute();
    /**
     * Computes the result of linear regression model-based training
     * in the second step of the distributed processing mode.
     */
    void finalizeCompute();
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__TRAINING__DISTRIBUTED"></a>
 * \brief Provides methods for linear regression model-based training in the distributed processing mode
 *
 * \tparam step             Step of the algorithm in the distributed processing mode, \ref ComputeStep
 * \tparam algorithmFPType  Data type to use in intermediate computations for linear regression model-based training, double or float
 * \tparam method           Linear regression model-based training method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method  Computation methods
 *
 * \par References
 *      - <a href="DAAL-REF-LINEARREGRESSION-ALGORITHM">Linear regression algorithm description and usage models</a>
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref linear_regression::interface1::Model "linear_regression::Model" class
 *      - \ref linear_regression::interface1::ModelNormEq "linear_regression::ModelNormEq" class
 *      - \ref linear_regression::interface1::ModelQR "linear_regression::ModelQR" class
 *      - \ref prediction::interface1::Batch "prediction::Batch" class
 */
template<ComputeStep step, typename algorithmFPType = double, Method method = normEqDense>
class DAAL_EXPORT Distributed : public Training<distributed> {};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__TRAINING__DISTRIBUTED"></a>
 * \brief Performs linear regression model-based training in the the first step of the distributed processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for linear regression
 *                          model-based training, double or float
 * \tparam method           Linear regression training method, \ref Method
 *
 * \par Enumerations
 *      - Method  Computation methods
 *
 * \par References
 *      - <a href="DAAL-REF-LINEARREGRESSION-ALGORITHM">Linear regression algorithm description and usage models</a>
 *      - \ref interface1::Parameter class
 *      - \ref linear_regression::interface1::Model class
 *      - \ref linear_regression::interface1::ModelNormEq class
 *      - \ref linear_regression::interface1::ModelQR class
 *      - \ref prediction::interface1::Batch class
 */
template<typename algorithmFPType, Method method>
class DAAL_EXPORT Distributed<step1Local, algorithmFPType, method> : public Training<distributed>
{
public:
    /** Default constructor */
    Distributed()
    {
        initialize();
    }

    /**
     * Constructs a linear regression training algorithm in the first step of the distributed processing mode
     * by copying input objects and parameters of another linear regression training algorithm
     * \param[in] other Algorithm to use as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Distributed(const Distributed<step1Local, algorithmFPType, method> &other)
    {
        initialize();
        input.set(data,               other.input.get(data));
        input.set(dependentVariables, other.input.get(dependentVariables));
        parameter = other.parameter;
    }

    ~Distributed() {}

    /**
    * Returns the method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Registers user-allocated memory to store a partial result of linear regression model-based training
     * \param[in] partialResult    Structure to store a partial result of linear regression model-based training
     */
    void setPartialResult(services::SharedPtr<PartialResult> partialResult)
    {
        _partialResult = partialResult;
        _pres = _partialResult.get();
    }

    /**
     * Returns the structure that contains a partial result of linear regression model-based training
     * \return Structure that contains a partial result of linear regression model-based training
     */
    services::SharedPtr<PartialResult> getPartialResult() { return _partialResult; }

    /**
     * Registers user-allocated memory to store the result of linear regression model-based training
     * \param[in] res    Structure to store the result of linear regression model-based training
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns the structure that contains the result of linear regression model-based training
     * in the first step of the distributed processing mode
     * \return Structure that contains the result of linear regression model-based training
     * in the first step of the distributed processing mode
     */
    services::SharedPtr<Result> getResult() { return _result; }

    /**
     * Returns a pointer to a newly allocated linear regression training algorithm
     * with a copy of the input objects and parameters of this linear regression training algorithm
     * in the first step of the distributed processing mode
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Distributed<step1Local, algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Distributed<step1Local, algorithmFPType, method> >(cloneImpl());
    }

    DistributedInput<step1Local> input;  /*!< %Input data structure */
    Parameter parameter; /*!< Training parameters */

protected:
    services::SharedPtr<PartialResult> _partialResult;
    services::SharedPtr<Result> _result;

    virtual Distributed<step1Local, algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Distributed<step1Local, algorithmFPType, method>(*this);
    }

    void allocateResult()
    {
        _result->allocate<algorithmFPType>(_pres, &parameter, method);
        _res = _result.get();
    }

    void allocatePartialResult()
    {
        _partialResult->allocate<algorithmFPType>(&input, &parameter, method);
        _pres = _partialResult.get();
    }

    void initializePartialResult() {}

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(distributed, DistributedContainer, step1Local, algorithmFPType, method)(&_env);
        _in = &input;
        _par = &parameter;
        _partialResult = services::SharedPtr<PartialResult>(new PartialResult());
        _result = services::SharedPtr<Result>(new Result());
    }

}; // class  : public Training

/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__TRAINING__DISTRIBUTED"></a>
 * \brief Performs linear regression model-based training in the the second step of distributed processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for linear regression model-based training, double or float
 * \tparam method           Linear regression training method, \ref Method
 *
 * \par Enumerations
 *      - Method  Computation methods
 *
 * \par References
 *      - <a href="DAAL-REF-LINEARREGRESSION-ALGORITHM">Linear regression algorithm description and usage models</a>
 *      - \ref interface1::Parameter class
 *      - \ref linear_regression::interface1::Model class
 *      - \ref linear_regression::interface1::ModelNormEq class
 *      - \ref linear_regression::interface1::ModelQR class
 *      - \ref prediction::interface1::Batch class
 */
template<typename algorithmFPType, Method method>
class DAAL_EXPORT Distributed<step2Master, algorithmFPType, method> : public Training<distributed>
{
public:
    /** Default constructor */
    Distributed()
    {
        initialize();
    }

    /**
     * Constructs a linear regression training algorithm in the second step of the distributed processing mode
     * by copying input objects and parameters of another linear regression training algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Distributed(const Distributed<step2Master, algorithmFPType, method> &other)
    {
        initialize();
        input.set(partialModels, other.input.get(partialModels));
        parameter = other.parameter;
    }

    ~Distributed() {}

    /**
    * Returns the method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Registers user-allocated memory to store a partial result of linear regression model-based training
     * \param[in] partialResult    Structure to store a partial result of linear regression model-based training
     */
    void setPartialResult(services::SharedPtr<PartialResult> partialResult)
    {
        _partialResult = partialResult;
        _pres = _partialResult.get();
    }

    /**
     * Returns the structure that contains a partial result of linear regression model-based training
     * \return Structure that contains a partial result of linear regression model-based training
     */
    services::SharedPtr<PartialResult> getPartialResult() { return _partialResult; }

    /**
     * Registers user-allocated memory to store the result of linear regression model-based training
     * \param[in] res    Structure to store the result of linear regression model-based training
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns the structure that contains the result of linear regression model-based training
     * in the second step of the distributed processing mode
     * \return Structure that contains the result of linear regression model-based training
     * in the second step of the distributed processing mode
     */
    services::SharedPtr<Result> getResult() { return _result; }

    /**
     * Returns a pointer to a newly allocated linear regression training algorithm
     * with a copy of the input objects and parameters of this linear regression training algorithm
     * in the second step of the distributed processing mode
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Distributed<step2Master, algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Distributed<step2Master, algorithmFPType, method> >(cloneImpl());
    }

    DistributedInput<step2Master> input; /*!< %Input data structure */
    Parameter parameter; /*!< Training parameters */

protected:
    services::SharedPtr<PartialResult> _partialResult;
    services::SharedPtr<Result> _result;

    virtual Distributed<step2Master, algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Distributed<step2Master, algorithmFPType, method>(*this);
    }

    void allocateResult()
    {
        _result->allocate<algorithmFPType>(_pres, &parameter, method);
        _res = _result.get();
    }

    void allocatePartialResult()
    {
        _partialResult->allocate<algorithmFPType>(&input, &parameter, method);
        _pres = _partialResult.get();
    }
    void initializePartialResult() {}

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(distributed, DistributedContainer, step2Master, algorithmFPType, method)(&_env);
        _in = &input;
        _par = &parameter;
        _partialResult = services::SharedPtr<PartialResult>(new PartialResult());
        _result = services::SharedPtr<Result>(new Result());
    }

}; // class  : public Training
} // namespace interface1
using interface1::DistributedContainer;
using interface1::Distributed;

}
}
}
}
#endif
