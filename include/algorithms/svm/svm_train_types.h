/* file: svm_train_types.h */
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
//  SVM parameter structure
//--
*/

#ifndef __SVM_TRAIN_TYPES_H__
#define __SVM_TRAIN_TYPES_H__

#include "algorithms/algorithm.h"
#include "algorithms/kernel_function/kernel_function.h"
#include "algorithms/svm/svm_model.h"
#include "algorithms/classifier/classifier_training_types.h"

namespace daal
{
namespace algorithms
{
namespace svm
{
/**
 * \brief Contains classes to train the SVM model
 */
namespace training
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__SVM__TRAINING__RESULTID"></a>
 * Available methods to train the SVM model
 */
enum Method
{
    boser = 0,          /*!< Method proposed by Boser et al. */
    defaultDense = 0    /*!< Default method */
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__SVM__TRAINING__RESULT"></a>
 * \brief Provides methods to access final results obtained with the compute() method of the
 *        SVM training algorithm in the batch processing mode
 */
class Result : public classifier::training::Result
{
public:
    Result() : classifier::training::Result() {}

    virtual ~Result() {}

    /**
     * Returns the model trained with the SVM algorithm
     * \param[in] id    Identifier of the result, \ref classifier::training::ResultId
     * \return          Model trained with the SVM algorithm
     */
    services::SharedPtr<daal::algorithms::svm::Model> get(classifier::training::ResultId id) const
    {
        return services::staticPointerCast<daal::algorithms::svm::Model, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Allocates memory for storing SVM training results
     * \param[in] input     Pointer to input structure
     * \param[in] parameter Pointer to parameter structure
     * \param[in] method    Algorithm method
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        const classifier::training::Input *algInput = static_cast<const classifier::training::Input *>(input);

        algorithmFPType dummy = 1.0;
        set(classifier::training::model, services::SharedPtr<svm::Model>(
                new svm::Model(dummy, algInput->get(classifier::training::data)->getDataLayout())));
    }

    int getSerializationTag() { return SERIALIZATION_SVM_TRAINING_RESULT_ID; }

    /**
    *  Serializes the object
    *  \param[in]  arch  Storage for the serialized object or data structure
    */
    void serializeImpl(data_management::InputDataArchive  *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
    *  Deserializes the object
    *  \param[in]  arch  Storage for the deserialized object or data structure
    */
    void deserializeImpl(data_management::OutputDataArchive *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::OutputDataArchive, true>(arch);}

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};
} // namespace interface1
using interface1::Result;

} // namespace training
} // namespace svm
} // namespace algorithms
} // namespace daal
#endif
