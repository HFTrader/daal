/* file: uniform_initializer.h */
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
//  Implementation of uniform initializer.
//--
*/

#ifndef __NEURAL_NETWORK_UNIFORM_INITIALIZER_H__
#define __NEURAL_NETWORK_UNIFORM_INITIALIZER_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/initializers/initializer.h"
#include "algorithms/neural_networks/initializers/uniform/uniform_initializer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace initializers
{
namespace uniform
{
namespace interface1
{
/**
 * \brief Provides methods to run implementations of the uniform initializer.
 *        This class is associated with the \ref uniform::interface1::Batch "uniform::Batch" class
 *        and supports the method of uniform initializer computation in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of uniform initializer, double or float
 * \tparam method           Computation method of the initializer, uniform::Method
 * \tparam cpu              Version of the cpu-specific implementation of the initializer, daal::CpuType
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public AnalysisContainerIface<batch>
{
public:
    /**
     * Constructs the container for the uniform initializer with the specified environment
     * \param[in] daalEnv   Environment object
     */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__INITIALIZERS__UNIFORM__BATCH"></a>
 * \brief Provides methods for uniform initializer computations in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of uniform initializer, double or float
 * \tparam method           Computation method of the initializer, uniform::Method
 *
 * \par Enumerations
 *      - uniform::Method          Computation methods for the uniform initializer
 *
 * \par References
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref initializers::interface1::Input "initializers::Input" class
 *      - \ref initializers::interface1::Result "initializers::Result" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public initializers::InitializerIface
{
public:
    Parameter *parameter; /*!< %Parameters of the initializer */

    /**
     * Constructs uniform initializer
     *  \param[in] a     Left bound a
     *  \param[in] b     Right bound b
     *  \param[in] seed  Seed for generating random numbers for the initialization
     */
    Batch(double a = -0.5, double b = 0.5, size_t seed = 777) : parameter(new Parameter(a, b, seed))
    {
        initialize();
    };

    /**
     * Constructs uniform initializer by copying input objects and parameters of another uniform initializer
     * \param[in] other An initializer to be used as the source to initialize the input objects
     *                  and parameters of this initializer
     */
    Batch(const Batch<algorithmFPType, method> &other): parameter(other.parameter)
    {
        initialize();
        input.set(initializers::data, other.input.get(initializers::data));
    }

    /**
     * Returns method of the initializer
     * \return Method of the initializer
     */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains results of uniform initializer
     * \return Structure that contains results of uniform initializer
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store results of uniform initializer
     * \param[in] result  Structure to store results of uniform initializer
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated uniform initializer
     * with a copy of input objects and parameters of this uniform initializer
     * \return Pointer to the newly allocated initializer
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    /**
     * Allocates memory to store the result of the uniform initializer
     */
    virtual void allocateResult() DAAL_C11_OVERRIDE
    {
        _par = parameter;
        this->_result->template allocate<algorithmFPType>(&(this->input), parameter, (int) method);
        this->_res = this->_result.get();
    }

protected:
    virtual Batch<algorithmFPType, method> *cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void initialize()
    {
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in = &input;
        _par = parameter;
        _result = services::SharedPtr<Result>(new Result());
    }

private:
    services::SharedPtr<Result> _result;
};

} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;
} // namespace uniform
} // namespace initializers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
