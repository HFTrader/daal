/* file: kernel_function_linear_base.h */
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
//  Declaration of template structs that calculate SVM Linear Kernel functions.
//--
*/

#ifndef __KERNEL_FUNCTION_LINEAR_BASE_H__
#define __KERNEL_FUNCTION_LINEAR_BASE_H__

#include "kernel_function_types_linear.h"
#include "kernel.h"

using namespace daal::internal;

namespace daal
{
namespace algorithms
{
namespace kernel_function
{
namespace linear
{
namespace internal
{

template <Method method, typename AlgorithmFPType, CpuType cpu>
struct KernelImplLinear{};

} // namespace internal

} // namespace linear

} // namespace kernel_function

} // namespace algorithms

} // namespace daal

#endif
