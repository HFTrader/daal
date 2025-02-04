/* file: covariance_batch.h */
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
//  Implementation of Covariance Batch algorithm interface.
//--
*/

#ifndef __COVARIANCE_BATCH_H__
#define __COVARIANCE_BATCH_H__

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
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__BATCHCONTAINERIFACE"></a>
 * \brief Class that specifies interfaces of implementations of the correlation or variance-covariance matrix container.
 *        This class is associated with daal::algorithms::covariance::BatchContainerIface class
 */
class BatchContainerIface : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    /** Default constructor */
    BatchContainerIface() {};
    virtual ~BatchContainerIface() {}

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute() = 0;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__BATCHCONTAINER"></a>
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm.
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 * \tparam method           Computation method of the algorithm, \ref daal::algorithms::covariance::Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer
{};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using default computation method
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, defaultDense, cpu> : public BatchContainerIface
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using single-pass computation method
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, singlePassDense, cpu> : public BatchContainerIface
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using precomputed sum computation method
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, sumDense, cpu> : public BatchContainerIface
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using fast computation method that works with Compressed Sparse Rows (CSR) numeric tables
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, fastCSR, cpu> : public BatchContainerIface
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using single-pass computation method that works with Compressed Sparse Rows (CSR) numeric tables
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, singlePassCSR, cpu> : public BatchContainerIface
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * \brief Provides methods to run implementations of the correlation or variance-covariance matrix algorithm
 *        using precomputed sum computation method that works with Compressed Sparse Rows (CSR) numeric tables
 *        This class is associated with daal::algorithms::covariance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, sumCSR, cpu> : public BatchContainerIface
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__BATCHIFACE"></a>
 * \brief Abstract class that specifies interface of the algorithms
 *        for computing correlation or variance-covariance matrix in the batch processing mode
 */
class DAAL_EXPORT BatchIface : public daal::algorithms::Analysis<batch>
{
public:
    /** Default constructor */
    BatchIface()
    {
        initialize();
    };

    /**
     * Constructs an algorithm for correlation or variance-covariance matrix computation
     * by copying input objects and parameters of another algorithm for correlation or variance-covariance
     * matrix computation
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    BatchIface(const BatchIface &other)
    {
        initialize();
        input.set(data, other.input.get(data));
        parameter = other.parameter;
    }

    /**
     * Returns the structure that contains correlation or variance-covariance matrix
     * \return Structure that contains the computed matrix
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    };

    /**
     * Registers user-allocated memory to store results of computation of the correlation or variance-covariance matrix
     * \param[in] result    Structure to store the results
     */
    virtual void setResult(const services::SharedPtr<Result> &result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated algorithm for correlation or variance-covariance matrix computation
     * with a copy of input objects and parameters of this algorithm for correlation or variance-covariance
     * matrix computation
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<BatchIface> clone() const
    {
        return services::SharedPtr<BatchIface>(cloneImpl());
    }

    virtual ~BatchIface() {}

    Input input;                    /*!< %Input data structure */
    Parameter parameter;            /*!< %Parameter structure */

protected:
    services::SharedPtr<Result> _result;

    void initialize()
    {
        _result = services::SharedPtr<Result>(new Result());
        _in  = &input;
        _par = &parameter;
    }
    virtual BatchIface * cloneImpl() const DAAL_C11_OVERRIDE = 0;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__COVARIANCE__BATCH"></a>
 * \brief Computes correlation or variance-covariance matrix in the batch processing mode.
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the correlation or variance-covariance matrix, double or float
 * \tparam method           Computation method, \ref daal::algorithms::covariance::Method
 *
 * \par Enumerations
 *      - \ref Method  Computation methods for correlation or variance-covariance matrix
 *      - \ref InputId  Identifiers of input objects for the correlation or variance-covariance matrix algorithm
 *      - \ref ResultId Identifiers of results of the correlation or variance-covariance matrix algorithm
 *
 * \par References
 *      - <a href="DAAL-REF-COVARIANCE-ALGORITHM">Correlation and variance-covariance matrix algorithm description and usage models</a>
 *      - Input class
 *      - Parameter class
 *      - Result class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public BatchIface
{
public:
    /** Default constructor */
    Batch()
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
    Batch(const Batch<algorithmFPType, method> &other) : BatchIface(other)
    {
        initialize();
    }

    virtual ~Batch() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Returns a pointer to the newly allocated algorithm for correlation or variance-covariance matrix computation
     * with a copy of input objects and parameters of this algorithm for correlation or variance-covariance
     * matrix computation
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

    virtual void allocateResult() DAAL_C11_OVERRIDE
    {
        _result->allocate<algorithmFPType>(&input, _par, (int)method);
        _res = _result.get();
    }

    void initialize()
    {
        this->_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
    }
};

} // namespace interface1
using interface1::BatchContainerIface;
using interface1::BatchContainer;
using interface1::BatchIface;
using interface1::Batch;

} // namespace daal::algorithms::covariance
}
} // namespace daal
#endif  // __COVARIANCE_BATCH_H__
