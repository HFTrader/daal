/* file: cross_entropy_dense_default_batch_kernel.h */
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

//++
//  Declaration of template function that calculate cross_entropy.
//--


#ifndef __CROSS_ENTROPY_FPK_H__
#define __CROSS_ENTROPY_FPK_H__

#include "cross_entropy_batch.h"
#include "kernel.h"
#include "numeric_table.h"

using namespace daal::data_management;

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
/**
 *  \brief Kernel for cross_entropy calculation
 *  in case floating point type of intermediate calculations
 *  and method of calculations are different
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class CrossEntropyKernel : public Kernel
{
public:
    void compute(Input *input, objective_function::Result *result, Parameter *parameter);
};

} // namespace cross_entropy
} // namespace internal
} // namespace optimization_solver
} // namespace algorithm
} // namespace daal

#endif
