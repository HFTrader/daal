/* file: multiclass_confusion_matrix_dense_default_batch_fpt_dispatcher.cpp */
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
//  Instantiation of the container for the multi-class confusion matrix.
//--
*/

#include "multiclass_confusion_matrix_dense_default_batch_container.h"

namespace daal
{
namespace algorithms
{
namespace interface1
{
__DAAL_INSTANTIATE_DISPATCH_CONATINER(classifier::quality_metric::multiclass_confusion_matrix::BatchContainer, batch, DAAL_FPTYPE,  \
    classifier::quality_metric::multiclass_confusion_matrix::defaultDense)
}
}
}
