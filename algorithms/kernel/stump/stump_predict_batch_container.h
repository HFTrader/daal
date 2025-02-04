/* file: stump_predict_batch_container.h */
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
//  Implementation of Decision Stump prediction algorithm container --
//  a class that contains Fast Decision Stump kernels for supported architectures.
//--
*/

#ifndef __STUMP_PREDICT_BATCH_CONTAINER_H__
#define __STUMP_PREDICT_BATCH_CONTAINER_H__

#include "stump_predict.h"
#include "stump_predict_kernel.h"

namespace daal
{
namespace algorithms
{
namespace stump
{
namespace prediction
{

template<typename algorithmFPType, Method method, CpuType cpu>
PredictionContainer<algorithmFPType, method, cpu>::PredictionContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::StumpPredictKernel, method, algorithmFPType);
}

template<typename algorithmFPType, Method method, CpuType cpu>
PredictionContainer<algorithmFPType, method, cpu>::~PredictionContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename algorithmFPType, Method method, CpuType cpu>
void PredictionContainer<algorithmFPType, method, cpu>::compute()
{
    classifier::prediction::Input *input = static_cast<classifier::prediction::Input *>(_in);
    classifier::prediction::Result *result = static_cast<classifier::prediction::Result *>(_res);

    size_t nr = result->size();

    NumericTable *a = static_cast<NumericTable *>(input->get(classifier::prediction::data).get());
    stump::Model *m = static_cast<stump::Model *>(input->get(classifier::prediction::model).get());
    NumericTable *r[] = { static_cast<NumericTable *>(result->get(classifier::prediction::prediction).get()) };

    daal::services::Environment::env &env = *_env;
    __DAAL_CALL_KERNEL(env, internal::StumpPredictKernel, __DAAL_KERNEL_ARGUMENTS(method, algorithmFPType), compute, a, m, nr, r, NULL);
}

} // daal::algorithms::stump::prediction
}
}
} // namespace daal

#endif
