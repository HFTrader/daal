/* file: outlierdetection_multivariate_dense_bacon_kernel.h */
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
//  Declaration of template structs for multivariate outlier detection
//--
*/

#ifndef __MULTIVARIATE_OUTLIER_DETECTION_DENSE_BACON_KERNEL_H__
#define __MULTIVARIATE_OUTLIER_DETECTION_DENSE_BACON_KERNEL_H__

#include "numeric_table.h"
#include "outlier_detection_multivariate_types.h"

#include "service_micro_table.h"
#include "service_numeric_table.h"
#include "service_math.h"

#include "outlierdetection_multivariate_kernel.h"

using namespace daal::internal;
using namespace daal::data_management;

namespace daal
{
namespace algorithms
{
namespace multivariate_outlier_detection
{
namespace internal
{

template <typename AlgorithmFPType, CpuType cpu>
struct OutlierDetectionKernel<AlgorithmFPType, baconDense, cpu> : public Kernel
{
    void compute(const NumericTable *a, NumericTable *r, const daal::algorithms::Parameter *par);
};

} // namespace internal

} // namespace multivariate_outlier_detection

} // namespace algorithms

} // namespace daal

#endif
