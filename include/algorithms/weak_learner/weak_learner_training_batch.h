/* file: weak_learner_training_batch.h */
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
//  Implementation of base classes defining the interface for training the
//  weak learner model in the batch processing mode.
//--
*/

#ifndef __WEAK_LEARNER_TRAINING_BATCH_H__
#define __WEAK_LEARNER_TRAINING_BATCH_H__

#include "algorithms/classifier/classifier_training_batch.h"
#include "algorithms/weak_learner/weak_learner_training_types.h"

namespace daal
{
namespace algorithms
{
namespace weak_learner
{
namespace training
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__WEAK_LEARNER__TRAINING__BATCH"></a>
 * \brief %Base class for training the weak learner model in the batch processing mode
 *
 * \par Enumerations
 *      - \ref classifier::training::InputId  Identifiers of input objects
 *      - \ref classifier::training::ResultId Identifiers of results
 *
 * \par References
 *      - \ref interface1::Input "Input" class
 *      - \ref interface1::Model "Model" class
 *      - Result class
 */
class DAAL_EXPORT Batch : public classifier::training::Batch
{
public:
    Batch() {}

    /**
     * Constructs algorithm for training the weak learner model
     * by copying input objects and parameters of another algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch &other) : classifier::training::Batch(other) {}

    virtual ~Batch() {}

    /**
     * Provides memory for storing weak learner results
     * \param[in] result    Structure for storing weak learner results
     */
    void setResult(services::SharedPtr<weak_learner::training::Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns structure that contains computed weak learner results
     * \return Structure that contains computed weak learner results
     */
    services::SharedPtr<weak_learner::training::Result> getResult()
    {
        return services::staticPointerCast<weak_learner::training::Result, classifier::training::Result>(_result);
    }

    /**
     * Returns a pointer to the newly allocated algorithm for training the weak learner model
     * with a copy of input objects and parameters of this algorithm
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

} // namespace daal::algorithms::weak_learner::training
}
}
} // namespace daal
#endif // __WEAK_LEARNER_TRAINING_BATCH_H__
