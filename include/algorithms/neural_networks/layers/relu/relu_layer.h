/* file: relu_layer.h */
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
//  Implementation of the rectifier linear unit (relu) layer
//--
*/

#ifndef __NEURAL_NETWORK_RELU_LAYER_H__
#define __NEURAL_NETWORK_RELU_LAYER_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/relu/relu_layer_types.h"
#include "algorithms/neural_networks/layers/relu/relu_layer_forward.h"
#include "algorithms/neural_networks/layers/relu/relu_layer_backward.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * \brief Contains classes for the relu layer
 */
namespace relu
{
/**
* \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
*/
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__RELU__BATCH"></a>
 * \brief Provides methods for the relu layer in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the relu layer, double or float
 * \tparam method           Relu layer method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method   Computation methods
 *
 * \par References
 *      - <a href="DAAL-REF-RELUFORWARD-ALGORITHM">Forward relu layer description and usage models</a>
 *      - \ref forward::interface1::Batch "forward::Batch" class
 *      - <a href="DAAL-REF-RELUBACKWARD-ALGORITHM">Backward relu layer description and usage models</a>
 *      - \ref backward::interface1::Batch "backward::Batch" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public LayerIface
{
public:


    /** \brief Default constructor */
    Batch()
    {
        forward::Batch<algorithmFPType, method> *forwardLayerObject = new forward::Batch<algorithmFPType, method>();
        backward::Batch<algorithmFPType, method> *backwardLayerObject = new backward::Batch<algorithmFPType, method>();

        LayerIface::forwardLayer = services::SharedPtr<forward::Batch<algorithmFPType, method> >(forwardLayerObject);
        LayerIface::backwardLayer = services::SharedPtr<backward::Batch<algorithmFPType, method> >(backwardLayerObject);
    };

    /**
     * Returns the structure that contains parameters of the relu layer
     * \return Structure that contains parameters of the relu layer
     */
    virtual const layers::Parameter *cloneLayerParameter()
    {
        return NULL;
    };
};
} // namespace interface1
using interface1::Batch;

} // namespace relu
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
