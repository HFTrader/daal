/* file: kernel_function_linear_dense_default_batch_fpt_dispatcher.cpp */
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
//  Implementation of linear kernel function container for dense input data.
//--
*/

#include "kernel_function_linear.h"
#include "kernel_function_linear_batch_container.h"
#include "kernel_function_linear_dense_default_kernel.h"

namespace daal
{
namespace algorithms
{
namespace interface1
{
__DAAL_INSTANTIATE_DISPATCH_CONATINER(kernel_function::linear::BatchContainer, batch, DAAL_FPTYPE, kernel_function::linear::defaultDense)
}
} // namespace algorithms
} // namespace daal
