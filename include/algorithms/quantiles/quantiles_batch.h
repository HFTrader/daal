/* file: quantiles_batch.h */
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
//  Implementation of the interface of the quantiles algorithm in the batch processing mode.
//--
*/

#ifndef __QUANTILES_BATCH_H__
#define __QUANTILES_BATCH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/quantiles/quantiles_types.h"

namespace daal
{
namespace algorithms
{
namespace quantiles
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__QUANTILES__BATCHCONTAINER"></a>
 * \brief Provides methods to run implementations of the quantiles algorithm.
 *        It is associated with the daal::algorithms::quantiles::Batch class
 *        and supports methods of quantiles computation in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the quantile algorithms, double or float
 * \tparam method           Quantiles computation method, \ref daal::algorithms::quantiles::Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    BatchContainer(daal::services::Environment::env *daalEnv);
    virtual ~BatchContainer();
    /**
     * Run an implementation of the quantiles algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__QUANTILES__BATCH"></a>
 * \brief Computes values of quantiles in the batch processing mode.
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the quantile algorithms, double or float
 * \tparam method           Quantiles computation method, \ref daal::algorithms::quantiles::Method
 *
 * \par Enumerations
 *      - \ref Method   Quantiles computation methods
 *      - \ref InputId  Identifiers of quantiles input objects
 *      - \ref ResultId Identifiers of quantiles results
 *
 * \par References
 *      - <a href="DAAL-REF-QUANTILES-ALGORITHM">Quantiles algorithm description and usage models</a>
 *      - Input class
 *      - Parameter class
 *      - Result class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public daal::algorithms::Analysis<batch>
{
public:
    Input input;                    /*!< %input data structure */
    Parameter parameter;            /*!< Quantiles parameters structure */

    /** Default constructor     */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs algorithm that computes quantiles by copying input objects and parameters
     * of another algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other)
    {
        initialize();
        input.set(data, other.input.get(data));
        parameter = other.parameter;
    }

    virtual ~Batch() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Returns the structure that contains computed results of the quantile algorithms
     * \return Structure that contains computed results of the quantile algorithms
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store results of the quantile algorithms
     * \param[in] result Structure to store results of the quantile algorithms
     */
    void setResult(const services::SharedPtr<Result> &result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated algorithm that computes quantiles
     * with a copy of input objects and parameters of this algorithm
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
        _result->allocate<algorithmFPType>(&input, &parameter, method);
        _res = _result.get();
    }

    void initialize()
    {
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in  = &input;
        _par = &parameter;
        _result = services::SharedPtr<Result>(new Result());
    }

    services::SharedPtr<Result> _result;
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // namespace daal::algorithms::quantiles
} // namespace daal::algorithms
} // namespace daal
#endif
