/* file: covariance_online.h */
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
//  Implementation of Covariance Online algorithm interface.
//--
*/

#ifndef __COVARIANCE_ONLINE_H__
#define __COVARIANCE_ONLINE_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/covariance/covariance_types.h"

namespace daal
{
namespace algorithms
{
namespace covariance
{

namespace interface1
{
/**
* <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__ONLINECONTAINER"></a>
* \brief Class that spcifies interfaces of implementations of the correlation or variance-covariance matrix algorithm.
*        This class is associated with daal::algorithms::covariance::OnlineIface class
*
* \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
* \tparam method           Computation method of the algorithm, \ref daal::algorithms::covariance::Method
*/
class OnlineContainerIface : public daal::algorithms::AnalysisContainerIface<online>
{
public:
    OnlineContainerIface() {};
    virtual ~OnlineContainerIface() {}

    /**
     * Runs the  correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute() = 0;

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute() = 0;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__ONLINECONTAINER"></a>
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam method           Computation method for correlation or variance-covariance matrix, \ref daal::algorithms::covariance::Method
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT OnlineContainer
{};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using default computation method.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT OnlineContainer<algorithmFPType, defaultDense, cpu> : public OnlineContainerIface
{
public:
    OnlineContainer(daal::services::Environment::env *daalEnv);
    virtual ~OnlineContainer();

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute();
    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using single-pass computation method.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT OnlineContainer<algorithmFPType, singlePassDense, cpu> : public OnlineContainerIface
{
public:
    OnlineContainer(daal::services::Environment::env *daalEnv);
    virtual ~OnlineContainer();

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute();
    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using sum computation method.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT OnlineContainer<algorithmFPType, sumDense, cpu> : public OnlineContainerIface
{
public:
    OnlineContainer(daal::services::Environment::env *daalEnv);
    virtual ~OnlineContainer();

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute();
    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using fast computation method that works with Compressed Sparse Rows (CSR) numeric tables.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT OnlineContainer<algorithmFPType, fastCSR, cpu> : public OnlineContainerIface
{
public:
    OnlineContainer(daal::services::Environment::env *daalEnv);
    virtual ~OnlineContainer();

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute();
    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using single-pass computation method that works with Compressed Sparse Rows (CSR) numeric tables.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT OnlineContainer<algorithmFPType, singlePassCSR, cpu> : public OnlineContainerIface
{
public:
    OnlineContainer(daal::services::Environment::env *daalEnv);
    virtual ~OnlineContainer();

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute();
    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using precomputed sum computation method that works with Compressed Sparse Rows (CSR) numeric tables.
 *        This class is associated with daal::algorithms::covariance::Online class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT OnlineContainer<algorithmFPType, sumCSR, cpu> : public OnlineContainerIface
{
public:
    OnlineContainer(daal::services::Environment::env *daalEnv);
    virtual ~OnlineContainer();

    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute a partial result.
     */
    virtual void compute();
    /**
     * Runs the correlation or variance-covariance matrix algorithm
     * in the online processing mode to compute the result.
     */
    virtual void finalizeCompute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__ONLINEIFACE"></a>
 * \brief Abstract class that specifies interface of the algorithms
 *        for computing correlation or variance-covariance matrix in the online processing mode
 */
class DAAL_EXPORT OnlineIface : public daal::algorithms::Analysis<online>
{
public:
    /** Default constructor */
    OnlineIface()
    {
        initialize();
    }

    /**
     * Constructs an algorithm for correlation or variance-covariance matrix computation
     * by copying input objects and parameters of another algorithm for correlation or variance-covariance
     * matrix computation
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    OnlineIface(const OnlineIface &other)
    {
        initialize();
        input.set(data, other.input.get(data));
        parameter = other.parameter;
    }

    virtual ~OnlineIface() {}

    /**
     * Returns the structure that contains final results of the correlation or variance-covariance matrix algorithm
     * \return Structure that contains the final results
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store final results of the correlation or variance-covariance matrix algorithm
     * \param[in] result    Structure to store the results
     */
    virtual void setResult(const services::SharedPtr<Result> &result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns the structure that contains partial results of the correlation or variance-covariance matrix algorithm
     * \return Structure that contains partial results
     */
    services::SharedPtr<PartialResult> getPartialResult()
    {
        return _partialResult;
    }

    /**
     * Registers user-allocated memory to store partial results of the correlation or variance-covariance matrix algorithm
     * \param[in] partialResult    Structure to store partial results
     * \param[in] _initFlag        Flag that specifies whether the partial results are initialized
     */
    virtual void setPartialResult(const services::SharedPtr<PartialResult> &partialResult, bool _initFlag = false)
    {
        _partialResult = partialResult;
        _pres = _partialResult.get();
        setInitFlag(_initFlag);
    }

    /**
     * Returns a pointer to the newly allocated algorithm for correlation or variance-covariance matrix computation
     * with a copy of input objects and parameters of this algorithm for correlation or variance-covariance
     * matrix computation
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<OnlineIface> clone() const
    {
        return services::SharedPtr<OnlineIface>(cloneImpl());
    }

    Input input;                  /*!< %Input data structure */
    OnlineParameter parameter;    /*!< %Parameter structure */

protected:
    virtual void initializePartialResult() DAAL_C11_OVERRIDE
    {
        (*parameter.initializationProcedure)(input, _partialResult);
    }

    void initialize()
    {
        _in     = &input;
        _par    = &parameter;
        _result = services::SharedPtr<Result>(new Result());
        _partialResult = services::SharedPtr<PartialResult>(new PartialResult());
    }

    virtual OnlineIface * cloneImpl() const DAAL_C11_OVERRIDE = 0;

    services::SharedPtr<PartialResult> _partialResult;
    services::SharedPtr<Result> _result;
};


/**
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__ONLINE"></a>
 * \brief Computes correlation or variance-covariance matrix in the online processing mode.
 *
 * \tparam method           Computation method for correlation or variance-covariance matrix, \ref daal::algorithms::covariance::Method
 * \tparam algorithmFPType  Data type to use in intermediate computations of correlation or variance-covariance matrix, double or float
 *
 * \par Enumerations
 *      - \ref Method           Correlation or variance-covariance matrix computation methods
 *      - \ref InputId          Identifiers of input objects for the correlation or variance-covariance matrix algorithm
 *      - \ref PartialResultId  Identifiers of partial results of the correlation or variance-covariance matrix algorithm
 *      - \ref ResultId         Identifiers of results of the correlation or variance-covariance matrix algorithm
 *
 * \par References
 *      - <a href="DAAL-REF-COVARIANCE-ALGORITHM">Correlation and variance-covariance matrix algorithm description and usage models</a>
 *      - Input class
 *      - Parameter class
 *      - PartialResult class
 *      - Result class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Online : public OnlineIface
{
public:
    /** Default constructor */
    Online()
    {
        initialize();
    }

    /**
     * Constructs an algorithm for correlation or variance-covariance matrix computation
     * by copying input objects and parameters of another algorithm for correlation or variance-covariance
     * matrix computation
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Online(const Online<algorithmFPType, method> &other) : OnlineIface(other)
    {
        initialize();
    }

    virtual ~Online() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return (int)method; }

    /**
     * Returns a pointer to the newly allocated algorithm for correlation or variance-covariance matrix computation
     * with a copy of input objects and parameters of this algorithm for correlation or variance-covariance
     * matrix computation
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Online<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Online<algorithmFPType, method> >(cloneImpl());
    }

protected:
    virtual Online<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Online<algorithmFPType, method>(*this);
    }

    virtual void allocateResult() DAAL_C11_OVERRIDE
    {
        _result->allocate<algorithmFPType>(_partialResult.get(), _par, (int)method);
        _res    = _result.get();
        _pres   = _partialResult.get();
    }

    virtual void allocatePartialResult() DAAL_C11_OVERRIDE
    {
        _partialResult->allocate<algorithmFPType>(&input, _par, (int)method);
        _pres   = _partialResult.get();
    }

    void initialize()
    {
        this->_ac = new __DAAL_ALGORITHM_CONTAINER(online, OnlineContainer, algorithmFPType, method)(&_env);
    }
};
} // namespace interface1
using interface1::OnlineContainerIface;
using interface1::OnlineContainer;
using interface1::OnlineIface;
using interface1::Online;

} // namespace daal::algorithms::covariance
} // namespace daal::algorithms
} // namespace daal
#endif
