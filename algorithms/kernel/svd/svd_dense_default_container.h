/* file: svd_dense_default_container.h */
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
//  Implementation of svd calculation algorithm container.
//--
*/

//#include "svd.h"
#include "svd_types.h"
#include "svd_batch.h"
#include "svd_online.h"
#include "svd_distributed.h"
#include "svd_dense_default_kernel.h"
#include "kernel.h"

namespace daal
{
namespace algorithms
{
namespace svd
{

/**
 *  \brief Initialize list of cholesky kernels with implementations for supported architectures
 */
template<typename interm, Method method, CpuType cpu>
BatchContainer<interm, method, cpu>::BatchContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::SVDBatchKernel, interm, method);
}

template<typename interm, Method method, CpuType cpu>
BatchContainer<interm, method, cpu>::~BatchContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename interm, Method method, CpuType cpu>
void BatchContainer<interm, method, cpu>::compute()
{
    Input *input = static_cast<Input *>(_in);
    Result *result = static_cast<Result *>(_res);
    size_t na = input->size();
    size_t nr = result->size();
    NumericTable *a0 = static_cast<NumericTable *>(input->get(data).get());
    NumericTable **a = &a0;
    NumericTable *r[3];
    r[0] = static_cast<NumericTable *>(result->get(singularValues     ).get());
    r[1] = static_cast<NumericTable *>(result->get(leftSingularMatrix ).get());
    r[2] = static_cast<NumericTable *>(result->get(rightSingularMatrix).get());
    daal::algorithms::Parameter *par = _par;
    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::SVDBatchKernel, __DAAL_KERNEL_ARGUMENTS(interm, method), compute, na, a,
                       nr, r, par);
}

/**
 *  \brief Initialize list of cholesky kernels with implementations for supported architectures
 */
template<typename interm, Method method, CpuType cpu>
OnlineContainer<interm, method, cpu>::OnlineContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::SVDOnlineKernel, interm, method);
}

template<typename interm, Method method, CpuType cpu>
OnlineContainer<interm, method, cpu>::~OnlineContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename interm, Method method, CpuType cpu>
void OnlineContainer<interm, method, cpu>::compute()
{
    Input *input = static_cast<Input *>(_in);
    OnlinePartialResult *partialResult = static_cast<OnlinePartialResult *>(_pres);
    Parameter &kmPar = *(static_cast<Parameter *>(_par));


    size_t na = input->size();
    NumericTable *a0 = static_cast<NumericTable *>(input->get(data).get());
    NumericTable **a = &a0;

    size_t m = a0->getNumberOfColumns();
    size_t n = a0->getNumberOfRows();

    partialResult->addPartialResultStorage<interm>(m, n, kmPar);

    size_t nr = 2;
    data_management::DataCollection *rCollection = static_cast<data_management::DataCollection *>(partialResult->get(
                                                                                                      outputOfStep1ForStep2).get());
    size_t np = rCollection->size();

    NumericTable *r[2] = {0, 0};

    if( kmPar.leftSingularMatrix != notRequired )
    {
        data_management::DataCollection *qCollection
            = static_cast<data_management::DataCollection *>(partialResult->get(outputOfStep1ForStep3).get());
        r[0] = static_cast<NumericTable *>((*qCollection)[np - 1].get());
    }
    r[1] = static_cast<NumericTable *>((*rCollection)[np - 1].get());

    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::SVDOnlineKernel, __DAAL_KERNEL_ARGUMENTS(interm, method), compute, na, a,
                       nr, r, &kmPar);
}

template<typename interm, Method method, CpuType cpu>
void OnlineContainer<interm, method, cpu>::finalizeCompute()
{
    Parameter &kmPar = *(static_cast<Parameter *>(_par));
    Result *result = static_cast<Result *>(_res);
    OnlinePartialResult *partialResult = static_cast<OnlinePartialResult *>(_pres);

    data_management::DataCollection *qCollection = static_cast<data_management::DataCollection *>(partialResult->get(
                                                                                                      outputOfStep1ForStep3).get());
    data_management::DataCollection *rCollection = static_cast<data_management::DataCollection *>(partialResult->get(
                                                                                                      outputOfStep1ForStep2).get());
    size_t np = rCollection->size();

    size_t na = np * 2;
    NumericTable **a = new NumericTable*[na];
    for(size_t i = 0; i < np; i++)
    {
        a[i     ] = static_cast<NumericTable *>((*rCollection)[i].get());
        if( kmPar.leftSingularMatrix != notRequired )
        {
            a[i + np] = static_cast<NumericTable *>((*qCollection)[i].get());
        }
        else
        {
            a[i + np] = 0;
        }
    }

    size_t nr = 3;
    NumericTable *r[3];
    r[0] = static_cast<NumericTable *>(result->get(singularValues     ).get());
    r[1] = static_cast<NumericTable *>(result->get(leftSingularMatrix ).get());
    r[2] = static_cast<NumericTable *>(result->get(rightSingularMatrix).get());

    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::SVDOnlineKernel, __DAAL_KERNEL_ARGUMENTS(interm, method), finalizeCompute, na, a, nr, r, &kmPar);

    delete[] a;
}

/**
 *  \brief Initialize list of cholesky kernels with implementations for supported architectures
 */
template<typename interm, Method method, CpuType cpu>
DistributedContainer<step2Master, interm, method, cpu>::DistributedContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::SVDDistributedStep2Kernel, interm, method);
}

template<typename interm, Method method, CpuType cpu>
DistributedContainer<step2Master, interm, method, cpu>::~DistributedContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename interm, Method method, CpuType cpu>
void DistributedContainer<step2Master, interm, method, cpu>::compute()
{
    DistributedStep2Input *input = static_cast<DistributedStep2Input *>(_in);
    DistributedPartialResult *partialResult = static_cast<DistributedPartialResult *>(_pres);
    data_management::KeyValueDataCollection *inCollection =
        static_cast<data_management::KeyValueDataCollection *>(input->get(inputOfStep2FromStep1).get());

    size_t nBlocks = input->getNBlocks();
    size_t nNodes  = inCollection->size();

    data_management::KeyValueDataCollection *perNodePartials =
        static_cast<data_management::KeyValueDataCollection *>(partialResult->get(outputOfStep2ForStep3).get());
    Result                 *results         = static_cast<Result *>(partialResult->get(finalResultFromStep2Master).get());

    size_t na = nBlocks;
    NumericTable **a = new NumericTable*[nBlocks];
    size_t nr = nBlocks + 2;
    NumericTable **r = new NumericTable*[nBlocks + 2];

    r[0] = static_cast<NumericTable *>(results->get(singularValues).get());
    r[1] = static_cast<NumericTable *>(results->get(rightSingularMatrix).get());

    size_t iBlocks = 0;
    for( size_t i = 0; i < nNodes; i++ )
    {
        data_management::DataCollection *nodeCollection = static_cast<data_management::DataCollection *>((*inCollection   ).getValueByIndex(
                                                                                                             i).get());
        data_management::DataCollection *nodePartials   = static_cast<data_management::DataCollection *>((*perNodePartials).getValueByIndex(
                                                                                                             i).get());

        size_t nodeSize = nodeCollection->size();

        for( size_t j = 0 ; j < nodeSize ; j++ )
        {
            a[iBlocks + j    ] = static_cast<NumericTable *>((*nodeCollection)[j].get());
            r[iBlocks + j + 2] = static_cast<NumericTable *>((*nodePartials  )[j].get());
        }

        iBlocks += nodeSize;
    }

    daal::algorithms::Parameter *par = _par;
    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::SVDDistributedStep2Kernel, __DAAL_KERNEL_ARGUMENTS(interm, method), compute, na, a, nr, r, par);

    inCollection->clear();

    delete[] a;
    delete[] r;
}

template<typename interm, Method method, CpuType cpu>
void DistributedContainer<step2Master, interm, method, cpu>::finalizeCompute() {}

template<typename interm, Method method, CpuType cpu>
DistributedContainer<step3Local, interm, method, cpu>::DistributedContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::SVDDistributedStep3Kernel, interm, method);
}

template<typename interm, Method method, CpuType cpu>
DistributedContainer<step3Local, interm, method, cpu>::~DistributedContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template<typename interm, Method method, CpuType cpu>
void DistributedContainer<step3Local, interm, method, cpu>::compute()
{
    DistributedStep3Input *input = static_cast<DistributedStep3Input *>(_in);
    DistributedPartialResultStep3 *partialResult = static_cast<DistributedPartialResultStep3 *>(_pres);
    services::SharedPtr<data_management::DataCollection> qCollection = input->get(inputOfStep3FromStep1);
    services::SharedPtr<data_management::DataCollection> rCollection = input->get(inputOfStep3FromStep2);

    services::SharedPtr<Result> result = partialResult->get(finalResultFromStep3);

    size_t nBlocks = qCollection->size();

    size_t na = nBlocks * 2;
    NumericTable **a = new NumericTable*[na];
    for(size_t i = 0; i < nBlocks; i++)
    {
        a[i          ] = static_cast<NumericTable *>((*qCollection)[i].get());
        a[i + nBlocks] = static_cast<NumericTable *>((*rCollection)[i].get());
    }

    size_t nr = 1;
    NumericTable *r[1];
    r[0] = static_cast<NumericTable *>(result->get(leftSingularMatrix).get());

    daal::algorithms::Parameter *par = _par;
    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::SVDDistributedStep3Kernel, __DAAL_KERNEL_ARGUMENTS(interm, method), compute, na, a, nr, r, par);

    delete[] a;
}

template<typename interm, Method method, CpuType cpu>
void DistributedContainer<step3Local, interm, method, cpu>::finalizeCompute() {}

}
}
} // namespace daal
