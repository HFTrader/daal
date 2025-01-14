/* file: kernel.h */
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
//  Defines used for kernel allocation, deallocation and calling kernel methods
//--
*/

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "daal_defines.h"
#include "service_defines.h"

#undef __DAAL_INTIALIZE_KERNELS
#define __DAAL_INTIALIZE_KERNELS(KernelClass, ...)        \
    {                                                     \
        _kernel = (new KernelClass<__VA_ARGS__, cpu>);    \
    }

#undef __DAAL_DEINTIALIZE_KERNELS
#define __DAAL_DEINTIALIZE_KERNELS()    \
    {                                   \
        if(_kernel) delete _kernel;     \
    }

#undef __DAAL_KERNEL_ARGUMENTS
#define __DAAL_KERNEL_ARGUMENTS(...) __VA_ARGS__

#undef __DAAL_CALL_KERNEL
#define __DAAL_CALL_KERNEL(env, KernelClass, templateArguments, method, ...)            \
    {                                                                                   \
        ((KernelClass<templateArguments, cpu> *)(_kernel))->method(__VA_ARGS__);        \
    }

#define __DAAL_INSTANTIATE_DISPATCH_CONATINER(ContainerTemplate, Mode, ...)                                     \
template<>                                                                                                      \
AlgorithmDispatchContainer< Mode,                                                                               \
         ContainerTemplate<__VA_ARGS__, sse2>,      ContainerTemplate<__VA_ARGS__, ssse3>,                      \
         ContainerTemplate<__VA_ARGS__, sse42>,     ContainerTemplate<__VA_ARGS__, avx>,                        \
         ContainerTemplate<__VA_ARGS__, avx2>,      ContainerTemplate<__VA_ARGS__, avx512_mic>,                 \
         ContainerTemplate<__VA_ARGS__, avx512> >::                                                             \
AlgorithmDispatchContainer(daal::services::Environment::env *daalEnv) : AlgorithmContainerIface<Mode>(daalEnv)  \
{                                                                                                               \
    switch (daalEnv->cpuid)                                                                                     \
    {                                                                                                           \
        case avx512:     _cntr = (new ContainerTemplate<__VA_ARGS__, avx512>    (daalEnv)); break;              \
        case avx512_mic: _cntr = (new ContainerTemplate<__VA_ARGS__, avx512_mic>(daalEnv)); break;              \
        case avx2:       _cntr = (new ContainerTemplate<__VA_ARGS__, avx2>      (daalEnv)); break;              \
        case avx:        _cntr = (new ContainerTemplate<__VA_ARGS__, avx>       (daalEnv)); break;              \
        case sse42:      _cntr = (new ContainerTemplate<__VA_ARGS__, sse42>     (daalEnv)); break;              \
        case ssse3:      _cntr = (new ContainerTemplate<__VA_ARGS__, ssse3>     (daalEnv)); break;              \
        case sse2:       _cntr = (new ContainerTemplate<__VA_ARGS__, sse2>      (daalEnv)); break;              \
    }                                                                                                           \
}                                                                                                               \
                                                                                                                \
template                                                                                                        \
class AlgorithmDispatchContainer< Mode,                                                                         \
         ContainerTemplate<__VA_ARGS__, sse2>,        ContainerTemplate<__VA_ARGS__, ssse3>,                    \
         ContainerTemplate<__VA_ARGS__, sse42>,       ContainerTemplate<__VA_ARGS__, avx>,                      \
         ContainerTemplate<__VA_ARGS__, avx2>,        ContainerTemplate<__VA_ARGS__, avx512_mic>,               \
         ContainerTemplate<__VA_ARGS__, avx512> >;

#endif
