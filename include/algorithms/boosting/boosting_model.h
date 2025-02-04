/* file: boosting_model.h */
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
//  Implementation of the base class defining Boosting algorithm model.
//--
*/

#ifndef __BOOSTING_MODEL_H__
#define __BOOSTING_MODEL_H__

#include "algorithms/weak_learner/weak_learner_model.h"
#include "algorithms/weak_learner/weak_learner_training_batch.h"
#include "algorithms/weak_learner/weak_learner_predict.h"
#include "algorithms/stump/stump_training_batch.h"
#include "algorithms/stump/stump_predict.h"
#include "algorithms/classifier/classifier_model.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes of boosting classification algorithms
 */
namespace boosting
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__BOOSTING__PARAMETER"></a>
* \brief %Base class for parameters of the %boosting algorithm
 *
 * \snippet boosting/boosting_model.h Parameter source code
 */
/* [Parameter source code] */
struct Parameter : public classifier::Parameter
{
    /** Default constructor. Sets the decision stump as the default weak learner */
    Parameter() :
        weakLearnerTraining(new stump::training::Batch<>),
        weakLearnerPrediction(new stump::prediction::Batch<>) {}

    /**
     * Constructs %boosting algorithm parameters from weak learner training and prediction algorithms
     * \param[in] wlTrain       Pointer to the training algorithm of the weak learner
     * \param[in] wlPredict     Pointer to the prediction algorithm of the weak learner
     */
    Parameter(services::SharedPtr<weak_learner::training::Batch>   wlTrain,
              services::SharedPtr<weak_learner::prediction::Batch> wlPredict) :
        weakLearnerTraining(wlTrain), weakLearnerPrediction(wlPredict) {}

    /** The algorithm for weak learner model training */
    services::SharedPtr<weak_learner::training::Batch>   weakLearnerTraining;

    /** The algorithm for prediction based on a weak learner model */
    services::SharedPtr<weak_learner::prediction::Batch> weakLearnerPrediction;
};
/* [Parameter source code] */

/**
 * <a name="DAAL-CLASS-ALGORITHMS__BOOSTING__MODEL"></a>
* \brief %Base class for %boosting algorithm models.
 *        Contains a collection of weak learner models constructed during training of the %boosting algorithm
 */
class Model : public classifier::Model
{
public:
    Model() : _models(new data_management::DataCollection()) {}
    virtual ~Model() {}

    /**
*  Returns the number of weak learners constructed during training of the %boosting algorithm
     *  \return The number of weak learners
     */
    size_t getNumberOfWeakLearners() const
    {
        return _models->size();
    }

    /**
     *  Returns weak learner model constructed during training of the %boosting algorithm
     *  \param[in] idx  Index of the model in the collection
     *  \return Weak Learner model corresponding to the index idx
     */
    services::SharedPtr<weak_learner::Model> getWeakLearnerModel(size_t idx) const
    {
        if(idx < _models->size())
        {
            return services::staticPointerCast<weak_learner::Model, data_management::SerializationIface>((*_models)[idx]);
        }
        return services::SharedPtr<weak_learner::Model>();
    }

    /**
     *  Add weak learner model into the %boosting model
     *  \param[in] model Weak learner model to add into collection
     */
    void addWeakLearnerModel(services::SharedPtr<weak_learner::Model> model)
    {
        (*_models) << model;
    }

    void clearWeakLearnerModels()
    {
        _models->clear();
    }

    int getSerializationTag() { return 0; }
    /**
     *  Serializes the object or data structure
     *  \param[in]  archive  Storage for the serialized object or data structure
     */
    void serializeImpl(data_management::InputDataArchive *archive) {}

    /**
     *  Deserializes the object or data structure
     *  \param[in]  archive  Storage for the deserialized object or data structure
     */
    void deserializeImpl(data_management::OutputDataArchive *archive) {}
protected:
    services::SharedPtr<data_management::DataCollection> _models;

    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        classifier::Model::serialImpl<Archive, onDeserialize>(arch);
        arch->setSharedPtrObj(_models);
    }
};
} // namespace interface1
using interface1::Parameter;
using interface1::Model;

} // namespace daal::algorithms::boosting
}
}
#endif // __BOOSTING_MODEL_H__
