/* file: correlation_distance.h */
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
//  Implementation of correlation distance algorithm interface.
//--
*/

#ifndef __CORDISTANCE_H__
#define __CORDISTANCE_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/distance/correlation_distance_types.h"

namespace daal
{
namespace algorithms
{
namespace correlation_distance
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__CORDISTANCE__OFFLINECONTAINER"></a>
 * \brief Provides methods to run implementations of the correlation distance algorithm.
 *        This class is associated with daal::algorithms::correlation_distance::Batch class
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the correlation distance algorithm, double or float
 * \tparam method           Correlation distance computation method, \ref Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();
    /**
     * Runs implementation of the correlation distance algorithm in the batch processing mode
     */
    virtual void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__CORDISTANCE__OFFLINE"></a>
 * \brief Computes the correlation distance in the batch processing mode.
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the correlation distance algorithm, double or float
 * \tparam method           Correlation distance computation method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method   Correlation distance computation methods
 *      - \ref InputId  Identifiers of correlation distance input objects
 *      - \ref ResultId Identifiers of correlation distance results
 *
 * \par References
 *      - <a href="DAAL-REF-CORDISTANCE-ALGORITHM">Correlation distance algorithm description and usage models</a>
 *      - Input class
 *      - Result class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public daal::algorithms::Analysis<batch>
{
public:
    Batch()
    {
        initialize();
    }

    /**
     * Constructs a correlation distance algorithm by copying input objects
     * of another correlation distance algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other)
    {
        initialize();
        input.set(data, other.input.get(data));
    }

    /**
    * Returns the method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int)method; }

    /**
     * Returns the structure that contains the correlation distance
     * \return Structure that contains the correlation distance
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Sets the memory to store the results of the correlation distance algorithm
     * \param[in] res  Structure to store results of the algorithm
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated correlation distance algorithm with a copy of input objects
     * of this correlation distance algorithm
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

    virtual void allocateResult()
    {
        _result->allocate<algorithmFPType>(&input, NULL, (int) method);
        _res = _result.get();
    }

    void initialize()
    {
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in = &input;
        _result = services::SharedPtr<Result>(new Result());
    }

public:
    Input input;

private:
    services::SharedPtr<Result> _result;
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // namespace correlation_distance
} // namespace algorithms
} // namespace daal
#endif
