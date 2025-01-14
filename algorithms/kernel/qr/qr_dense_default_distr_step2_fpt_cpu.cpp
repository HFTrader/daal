/* file: qr_dense_default_distr_step2_fpt_cpu.cpp */
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
//  Instantiation of QR algorithm classes.
//--
*/

#include "qr_dense_default_kernel.h"
#include "qr_dense_default_distr_impl.i"
#include "qr_dense_default_container.h"

namespace daal
{
namespace algorithms
{
namespace qr
{
namespace interface1
{
template class DistributedContainer<step2Master, DAAL_FPTYPE, daal::algorithms::qr::defaultDense, DAAL_CPU>;
}
namespace internal
{
template class QRDistributedStep2Kernel<DAAL_FPTYPE, defaultDense, DAAL_CPU>;
}
}
}
}
