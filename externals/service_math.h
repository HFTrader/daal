/* file: service_math.h */
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
//  Template wrappers for math functions.
//--
*/

#ifndef __SERVICE_MATH_H__
#define __SERVICE_MATH_H__

#include "service_defines.h"
#include "service_math_mkl.h"

namespace daal
{
namespace internal
{

/*
// Template functions definition
*/
template<typename fpType, CpuType cpu, template<typename, CpuType> class _impl=mkl::MklMath>
struct Math
{
    typedef typename _impl<fpType,cpu>::SizeType SizeType;

    static fpType sFabs(fpType in)
    {
        return _impl<fpType,cpu>::sFabs(in);
    }

    static fpType sMin(fpType in1, fpType in2)
    {
        return _impl<fpType,cpu>::sMin(in1, in2);
    }

    static fpType sMax(fpType in1, fpType in2)
    {
        return _impl<fpType,cpu>::sMax(in1, in2);
    }

    static fpType sSqrt(fpType in)
    {
        return _impl<fpType,cpu>::sSqrt(in);
    }

    static fpType sPowx(fpType in, fpType in1)
    {
        return _impl<fpType,cpu>::sPowx(in, in1);
    }

    static fpType sCeil(fpType in)
    {
        return _impl<fpType,cpu>::sCeil(in);
    }

    static fpType sErfInv(fpType in)
    {
        return _impl<fpType,cpu>::sErfInv(in);
    }

    static fpType sLog(fpType in)
    {
        return _impl<fpType,cpu>::sLog(in);
    }

    static void vPowx(SizeType n, fpType *in, fpType in1, fpType *out)
    {
        _impl<fpType,cpu>::vPowx(n, in, in1, out);
    }

    static void vCeil(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vCeil(n, in, out);
    }

    static void vErfInv(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vErfInv(n, in, out);
    }

    static void vErf(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vErf(n, in, out);
    }

    static void vExp(SizeType n, fpType* in, fpType* out)
    {
        _impl<fpType,cpu>::vExp(n, in, out);
    }

    static void vTanh(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vTanh(n, in, out);
    }

    static void vSqrt(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vSqrt(n, in, out);
    }

    static void vLog(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vLog(n, in, out);
    }

    static void vLog1p(SizeType n, fpType *in, fpType *out)
    {
        _impl<fpType,cpu>::vLog1p(n, in, out);
    }

};

} // namespace internal
} // namespace daal

#endif
