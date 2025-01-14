/* file: naivebayes_predict_container.h */
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
//  Implementation of K-means algorithm container -- a class that contains
//  Lloyd K-means kernels for supported architectures.
//--
*/

#include "multinomial_naive_bayes_predict.h"
#include "naivebayes_predict_kernel.h"

namespace daal
{
namespace algorithms
{
namespace multinomial_naive_bayes
{
namespace prediction
{

template <typename interm, Method method, CpuType cpu>
PredictionContainer<interm, method, cpu>::PredictionContainer(daal::services::Environment::env *daalEnv) : PredictionContainerIface()
{
    __DAAL_INTIALIZE_KERNELS(internal::NaiveBayesPredictKernel, interm, method);
}

template <typename interm, Method method, CpuType cpu>
PredictionContainer<interm, method, cpu>::~PredictionContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template <typename interm, Method method, CpuType cpu>
void PredictionContainer<interm, method, cpu>::compute()
{
    classifier::prediction::Input *input = static_cast<classifier::prediction::Input *>(_in);
    classifier::prediction::Result *result = static_cast<classifier::prediction::Result *>(_res);

    NumericTable *a = static_cast<NumericTable *>(input->get(classifier::prediction::data).get());
    multinomial_naive_bayes::Model *m = static_cast<multinomial_naive_bayes::Model *>(input->get(classifier::prediction::model).get());
    NumericTable *r[1];
    r[0] = static_cast<NumericTable *>(result->get(classifier::prediction::prediction).get());

    multinomial_naive_bayes::Parameter *par = static_cast<multinomial_naive_bayes::Parameter *>(_par);
    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::NaiveBayesPredictKernel, __DAAL_KERNEL_ARGUMENTS(interm, method), compute, a, m, 1, r, par);
}

} // namespace prediction
} // namespace multinomial_naive_bayes
} // namespace algorithms
} // namespace daal
