/* file: kernel_function_types_rbf.h */
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
//  Kernel function parameter structure
//--
*/

#ifndef __KERNEL_FUNCTION_TYPES_RBF_H__
#define __KERNEL_FUNCTION_TYPES_RBF_H__

#include "algorithms/kernel_function/kernel_function_types.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes for computing kernel functions
 */
namespace kernel_function
{
/**
 * \brief Contains classes for computing the radial basis function (RBF) kernel
 */
namespace rbf
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__KERNEL_FUNCTION__RBF__METHOD"></a>
 * Method for computing  kernel functions
 */
enum Method
{
    defaultDense = 0,    /*!< Default method for computing the RBF kernel */
    fastCSR = 1          /*!< Fast: performance-oriented method. Works with Compressed Sparse Rows (CSR) numeric tables */
};

/**
 * \brief Contains version 1.0 of the Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__KERNEL_FUNCTION__RBF__PARAMETER"></a>
 * \brief Parameters for the radial basis function (RBF) kernel
 *
 * \snippet kernel_function/kernel_function_types_rbf.h RBF input object source code
 */
/* [RBF input object source code] */
struct DAAL_EXPORT Parameter : public ParameterBase
{
    Parameter(double sigma = 1.0) : ParameterBase(), sigma(sigma) {}
    double sigma;   /*!< RBF kernel coefficient */
};
/* [RBF input object source code] */
} // namespace interface1
using interface1::Parameter;

} // rbf
} // namespace kernel_function
} // namespace algorithms
} // namespace daal
#endif
