/* file: kmeans_init_kernel.h */
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
//  Declaration of template function that computes K-means.
//--
*/

#ifndef _KMEANS_init_H
#define _KMEANS_init_H

#include "kmeans_init_types.h"
#include "kernel.h"
#include "numeric_table.h"

using namespace daal::data_management;

namespace daal
{
namespace algorithms
{
namespace kmeans
{
namespace init
{
namespace internal
{

template <Method method, typename interm, CpuType cpu>
class KMeansinitKernel: public Kernel
{
public:
    void compute(size_t na, const NumericTable *const *a, size_t nr, const NumericTable *const *r, const Parameter *par);
};

template <Method method, typename interm, CpuType cpu>
class KMeansinitStep1LocalKernel: public Kernel
{
public:
    void compute(size_t na, const NumericTable *const *a, size_t nr, const NumericTable *const *r, const Parameter *par);
    void finalizeCompute(size_t na, const NumericTable *const *a, size_t nr, const NumericTable *const *r, const Parameter *par);
};

template <Method method, typename interm, CpuType cpu>
class KMeansinitStep2MasterKernel: public Kernel
{
public:
    void compute(size_t na, const NumericTable *const *a, size_t nr, const NumericTable *const *r, const Parameter *par);
    void finalizeCompute(size_t na, const NumericTable *const *a, size_t nr, const NumericTable *const *r, const Parameter *par);
};

} // namespace daal::algorithms::kmeans::init::internal
} // namespace daal::algorithms::kmeans::init
} // namespace daal::algorithms::kmeans
} // namespace daal::algorithms
} // namespace daal

#endif
