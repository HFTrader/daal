/* file: cross_entropy_dense_default_batch_container.h */
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
//  Implementation of cross_entropy calculation algorithm container.
//--
*/

#include "cross_entropy_batch.h"
#include "cross_entropy_dense_default_batch_kernel.h"

namespace daal
{
namespace algorithms
{
namespace optimization_solver
{
namespace internal
{
namespace cross_entropy
{
namespace interface1
{
template<typename algorithmFPType, Method method, CpuType cpu>
BatchContainer<algorithmFPType, method, cpu>::BatchContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::cross_entropy::CrossEntropyKernel, algorithmFPType, method);
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
    objective_function::Result *result = static_cast<objective_function::Result *>(_res);
    Parameter *parameter = static_cast<Parameter *>(_par);

    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::cross_entropy::CrossEntropyKernel,
                       __DAAL_KERNEL_ARGUMENTS(algorithmFPType, method), compute, input, result, parameter);
}

} // namespace interface1
} // namespace cross_entropy
} // namespace internal
} // namespace optimization_solver
} // namespace algorithm
} // namespace daal
