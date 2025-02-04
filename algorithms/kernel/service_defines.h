/* file: service_defines.h */
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
//  Declaration of service constants
//--
*/

#ifndef __SERVICE_DEFINES_H__
#define __SERVICE_DEFINES_H__

#include "services/env_detect.h"

int __daal_serv_cpu_detect(int );

#if defined(_MSC_VER)
#define PRAGMA_IVDEP
#define PRAGMA_VECTOR_UNALIGNED
#define PRAGMA_VECTOR_ALWAYS
#define PRAGMA_SIMD_ASSERT
#else
#define PRAGMA_IVDEP _Pragma("ivdep")
#define PRAGMA_VECTOR_UNALIGNED _Pragma("vector unaligned")
#define PRAGMA_VECTOR_ALWAYS _Pragma("vector always")
#define PRAGMA_SIMD_ASSERT _Pragma("simd assert")
#endif

namespace daal
{

/* Execution if(!this->_errors->isEmpty()) */
enum ServiceStatus
{
    SERV_ERR_OK = 0,
    SERV_ERR_MKL_SVD_ITH_PARAM_ILLEGAL_VALUE,
    SERV_ERR_MKL_SVD_XBDSQR_DID_NOT_CONVERGE,
    SERV_ERR_MKL_QR_ITH_PARAM_ILLEGAL_VALUE,
    SERV_ERR_MKL_QR_XBDSQR_DID_NOT_CONVERGE
};

/** Data storage format */
enum DataFormat
{
    dense   = 0,    /*!< Dense storage format */
    CSR     = 1     /*!< Compressed Sparse Rows (CSR) storage format */
};

}

#endif
