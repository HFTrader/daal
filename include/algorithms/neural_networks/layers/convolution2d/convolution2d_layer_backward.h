/* file: convolution2d_layer_backward.h */
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
//  Implementation of backward two-dimensional (2D) convolution layer.
//--
*/

#ifndef __NEURAL_NETWORK_CONVOLUTION2D_LAYER_BACKWARD_H__
#define __NEURAL_NETWORK_CONVOLUTION2D_LAYER_BACKWARD_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer_types.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer_backward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace convolution2d
{
namespace backward
{
namespace interface1
{
/**
 * \brief Provides methods to run implementations of the of the backward 2D convolution layer
 *        This class is associated with the daal::algorithms::neural_networks::layers::convolution2d::backward::Batch class
 *        and supports the method of backward 2D convolution layer computation in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of backward 2D convolution layer, double or float
 * \tparam method           Computation method of the layer, \ref daal::algorithms::neural_networks::layers::convolution2d::Method
 * \tparam cpu              Version of the cpu-specific implementation of the layer, \ref daal::CpuType
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public AnalysisContainerIface<batch>
{
public:
    /**
     * Constructs the container for the backward 2D convolution layer with the specified environment
     * \param[in] daalEnv   Environment object
     */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__CONVOLUTION2D__BACKWARD__BATCH"></a>
 * \brief Provides methods for backward 2D convolution layer computations in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of backward 2D convolution layer, double or float
 * \tparam method           Computation method of the layer, \ref Method
 *
 * \par Enumerations
 *      - \ref Method          Computation methods for the backward 2D convolution layer
 *      - \ref LayerDataId     Identifiers of input objects for the backward 2D convolution layer
 *
 * \par References
 *      - Parameter class
 *      - Input class
 *      - Result class
 *      - <a href="DAAL-REF-CONVOLUTION2DBACKWARD-ALGORITHM">Backward 2D convolution layer description and usage models</a>
 *      - forward::Batch class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public layers::backward::LayerIface
{
public:
    Parameter *parameter; /*!< Parameters of the layer */
    Input input;          /*!< %Input objects of the layer */

    /**
     * Constructs 2D convolution layer
     */
    Batch() : parameter(new Parameter())
    {
        initialize();
    };

    /**
     * Constructs 2D convolution layer by copying input objects and parameters of another 2D convolution layer
     * \param[in] other A layer to be used as the source to initialize the input objects
     *                  and parameters of this layer
     */
    Batch(const Batch<algorithmFPType, method> &other): parameter(other.parameter)
    {
        initialize();
        input.set(layers::backward::inputGradient, other.input.get(layers::backward::inputGradient));
        input.set(layers::backward::inputFromForward, other.input.get(layers::backward::inputFromForward));
    }

    /**
     * Returns computation method of the layer
     * \return Computation method of the layer
     */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains input objects of 2D convolution layer
     * \return Structure that contains input objects of 2D convolution layer
     */
    virtual Input *getLayerInput() DAAL_C11_OVERRIDE { return &input; }

    /**
     * Returns the structure that contains parameters of the 2D convolution layer
     * \return Structure that contains parameters of the 2D convolution layer
     */
    virtual Parameter *getLayerParameter() { return parameter; };

    /**
     * Returns the structure that contains results of 2D convolution layer
     * \return Structure that contains results of 2D convolution layer
     */
    services::SharedPtr<layers::backward::Result> getLayerResult() DAAL_C11_OVERRIDE
    {
        return getResult();
    }

    /**
     * Returns the structure that contains results of 2D convolution layer
     * \return Structure that contains results of 2D convolution layer
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store results of 2D convolution layer
     * \param[in] result  Structure to store  results of 2D convolution layer
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated 2D convolution layer
     * with a copy of input objects and parameters of this 2D convolution layer
     * \return Pointer to the newly allocated layer
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

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
        input = convolution2d::backward::Input();
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
} // namespace convolution2d
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
