/* file: neural_networks_training_batch_container.h */
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
//  Implementation of neural_networks calculation algorithm container.
//--
*/

#ifndef __NEURAL_NETWORKS_TRAINING_BATCH_CONTAINER_H__
#define __NEURAL_NETWORKS_TRAINING_BATCH_CONTAINER_H__

#include "neural_networks/neural_networks_training.h"
#include "neural_networks_types.h"
#include "neural_networks_training_types.h"
#include "neural_networks_training_feedforward_kernel.h"
#include "kernel.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace training
{
namespace interface1
{
template<typename algorithmFPType, Method method, CpuType cpu>
BatchContainer<algorithmFPType, method, cpu>::BatchContainer(daal::services::interface1::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::NeuralNetworksFeedforwardTrainingKernel, algorithmFPType, method);
}

template<typename algorithmFPType, Method method, CpuType cpu>
BatchContainer<algorithmFPType, method, cpu>::~BatchContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename algorithmFPType, Method method, CpuType cpu>
void BatchContainer<algorithmFPType, method, cpu>::compute()
{
    Input *input = static_cast<Input *>(_in);
    Result *result = static_cast<Result *>(_res);

    Parameter<algorithmFPType> *parameter = static_cast<Parameter<algorithmFPType> *>(_par);
    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::NeuralNetworksFeedforwardTrainingKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFPType, method), compute,
                       input, parameter, result);
}
} // namespace interface1
}
} // namespace neural_networks
} // namespace algorithms
} // namespace daal

#endif
