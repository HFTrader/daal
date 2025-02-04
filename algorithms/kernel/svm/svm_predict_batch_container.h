/* file: svm_predict_batch_container.h */
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
//  Implementation of SVM prediction algorithm container.
//--
*/

#include "svm_predict.h"
#include "svm_predict_kernel.h"
#include "classifier_predict_types.h"

namespace daal
{
namespace algorithms
{
namespace svm
{
namespace prediction
{
/**
*  \brief Initialize list of SVM kernels with implementations for supported architectures
*/
template<typename AlgorithmFPType, Method method, CpuType cpu>
PredictionContainer<AlgorithmFPType, method, cpu>::PredictionContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::SVMPredictImpl, method, AlgorithmFPType);
}

template<typename AlgorithmFPType, Method method, CpuType cpu>
PredictionContainer<AlgorithmFPType, method, cpu>::~PredictionContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename AlgorithmFPType, Method method, CpuType cpu>
void PredictionContainer<AlgorithmFPType, method, cpu>::compute()
{
    classifier::prediction::Input *input = static_cast<classifier::prediction::Input *>(_in);
    classifier::prediction::Result *result = static_cast<classifier::prediction::Result *>(_res);

    services::SharedPtr<NumericTable> a = input->get(classifier::prediction::data);
    daal::algorithms::Model *m = static_cast<daal::algorithms::Model *>(input->get(classifier::prediction::model).get());
    services::SharedPtr<NumericTable> r = result->get(classifier::prediction::prediction);

    daal::algorithms::Parameter *par = _par;
    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::SVMPredictImpl, __DAAL_KERNEL_ARGUMENTS(method, AlgorithmFPType), compute, a, m, r, par);
}

} // namespace prediction
} // namespace svm
} // namespace algorithms
} // namespace daal
