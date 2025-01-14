/* file: naivebayes_predict_kernel.h */
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
//  Declaration of template function that computes K-means.
//--
*/

#ifndef _NAIVEBAYES_ASSIGN_FPK_H
#define _NAIVEBAYES_ASSIGN_FPK_H

#include "multinomial_naive_bayes_model.h"
#include "multinomial_naive_bayes_predict_types.h"
#include "kernel.h"
#include "numeric_table.h"

using namespace daal::data_management;

namespace daal
{
namespace algorithms
{
namespace multinomial_naive_bayes
{
namespace prediction
{
namespace internal
{

template <typename intFPtype, Method method, CpuType cpu>
class NaiveBayesPredictKernel : public Kernel
{
public:
    void compute(const NumericTable *a, const daal::algorithms::Model *m, size_t nr, NumericTable *r[],
                 const daal::algorithms::Parameter *par);
};

} // namespace internal

} // namespace prediction

} // namespace multinomial_naive_bayes

} // namespace algorithms

} // namespace daal


#endif
