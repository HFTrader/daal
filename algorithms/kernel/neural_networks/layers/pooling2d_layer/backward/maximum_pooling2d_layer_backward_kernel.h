/* file: maximum_pooling2d_layer_backward_kernel.h */
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

//++
//  Declaration of template function that calculate backward pooling layer relults.
//--


#ifndef __MAXIMUM_POOLING2D_LAYER_BACKWARD_KERNEL_H__
#define __MAXIMUM_POOLING2D_LAYER_BACKWARD_KERNEL_H__

#include "neural_networks/layers/pooling2d/maximum_pooling2d_layer_backward.h"
#include "neural_networks/layers/pooling2d/maximum_pooling2d_layer_backward_types.h"
#include "kernel.h"
#include "tensor.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace maximum_pooling2d
{
namespace backward
{
namespace internal
{

/**
 *  \brief Kernel for backward pooling layer results computation
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class PoolingKernel : public Kernel
{
public:
    void compute(const maximum_pooling2d::backward::Input *input,
                const maximum_pooling2d::Parameter *parameter,
                maximum_pooling2d::backward::Result *result);
};

} // internal
} // backward
} // maximum_pooling2d
} // layers
} // neural_networks
} // algorithms
} // daal

#endif
