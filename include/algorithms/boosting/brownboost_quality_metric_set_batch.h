/* file: brownboost_quality_metric_set_batch.h */
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
//  Interface for the BrownBoost quality metric set.
//--
*/

#ifndef __BROWNBOOST_QUALITY_METRIC_SET_BATCH_H__
#define __BROWNBOOST_QUALITY_METRIC_SET_BATCH_H__

#include "algorithms/algorithm_quality_metric_set_batch.h"
#include "algorithms/classifier/binary_confusion_matrix_batch.h"
#include "algorithms/boosting/brownboost_quality_metric_set_types.h"

namespace daal
{
namespace algorithms
{
namespace brownboost
{
/**
 * \brief Contains classes for checking the quality of the model trained with the BrownBoost algorithm
 */
namespace quality_metric_set
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__BROWNBOOST__QUALITY_METRIC_SET__BATCH"></a>
 * \brief Class that represents a set of quality metrics to check the model trained with the BrownBoost algorithm
 *
 * \par Enumerations
 *      - \ref QualityMetricId  Quality metrics provided by the library
 *
 * \par References
 *      - \ref algorithms::quality_metric_set::interface1::InputAlgorithmsCollection "algorithms::quality_metric_set::InputAlgorithmsCollection" class
 *      - InputDataCollection class
 *      - ResultCollection class
 */
class Batch : public algorithms::quality_metric_set::Batch
{
public:
    /**
     * Constructs a quality metric set for the model trained with the BrownBoost algorithm
     * \param[in] useDefaultMetrics     Flag. If true, a quality metric set is initialized with the quality metrics provided by the library
     */
    Batch(bool useDefaultMetrics = true) : algorithms::quality_metric_set::Batch(useDefaultMetrics)
    {
        _inputData = services::SharedPtr<InputDataCollection>(new InputDataCollection());
        if (_useDefaultMetrics)
        {
            initializeQualityMetrics();
        }
        _resultCollection = services::SharedPtr<ResultCollection>(new ResultCollection());
    }

    virtual ~Batch() {}

    /**
     * Returns the structure that contains a computed quality metric set
     * \return Structure that contains a computed quality metric set
     */
    services::SharedPtr<ResultCollection> getResultCollection()
    {
        return services::staticPointerCast<ResultCollection,
                                           algorithms::quality_metric_set::ResultCollection>(_resultCollection);
    }

    /**
     * Returns the collection of input objects of the quality metrics algorithm
     * \return Collection of input objects of the quality metrics algorithm
     */
    services::SharedPtr<InputDataCollection> getInputDataCollection()
    {
        return services::staticPointerCast<InputDataCollection,
                                           algorithms::quality_metric_set::InputDataCollection>(_inputData);
    }

protected:
    virtual void initializeQualityMetrics()
    {
        inputAlgorithms[confusionMatrix] = services::SharedPtr<classifier::quality_metric::binary_confusion_matrix::Batch<> >(
                new classifier::quality_metric::binary_confusion_matrix::Batch<>());
        _inputData->add(confusionMatrix, services::SharedPtr<algorithms::Input>(
                new classifier::quality_metric::binary_confusion_matrix::Input));
    }
};
} // namespace interface1
using interface1::Batch;

}
}
}
}
#endif
