/* file: average_pooling3d_layer_forward.h */
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
//  Implementation of forward average 3D pooling layer.
//--
*/

#ifndef __AVERAGE_POOLING3D_LAYER_FORWARD_H__
#define __AVERAGE_POOLING3D_LAYER_FORWARD_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/pooling3d/average_pooling3d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling3d/average_pooling3d_layer_forward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace average_pooling3d
{
namespace forward
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * \brief Provides methods to run implementations of the forward average 3D pooling layer.
 *        This class is associated with the \ref forward::interface1::Batch "forward::Batch" class
 *        and supports the method of forward average 3D pooling layer computation in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of forward average 3D pooling layer, double or float
 * \tparam method           Computation method of the layer, average_pooling3d::Method
 * \tparam cpu              Version of the cpu-specific implementation of the layer, \ref daal::CpuType
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public AnalysisContainerIface<batch>
{
public:
    /**
     * Constructs the container for the forward pooling layer with the specified environment
     * \param[in] daalEnv   Environment object
     */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__AVERAGE_POOLING3D__FORWARD__BATCH"></a>
 * \brief Provides methods for the forward average 3D pooling layer in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the forward average 3D pooling layer, double or float
 * \tparam method           Forward average 3D pooling layer method, average_pooling3d::Method
 *
 * \par Enumerations
 *      - \ref Method                     Computation methods for the forward average 3D pooling layer
 *      - \ref forward::InputId           Identifiers of input objects for the forward average 3D pooling layer
 *      - \ref forward::ResultId          Identifiers of result objects for the forward average 3D pooling layer
 *      - \ref forward::ResultLayerDataId Identifiers of extra results computed by the forward average 3D pooling layer
 *      - \ref LayerDataId                Identifiers of collection in result objects for the forward average 3D pooling layer
 *
 * \par References
 *      - <a href="DAAL-REF-AVERAGEPOOLING3DFORWARD-ALGORITHM">Forward average 3D pooling layer description and usage models</a>
 *      - \ref interface1::Parameter "Parameter" class
 *      - \ref interface1::Input "Input" class
 *      - \ref interface1::Result "Result" class
 *      - \ref backward::interface1::Batch "backward::Batch" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public layers::forward::LayerIface
{
public:
    Parameter *parameter; /*!< Forward average 3D pooling layer parameters */
    Input input;          /*!< Forward average 3D pooling layer input */

    /**
     * Constructs forward average 3D pooling layer with the provided parameters
     * \param[in] nDimensions Number of dimensions in input data tensor
     */
    Batch(size_t nDimensions) : parameter(new Parameter(nDimensions - 3, nDimensions - 2, nDimensions - 1))
    {
        initialize();
    }

    /**
     * Constructs a forward average 3D pooling layer by copying input objects
     * and parameters of another forward average 3D pooling layer in the batch processing mode
     * \param[in] other Algorithm to use as the source to initialize the input objects
     *                  and parameters of the layer
     */
    Batch(const Batch<algorithmFPType, method> &other) : parameter(other.parameter)
    {
        initialize();
        input.set(layers::forward::data,    other.input.get(layers::forward::data));
    }

    /**
     * Returns the method of the layer
     * \return Method of the layer
     */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains the input objects of the forward average 3D pooling layer
     * \return Structure that contains the input objects of the forward average 3D pooling layer
     */
    virtual Input *getLayerInput() DAAL_C11_OVERRIDE { return &input; }

    /**
     * Returns the structure that contains the parameters of the forward average 3D pooling layer
     * \return Structure that contains the parameters of the forward average 3D pooling layer
     */
    virtual Parameter *getLayerParameter() { return parameter; };

    /**
     * Returns the structure that contains result of the forward average 3D pooling layer
     * \return Structure that contains result of the forward average 3D pooling layer
     */
    services::SharedPtr<layers::forward::Result> getLayerResult()
    {
        return getResult();
    }

    /**
     * Returns the structure that contains the result of the forward average 3D pooling layer
     * \return Structure that contains the result of the forward average 3D pooling layer
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store the result of the forward average 3D pooling layer
     * \param[in] result Structure to store the result of the forward average 3D pooling layer
     */
    void setResult(services::SharedPtr<Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to a newly allocated forward average 3D pooling layer
     * with a copy of the input objects and parameters for this forward average 3D pooling layer
     * in the batch processing mode
     * \return Pointer to the newly allocated layer
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

    /**
     * Allocates memory to store the result of the forward average 3D pooling layer
     */
    virtual void allocateResult()
    {
        _par = parameter;
        this->_result->template allocate<algorithmFPType>(&(this->input), parameter, (int) method);
        this->_res = this->_result.get();
    }

    /**
     * Allocates memory buffers needed for the computations
     */
    virtual void allocateLayerData() DAAL_C11_OVERRIDE
    {
        _par = parameter;
        this->_result->template allocateLayerData<algorithmFPType>(&(this->input), parameter, (int) method);
        this->_res = this->_result.get();
    }

protected:
    virtual Batch<algorithmFPType, method> *cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    void setParameter() DAAL_C11_OVERRIDE { _par = parameter; }

    virtual void allocateInput() DAAL_C11_OVERRIDE
    {
        this->input.template allocate<algorithmFPType>(parameter, (int) method);
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
} // namespace forward
} // namespace average_pooling3d
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal

#endif
