/* file: sorting_batch_container.h */
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
//  Implementation of sorting algorithm container.
//--
*/

#ifndef __SORTING_BATCH_CONTAINER_H__
#define __SORTING_BATCH_CONTAINER_H__

#include "sorting_batch.h"
#include "sorting_kernel.h"
#include "kernel.h"
#include "homogen_numeric_table.h"

namespace daal
{
namespace algorithms
{
namespace sorting
{
template<typename algorithmFPType, Method method, CpuType cpu>
BatchContainer<algorithmFPType, method, cpu>::BatchContainer(daal::services::Environment::env *daalEnv)
{

    __DAAL_INTIALIZE_KERNELS(internal::SortingKernel, defaultDense, algorithmFPType);
}

template<typename algorithmFPType, Method method, CpuType cpu>
BatchContainer<algorithmFPType, method, cpu>::~BatchContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename algorithmFPType, Method method, CpuType cpu>
void BatchContainer<algorithmFPType, method, cpu>::compute()
{
    Result *result = static_cast<Result *>(_res);
    Input *input   = static_cast<Input *>(_in);

    daal::services::Environment::env &env = *_env;
    __DAAL_CALL_KERNEL(env, internal::SortingKernel, __DAAL_KERNEL_ARGUMENTS(defaultDense, algorithmFPType), compute, input, result);
}

} // namespace daal::algorithms::sorting

} // namespace daal::algorithms

} // namespace daal

#endif
