/* file: prelu_layer_backward.h */
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
//  Implementation of the parametric rectifier linear unit (prelu) layer
//--
*/

#ifndef __NEURAL_NETWORK_PRELU_LAYER_BACKWARD_H__
#define __NEURAL_NETWORK_PRELU_LAYER_BACKWARD_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/prelu/prelu_layer_types.h"
#include "algorithms/neural_networks/layers/prelu/prelu_layer_backward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * \brief Contains classes for the prelu layer
 */
namespace prelu
{
namespace backward
{
namespace interface1
{
/**
* \brief Provides methods to run implementations of the of the backward prelu layer
*        This class is associated with the daal::algorithms::neural_networks::layers::prelu::backward::Batch class
*        and supports the method of backward prelu layer computation in the batch processing mode
*
* \tparam algorithmFPType  Data type to use in intermediate computations of backward prelu layer, double or float
* \tparam method           Computation method of the layer, \ref daal::algorithms::neural_networks::layers::prelu::Method
* \tparam cpu              Version of the cpu-specific implementation of the layer, \ref daal::CpuType
*/

template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public AnalysisContainerIface<batch>
{
public:
    /**
    * Constructs the container for the backward prelu layer with the specified environment
    * \param[in] daalEnv   Environment object
    */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__PRELU__BACKWARD__BATCH"></a>
 * \brief Provides methods for the backward prelu layer in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the backward prelu layer, double or float
 * \tparam method           The backward prelu layer computation method, \ref Method
 * \par Enumerations
 *      - \ref Method                      Computation methods for the backward prelu layer
 *      - \ref backward::InputId           Identifiers of input objects for the backward prelu layer
 *      - \ref LayerDataId                 Identifiers of collection in input objects for the prelu layer
 *      - \ref backward::InputLayerDataId  Identifiers of extra results computed by the forward prelu layer
 *      - \ref backward::ResultId          Identifiers of result objects for the backward prelu layer
 *
 * \par References
 *      - <a href="DAAL-REF-PRELUBACKWARD-ALGORITHM">Backward prelu layer description and usage models</a>
 *      - \ref forward::interface1::Batch "forward::Batch" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public layers::backward::LayerIface
{
public:
    Input input;             /*!< %Input objects of the layer */
    Parameter *parameter;    /*!< Backward prelu layer parameters */

    /** \brief Default constructor */
    Batch() : parameter(new Parameter())
    {
        initialize();
    };

    /**
     * Constructs the backward prelu layer by copying input objects of
     * another backward prelu layer in the batch processing mode
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  of the backward prelu layer
     */
    Batch(const Batch<algorithmFPType, method> &other) : parameter(other.parameter)
    {
        initialize();
        input.set(layers::backward::inputGradient, other.input.get(layers::backward::inputGradient));
        input.set(layers::backward::inputFromForward, other.input.get(layers::backward::inputFromForward));
        parameter = other.parameter;
    }

    /**
    * Returns method of the backward prelu layer
    * \return Method of the backward prelu layer
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains input objects of the backward prelu layer
     * \return Structure that contains input objects of the backward prelu layer
     */
    virtual Input *getLayerInput() DAAL_C11_OVERRIDE { return &input; }

    /**
    * Returns the structure that contains parameters of the forward prelu layer
    * \return Structure that contains parameters of the forward prelu layer
    */
    virtual Parameter *getLayerParameter() { return parameter; };

    /**
     * Returns the structure that contains the result of the backward prelu layer
     * \return Structure that contains the result of the backward prelu layer
     */
    services::SharedPtr<layers::backward::Result> getLayerResult()
    {
        return _result;
    }

    /**
     * Returns the structure that contains the result of the backward prelu layer
     * \return Structure that contains the result of backward prelu layer
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store results of the backward prelu layer
     * \param[in] result  Structure to store  results of the backward prelu layer
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to a newly allocated backward prelu layer
     * with a copy of input objects of this backward prelu layer
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    /**
    * Allocates memory to store the result of the backward prelu layer
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
} // namespace prelu
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
