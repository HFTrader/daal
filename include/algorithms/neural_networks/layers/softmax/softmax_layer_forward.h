/* file: softmax_layer_forward.h */
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
//  Implementation of the forward softmax layer interface.
//--
*/

#ifndef __NEURAL_NETWORK_SOFTMAX_LAYER_FORWARD_H__
#define __NEURAL_NETWORK_SOFTMAX_LAYER_FORWARD_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/softmax/softmax_layer_types.h"
#include "algorithms/neural_networks/layers/softmax/softmax_layer_forward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace softmax
{
namespace forward
{
namespace interface1
{
/**
 * \brief Class containing methods for the forward softmax layer using algorithmFPType precision arithmetic
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    /**
    * Constructs the container for the forward softmax layer with the specified environment
    * \param[in] daalEnv   Environment object
    */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();
    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SOFTMAX__FORWARD__BATCH"></a>
 * \brief Computes the results of the forward softmax layer in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of the forward softmax layer, double or float
 * \tparam method           Forward softmax layer method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method                     Computation methods for the forward softmax layer
 *      - \ref forward::InputId           Identifiers of input objects for the forward softmax layer
 *      - \ref forward::ResultId          Identifiers of result objects for the forward softmax layer
 *
 * \par References
 *      - <a href="DAAL-REF-SOFTMAXFORWARD-ALGORITHM">Forward softmax layer description and usage models</a>
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref backward::interface1::Batch "backward::Batch" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public layers::forward::LayerIface
{
public:
    Parameter *parameter;  /*!< softmax layer parameters structure */
    Input input;          /*!< %Input objects of the layer */

    /** Default constructor */
    Batch() : parameter(new Parameter())
    {
        initialize();
    };

    /**
     * Constructs a forward softmax layer by copying input objects
     * and parameters of another forward softmax layer in the batch processing mode
     * \param[in] other Algorithm to use as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other) : parameter(other.parameter)
    {
        initialize();
        input.set(layers::forward::data, other.input.get(layers::forward::data));
        input.set(layers::forward::weights, other.input.get(layers::forward::weights));
        input.set(layers::forward::biases, other.input.get(layers::forward::biases));
    }

    /**
    * Returns the method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains input objects of the softmax forward layer
     * \return Structure that contains input objects of the softmax forward layer
     */
    virtual Input *getLayerInput() DAAL_C11_OVERRIDE { return &input; }

    /**
     * Returns the structure that contains parameters of the forward softmax layer
     * \return Structure that contains parameters of the forward softmax layer
     */
    virtual Parameter *getLayerParameter() { return parameter; };

    /**
     * Returns the structure that contains result of the forward softmax layer
     * \return Structure that contains result of the forward softmax layer
     */
    services::SharedPtr<layers::forward::Result> getLayerResult()
    {
        return getResult();
    }

    /**
     * Returns the structure that contains result of the forward softmax layer
     * \return Structure that contains result of the forward softmax layer
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store result of the forward softmax layer
     * \param[in] result  Structure to store result of the forward softmax layer
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated forward softmax layer
     * with a copy of input objects and parameters of this forward softmax layer
     * in the batch processing mode
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    /**
    * Allocates memory to store the result of the forward softmax layer
    */
    virtual void allocateResult()
    {
        this->_result->template allocate<algorithmFPType>(&(this->input), parameter, (int) method);
        this->_res = this->_result.get();
    }

    /**
    * Allocates memory to store the result of the forward softmax layer for the backward softmax layer
    */
    virtual void allocateLayerData() DAAL_C11_OVERRIDE
    {
        this->_result->template allocateLayerData<algorithmFPType>(&(this->input), parameter, (int) method);
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
} // namespace forward
} // namespace softmax
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
