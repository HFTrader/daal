/* file: pca_dense_svd_online_container.h */
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
//  Implementation of PCA Correlation algorithm container.
//--
*/

#ifndef __PCA_DENSE_SVD_ONLINE_CONTAINER_H__
#define __PCA_DENSE_SVD_ONLINE_CONTAINER_H__

#include "kernel.h"
#include "pca_online.h"
#include "pca_dense_svd_online_kernel.h"
#include "pca_dense_svd_container.h"

namespace daal
{
namespace algorithms
{
namespace pca
{

template <typename algorithmFPType, CpuType cpu>
OnlineContainer<algorithmFPType, svdDense, cpu>::OnlineContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INTIALIZE_KERNELS(internal::PCASVDOnlineKernel, algorithmFPType);
}

template <typename algorithmFPType, CpuType cpu>
OnlineContainer<algorithmFPType, svdDense, cpu>::~OnlineContainer()
{
    __DAAL_DEINTIALIZE_KERNELS();
}

template <typename algorithmFPType, CpuType cpu>
void OnlineContainer<algorithmFPType, svdDense, cpu>::compute()
{
    Input *input = static_cast<Input *>(_in);
    internal::InputDataType dtype = getInputDataType(input);

    PartialResult<svdDense> *partialResult = static_cast<PartialResult<svdDense> *>(_pres);

    services::SharedPtr<data_management::NumericTable> data = input->get(pca::data);

    services::SharedPtr<data_management::NumericTable> nObservations = partialResult->get(pca::nObservationsSVD);
    services::SharedPtr<data_management::NumericTable> sumSquaresSVD = partialResult->get(pca::sumSquaresSVD);
    services::SharedPtr<data_management::NumericTable> sumSVD = partialResult->get(pca::sumSVD);

    services::SharedPtr<data_management::DataCollection> rCollection = partialResult->get(auxiliaryData);
    size_t nFeatures = sumSquaresSVD.get()->getNumberOfColumns();
    services::SharedPtr<data_management::NumericTable> auxiliaryTable(
        new data_management::HomogenNumericTable<algorithmFPType>(nFeatures, nFeatures, data_management::NumericTableIface::doAllocate));
    rCollection->push_back(auxiliaryTable);

    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::PCASVDOnlineKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFPType), setType, dtype);
    __DAAL_CALL_KERNEL(env, internal::PCASVDOnlineKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFPType), compute,
                       data, nObservations, auxiliaryTable, sumSVD, sumSquaresSVD);
}

template <typename algorithmFPType, CpuType cpu>
void OnlineContainer<algorithmFPType, svdDense, cpu>::finalizeCompute()
{
    Input *input = static_cast<Input *>(_in);
    internal::InputDataType dtype = getInputDataType(input);

    services::SharedPtr<data_management::DataCollection> rCollection;
    Result *result = static_cast<Result *>(_res);

    PartialResult<svdDense> *partialResult = static_cast<PartialResult<svdDense> *>(_pres);

    services::SharedPtr<data_management::NumericTable> nObservations = partialResult->get(pca::nObservationsSVD);

    rCollection = partialResult->get(auxiliaryData);

    services::SharedPtr<data_management::NumericTable> eigenvalues  = result->get(pca::eigenvalues);
    services::SharedPtr<data_management::NumericTable> eigenvectors = result->get(pca::eigenvectors);

    data_management::NumericTable *inputs[1];
    size_t na = 1;
    inputs[0] = nObservations.get();

    data_management::NumericTable *results[2];
    size_t nr = 2;
    results[0] = eigenvectors.get();
    results[1] = eigenvalues.get();

    daal::services::Environment::env &env = *_env;

    __DAAL_CALL_KERNEL(env, internal::PCASVDOnlineKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFPType), setType, dtype);
    __DAAL_CALL_KERNEL(env, internal::PCASVDOnlineKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFPType), finalizeMerge,
                       nObservations, eigenvalues, eigenvectors, rCollection);
}

}
}
} // namespace daal
#endif
