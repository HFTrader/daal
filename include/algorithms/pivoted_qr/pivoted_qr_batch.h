/* file: pivoted_qr_batch.h */
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
//  Implementation of Pivoted QR Decomposition Batch algorithm interface.
//--
*/

#ifndef __PIVOTED_QR_BATCH_H__
#define __PIVOTED_QR_BATCH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/pivoted_qr/pivoted_qr_types.h"

namespace daal
{
namespace algorithms
{
namespace pivoted_qr
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__PIVOTED_QR__BATCHCONTAINER"></a>
 * \brief Provides methods to run implementations of the pivoted QR algorithm.
 *
 * \tparam method           Pivoted QR computation method, \ref daal::algorithms::pivoted_qr::Method
 * \tparam algorithmFPType  Data type to use in intermediate computations for the pivoted QR, double or float
 *
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    /** Default constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    /** Default destructor */
    virtual ~BatchContainer();
    virtual void compute() DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PIVOTED_QR__BATCH"></a>
 * \brief Computes the results of the pivoted QR algorithm in the batch processing mode.
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the pivoted QR algorithm, double or float
 * \tparam method           Computation method, \ref daal::algorithms::pivoted_qr::Method
 *
 * \par Enumerations
 *      - \ref Method   Computation methods for the algorithm
 *
 * \par References
 *      - <a href="DAAL-REF-PIVOTED_QR-ALGORITHM">Pivoted QR algorithm description and usage models</a>
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public daal::algorithms::Analysis<batch>
{
public:
    Input input;            /*!< Input data structure */
    Parameter parameter;    /*!< Pivoted QR parameters structure */

    Batch()
    {
        initialize();
    }

    /**
     * Constructs a pivoted QR decomposition algorithm by copying input objects and parameters
     * of another pivoted QR decomposition algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other)
    {
        initialize();
        input.set(data, other.input.get(data));
        parameter = other.parameter;
    }

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Returns the structure that contains the results of the pivoted QR decomposition algorithm
     * \return Structure that contains the results of the pivoted QR decomposition algorithm
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Sets structure to store the results of the pivoted QR algorithm
     * \return Structure to store results of the pivoted QR algorithm
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated pivoted QR decomposition algorithm
     * with a copy of input objects and parameters of this pivoted QR decomposition algorithm
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
        _result = services::SharedPtr<Result>(new Result());
        _result->allocate<algorithmFPType>(_in, 0, 0);
        _res = _result.get();
    }

    void initialize()
    {
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in   = &input;
        _par  = &parameter;
    }

private:
    services::SharedPtr<Result> _result;
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // namespace daal::algorithms::pivoted_qr
}
} // namespace daal
#endif
