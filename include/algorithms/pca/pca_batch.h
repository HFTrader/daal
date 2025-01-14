/* file: pca_batch.h */
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
//  Implementation of PCA algorithm interface.
//--
*/

#ifndef __PCA_BATCH_H__
#define __PCA_BATCH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "services/daal_memory.h"
#include "algorithms/pca/pca_types.h"

namespace daal
{
namespace algorithms
{
namespace pca
{

namespace interface1
{
/**
 * \brief Class containing methods to compute the results of the PCA algorithm */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public AnalysisContainerIface<batch>
{};

/**
 * \brief Class containing methods to compute the results of the PCA algorithm */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, correlationDense, cpu> : public AnalysisContainerIface<batch>
{
public:
    /** \brief Constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * \brief Class containing methods to compute the results of the PCA algorithm */
template<typename algorithmFPType, CpuType cpu>
class DAAL_EXPORT BatchContainer<algorithmFPType, svdDense, cpu> : public AnalysisContainerIface<batch>
{
public:
    /** \brief Constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__OFFLINE"></a>
 * \brief Computes the results of the PCA algorithm
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for PCA, double or float
 * \tparam method           PCA computation method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method  Computation methods for the algorithm
 *
 * \par References
 *      - <a href="DAAL-REF-PCA-ALGORITHM">PCA algorithm description and usage models</a>
 *      - \ref interface1::BatchParameter class
 */
template<typename algorithmFPType = double, Method method = correlationDense>
class DAAL_EXPORT Batch : public Analysis<batch>
{
public:
    /** Default constructor */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs a PCA algorithm by copying input objects and parameters of another PCA algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other)
    {
        initialize();
        input.set(data, other.input.get(data));
        parameter = other.parameter;
    }

    ~Batch() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const { return method; };

    /**
     * Registers user-allocated memory to store the results of the PCA algorithm
     * \param[in] res    Structure for storing the results of the PCA algorithm
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns the structure that contains final results of the PCA algorithm
     * \return Structure that contains final results of the PCA
     */
    services::SharedPtr<Result> getResult() { return _result; }

    /**
     * Returns a pointer to the newly allocated PCA algorithm
     * with a copy of input objects and parameters of this PCA algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    Input input; /*!< Input data structure */
    BatchParameter<algorithmFPType, method> parameter; /*!< Parameters */

protected:
    services::SharedPtr<Result> _result;

    virtual Batch<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void allocateResult()
    {
        _result->allocate<algorithmFPType>(&input, &parameter, method);
        _res = _result.get();
    }

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in = &input;
        _par = &parameter;
        _result = services::SharedPtr<Result>(new Result());
    }
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

}
}
}
#endif
