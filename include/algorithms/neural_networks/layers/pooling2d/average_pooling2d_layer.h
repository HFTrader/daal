/* file: average_pooling2d_layer.h */
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
//  Implementation of 2D average pooling layer.
//--
*/

#ifndef __AVERAGE_POOLING2D_LAYER_H__
#define __AVERAGE_POOLING2D_LAYER_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/pooling2d/average_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling2d/average_pooling2d_layer_forward.h"
#include "algorithms/neural_networks/layers/pooling2d/average_pooling2d_layer_backward.h"


namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * \brief Contains classes for average two-dimensional (2D) pooling layer
 */
namespace average_pooling2d
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__AVERAGE_POOLING2D__BATCH"></a>
 * \brief Provides methods for the average 2D pooling layer in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the average 2D pooling layer, double or float
 * \tparam method           Average 2D pooling layer method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method      Computation methods
 *      - \ref LayerDataId Identifiers of collection in results of forward and in input objects for the backward average 2D pooling layer
 *
 * \par References
 *      - <a href="DAAL-REF-AVERAGEPOOLING2DFORWARD-ALGORITHM">Forward average 2D pooling layer description and usage models</a>
 *      - \ref forward::interface1::Batch "forward::Batch" class
 *      - <a href="DAAL-REF-AVERAGEPOOLING2DBACKWARD-ALGORITHM">Backward average 2D pooling layer description and usage models</a>
 *      - \ref backward::interface1::Batch "backward::Batch" class
 *      - \ref interface1::Parameter "Parameter" class
 */
template<typename algorithmFPType = float, Method method = defaultDense>
class Batch : public LayerIface
{
public:
    /**
     * Constructs the average 2D pooling layer
     * \param[in] nDimensions Number of dimensions in input gradient tensor
     */
    Batch(size_t nDimensions) : parameter(nDimensions - 2, nDimensions - 1)
    {
        forward::Batch<algorithmFPType, method> *forwardLayerObject = new forward::Batch<algorithmFPType, method>(nDimensions);
        backward::Batch<algorithmFPType, method> *backwardLayerObject = new backward::Batch<algorithmFPType, method>(nDimensions);

        delete forwardLayerObject->parameter;
        forwardLayerObject->parameter = &parameter;

        delete backwardLayerObject->parameter;
        backwardLayerObject->parameter = &parameter;

        LayerIface::forwardLayer = services::SharedPtr<forward::Batch<algorithmFPType, method> >(forwardLayerObject);
        LayerIface::backwardLayer = services::SharedPtr<backward::Batch<algorithmFPType, method> >(backwardLayerObject);
    }

    Parameter parameter; /*!< Average 2D pooling layer parameters */

    /**
     * Returns the structure that contains parameters of the average 2D pooling layer
     * \return Structure that contains parameters of the average 2D pooling layer
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

} // namespace average_pooling2d
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal

#endif
