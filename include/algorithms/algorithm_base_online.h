/* file: algorithm_base_online.h */
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
//  Implementation of base classes defining algorithm interface.
//--
*/

#ifndef __ALGORITHM_BASE_STREAM_H__
#define __ALGORITHM_BASE_STREAM_H__

namespace daal
{
namespace algorithms
{
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__ALGORITHMCONTAINERIFACE"></a>
 * \brief Abstract interface class that provides virtual methods to access and run implementations
 *        of the algorithms in %online mode. It is associated with the Algorithm<online> class
 *        and supports the methods for computation and finalization of the algorithm results
 *        in online mode.
 *        The methods of the container are defined in derivative containers defined for each algorithm.
 */
template class AlgorithmContainerIface<online>;
/**
 * <a name="DAAL-CLASS-ALGORITHMS__ALGORITHM"></a>
 * \brief Implements the abstract interface AlgorithmIface. Algorithm<online> is, in turn, the base class
 *        for the classes interfacing the major stages of data processing in %online mode:
 *        Analysis<online> and Training<online>.
 */
template class Algorithm<online>;
}
}
}
#endif
