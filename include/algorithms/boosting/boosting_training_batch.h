/* file: boosting_training_batch.h */
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
//  Implementation of base classes defining interface for training models
//  of the Boosting algorithms in batch mode.
//--
*/

#ifndef __BOOSTING_TRAINING_BATCH_H__
#define __BOOSTING_TRAINING_BATCH_H__

#include "algorithms/algorithm.h"
#include "algorithms/classifier/classifier_training_batch.h"

namespace daal
{
namespace algorithms
{
namespace boosting
{
/**
 * \brief Contains classes for training %boosting models.
 */
namespace training
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__BOOSTING__TRAINING__BATCH"></a>
 * \brief %Base class for training models of %boosting algorithms in the batch processing mode
 *
  * \par Enumerations
 *      - \ref classifier::training::InputId  Identifiers of input objects for %boosting algorithms
 *      - \ref classifier::training::ResultId Result identifiers for %boosting algorithm training
 *
 * \par References
 *      - \ref classifier::training::interface1::Input "classifier::training::Input" class
 *      - \ref classifier::training::interface1::Result "classifier::training::Result" class
 */
class DAAL_EXPORT Batch : public classifier::training::Batch
{
public:
    Batch() {}

    /**
     * Constructs a %boosting classifier training algorithm by copying input objects and parameters
     * of another %boosting classifier training algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch &other) : classifier::training::Batch(other) {}

    virtual ~Batch() {}

    /**
     * Returns a pointer to the newly allocated %boosting classifier training algorithm with a copy of input objects
     * and parameters of this %boosting classifier training algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch> clone() const
    {
        return services::SharedPtr<Batch>(cloneImpl());
    }

protected:
    virtual Batch * cloneImpl() const DAAL_C11_OVERRIDE = 0;
};
} // namespace interface1
using interface1::Batch;

} // namespace daal::algorithms::boosting::training
}
}
}
#endif // __BOOSTING_TRAINING_BATCH_H__
