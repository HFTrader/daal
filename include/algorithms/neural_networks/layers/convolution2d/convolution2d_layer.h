/* file: convolution2d_layer.h */
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
//  Implementation of two-dimensional (2D) convolution neural network layer.
//--
*/

#ifndef __NEURAL_NETWORK_CONVOLUTION2D_LAYER_H__
#define __NEURAL_NETWORK_CONVOLUTION2D_LAYER_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer_types.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer_forward.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer_backward.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * \brief Contains classes for neural network 2D convolution layer
 */
namespace convolution2d
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__CONVOLUTION2D__BATCH"></a>
 * \brief Computes the result of the forward and backward 2D convolution layer of neural network in the batch processing mode
 *
 * \tparam algorithmFPType Data type to use in intermediate computations for the 2D convolution layer, double or float
 * \tparam method          Batch 2D convolution layer computation method, \ref Method
 *
 * \par References
 *      - \ref interface1::Parameter "Parameter" class
 *      - <a href="DAAL-REF-CONVOLUTION2DFORWARD-ALGORITHM">Forward 2D convolution layer description and usage models</a>
 *      - \ref forward::interface1::Batch  "forward::Batch" class
 *      - <a href="DAAL-REF-CONVOLUTION2DBACKWARD-ALGORITHM">Backward 2D convolution layer description and usage models</a>
 *      - \ref backward::interface1::Batch "backward::Batch" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public LayerIface
{
public:
    /**
     */
    Batch()
    {
        forward::Batch<algorithmFPType, method> *forwardLayerObject = new forward::Batch<algorithmFPType, method>();
        backward::Batch<algorithmFPType, method> *backwardLayerObject = new backward::Batch<algorithmFPType, method>();

        delete forwardLayerObject->parameter;
        forwardLayerObject->parameter = &parameter;

        delete backwardLayerObject->parameter;
        backwardLayerObject->parameter = &parameter;

        LayerIface::forwardLayer = services::SharedPtr<forward::Batch<algorithmFPType, method> >(forwardLayerObject);
        LayerIface::backwardLayer = services::SharedPtr<backward::Batch<algorithmFPType, method> >(backwardLayerObject);
    };

    Parameter parameter; /*!< %Parameters of the layer */

    /**
     * Returns the structure that contains parameters of the 2D convolution layer
     * \return Structure that contains parameters of the 2D convolution layer
     */
    virtual const layers::Parameter *cloneLayerParameter()
    {
        Parameter *par = new Parameter(parameter);

        services::SharedPtr<forward::Batch<algorithmFPType, method> > forwardLayerObject =
            services::staticPointerCast<forward::Batch<algorithmFPType, method>, layers::forward::LayerIface>(LayerIface::forwardLayer);

        services::SharedPtr<backward::Batch<algorithmFPType, method> > backwardLayerObject =
            services::staticPointerCast<backward::Batch<algorithmFPType, method>, layers::backward::LayerIface>(LayerIface::backwardLayer);

        forwardLayerObject->parameter = par;
        backwardLayerObject->parameter = par;

        return par;
    };
};
} // namespace interface1
using interface1::Batch;

} // namespace convolution2d
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
