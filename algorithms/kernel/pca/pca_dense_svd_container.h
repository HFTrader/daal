/* file: pca_dense_svd_container.h */
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

#ifndef __PCA_DENSE_SVD_CONTAINER_H__
#define __PCA_DENSE_SVD_CONTAINER_H__

namespace daal
{
namespace algorithms
{
namespace pca
{
static inline internal::InputDataType getInputDataType(pca::Input *input)
{
    if(input == 0 || input->size() == 0)
    {
        return internal::nonNormalizedDataset;
    }

    data_management::NumericTable *a = static_cast<data_management::NumericTable *>(input->get(data).get());
    if(input->isCorrelation())
    {
        return internal::correlation;
    }
    else if(a->isNormalized(data_management::NumericTableIface::standardScoreNormalized))
    {
        return internal::normalizedDataset;
    }
    else
    {
        return internal::nonNormalizedDataset;
    }
}

}
}
} // namespace daal
#endif
