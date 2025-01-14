/* file: covariance_kernel.h */
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
//  Declaration of template structs that calculate Covariance matrix.
//--
*/


#ifndef __COVARIANCE_KERNEL_H__
#define __COVARIANCE_KERNEL_H__

#include "numeric_table.h"
#include "algorithm_base_common.h"
#include "covariance_types.h"

using namespace daal::services;
using namespace daal::data_management;

namespace daal
{
namespace algorithms
{
namespace covariance
{
namespace internal
{

template<typename algorithmFPType, Method method, CpuType cpu>
class CovarianceDenseBatchKernel : public daal::algorithms::Kernel
{
public:
    void compute(SharedPtr<NumericTable> &dataTable, SharedPtr<NumericTable> &covTable,
            SharedPtr<NumericTable> &meanTable, const Parameter *parameter);
};

template<typename algorithmFPType, Method method, CpuType cpu>
class CovarianceCSRBatchKernel : public daal::algorithms::Kernel
{
public:
    void compute(SharedPtr<NumericTable> &dataTable, SharedPtr<NumericTable> &covTable,
            SharedPtr<NumericTable> &meanTable, const Parameter *parameter);
};

template<typename algorithmFPType, Method method, CpuType cpu>
class CovarianceDenseOnlineKernel : public daal::algorithms::Kernel
{
public:
    void compute(SharedPtr<NumericTable> &dataTable, SharedPtr<NumericTable> &nObsTable,
            SharedPtr<NumericTable> &crossProductTable, SharedPtr<NumericTable> &sumTable,
            const Parameter *parameter);

    void finalizeCompute(SharedPtr<NumericTable> &nObsTable, SharedPtr<NumericTable> &crossProductTable,
            SharedPtr<NumericTable> &sumTable, SharedPtr<NumericTable> &covTable,
            SharedPtr<NumericTable> &meanTable, const Parameter *parameter);
};

template<typename algorithmFPType, Method method, CpuType cpu>
class CovarianceCSROnlineKernel : public daal::algorithms::Kernel
{
public:
    void compute(SharedPtr<NumericTable> &dataTable, SharedPtr<NumericTable> &nObsTable,
            SharedPtr<NumericTable> &crossProductTable, SharedPtr<NumericTable> &sumTable,
            const Parameter *parameter);

    void finalizeCompute(SharedPtr<NumericTable> &nObsTable, SharedPtr<NumericTable> &crossProductTable,
            SharedPtr<NumericTable> &sumTable, SharedPtr<NumericTable> &covTable,
            SharedPtr<NumericTable> &meanTable, const Parameter *parameter);
};

template<typename algorithmFPType, Method method, CpuType cpu>
class CovarianceDistributedKernel : public daal::algorithms::Kernel
{
public:
    void compute(SharedPtr<DataCollection> &partialResultsCollection,
            SharedPtr<NumericTable> &nObsTable, SharedPtr<NumericTable> &crossProductTable,
            SharedPtr<NumericTable> &sumTable, const Parameter *parameter);

    void finalizeCompute(SharedPtr<NumericTable> &nObsTable, SharedPtr<NumericTable> &crossProductTable,
            SharedPtr<NumericTable> &sumTable, SharedPtr<NumericTable> &covTable,
            SharedPtr<NumericTable> &meanTable, const Parameter *parameter);
};

} // namespace internal
} // namespace covariance
} // namespace algorithms
} // namespace daal

#endif
