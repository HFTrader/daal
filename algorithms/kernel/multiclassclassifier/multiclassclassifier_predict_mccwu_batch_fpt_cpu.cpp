/* file: multiclassclassifier_predict_mccwu_batch_fpt_cpu.cpp */
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
//  Implementation of Wu method for Multi-class classifier
//  prediction algorithm for AVX2.
//--
*/

#include "multiclassclassifier_predict_batch_container.h"
#include "multiclassclassifier_predict_kernel.h"
#include "multiclassclassifier_predict_mccwu_kernel.h"
#include "multiclassclassifier_predict_mccwu_impl.i"

namespace daal
{
namespace algorithms
{
namespace multi_class_classifier
{
namespace prediction
{
namespace interface1
{
template class PredictionContainer<DAAL_FPTYPE, multiClassClassifierWu, training::oneAgainstOne, DAAL_CPU>;
}
namespace internal
{
template class MultiClassClassifierPredictKernel<multiClassClassifierWu, training::oneAgainstOne, DAAL_FPTYPE, DAAL_CPU>;
} // namespace internal
} // namespace prediction
} // namespace multi_class_classifier
} // namespace algorithms
} // namespace daal
