/* file: split_layer_backward.h */
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
//  Implementation of the backward split layer
//--
*/

#ifndef __NEURAL_NETWORK_SPLIT_LAYER_BACKWARD_H__
#define __NEURAL_NETWORK_SPLIT_LAYER_BACKWARD_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/split/split_layer_types.h"
#include "algorithms/neural_networks/layers/split/split_layer_backward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * \brief Contains classes for the split layer
 */
namespace split
{
/**
 * \brief Contains classes for the backward split layer
 */
namespace backward
{
namespace interface1
{
/**
* \brief Provides methods to run implementations of the of the backward split layer
*        This class is associated with the daal::algorithms::neural_networks::layers::split::backward::Batch class
*        and supports the method of backward split layer computation in the batch processing mode
*
* \tparam algorithmFPType  Data type to use in intermediate computations of backward split layer, double or float
* \tparam method           Computation method of the layer, \ref daal::algorithms::neural_networks::layers::split::Method
* \tparam cpu              Version of the cpu-specific implementation of the layer, \ref daal::CpuType
*/
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public AnalysisContainerIface<batch>
{
public:
    /**
    * Constructs the container for the backward split layer with the specified environment
    * \param[in] daalEnv   Environment object
    */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SPLIT__BACKWARD__BATCH"></a>
 * \brief Computes the results of the backward split layer in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the backward split layer, double or float
 * \tparam method           The backward split layer computation method, \ref Method
 * \par Enumerations
 *      - \ref Method                      Computation methods for the backward split layer
 *      - \ref backward::InputId           Identifiers of input objects for the backward split layer
 *      - \ref backward::InputLayerDataId  Identifiers of extra results computed by the backward split layer
 *      - \ref backward::ResultId          Identifiers of result objects for the backward split layer
 *
 * \par References
 *      - <a href="DAAL-REF-SPLITBACKWARD-ALGORITHM">Backward split layer description and usage models</a>
 *      - \ref forward::interface1::Batch "forward::Batch" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public layers::backward::LayerIface
{
public:
    Parameter *parameter; /*!< %Parameters of the algorithm */
    Input input;         /*!< %Input data structure */

    /** Default constructor */
    Batch() : parameter(new Parameter())
    {
        initialize();
    };

    /**
     * Constructs the backward split layer by copying input objects of
     * another backward split layer in the batch processing mode
     * \param[in] other An algorithm to be used as the source to initialize the input objects of the backward split layer
     */
    Batch(const Batch<algorithmFPType, method> &other) : parameter(other.parameter)
    {
        initialize();
        input.set(layers::backward::inputFromForward, other.input.get(layers::backward::inputFromForward));
    }

    /**
    * Returns method of the backward split layer
    * \return Method of the backward split layer
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains input objects of split layer
     * \return Structure that contains input objects of split layer
     */
    virtual Input *getLayerInput() DAAL_C11_OVERRIDE { return &input; }

    /**
    * Returns the structure that contains parameters of the backward split layer
    * \return Structure that contains parameters of the backward split layer
    */
    virtual Parameter *getLayerParameter() { return parameter; };

    /**
     * Returns the structure that contains the result of the backward split layer
     * \return Structure that contains the result of the backward split layer
     */
    services::SharedPtr<layers::backward::Result> getLayerResult()
    {
        return _result;
    }

    /**
     * Returns the structure that contains the result of the backward split layer
     * \return Structure that contains the result of backward split layer
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store results of the backward split layer
     * \param[in] result  Structure to store  results of the backward split layer
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to a newly allocated backward split layer
     * with a copy of input objects of this backward split layer
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    /**
    * Allocates memory to store the result of the backward split layer
    */
    virtual void allocateResult()
    {
        this->_result->template allocate<algorithmFPType>(&(this->input), parameter, (int) method);
        this->_res = this->_result.get();
    }

protected:
    virtual Batch<algorithmFPType, method> *cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void setParameter() DAAL_C11_OVERRIDE { _par = parameter; };

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
} // namespace backward
} // namespace split
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
