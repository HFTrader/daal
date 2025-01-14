/* file: brownboost_model.h */
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
//  Implementation of class defining Brown Boost model.
//--
*/

#ifndef __BROWN_BOOST_MODEL_H__
#define __BROWN_BOOST_MODEL_H__

#include "algorithms/algorithm.h"
#include "data_management/data/homogen_numeric_table.h"
#include "algorithms/boosting/boosting_model.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes for the BrownBoost classification algorithm
 */
namespace brownboost
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__BROWNBOOST__PARAMETER"></a>
 * \brief BrownBoost algorithm parameters
 *
 * \snippet boosting/brownboost_model.h Parameter source code
 */
/* [Parameter source code] */
struct Parameter : public boosting::Parameter
{
    /** Default constructor */
    Parameter() : boosting::Parameter(), accuracyThreshold(0.3), maxIterations(10),
        newtonRaphsonAccuracyThreshold(1.0e-3), newtonRaphsonMaxIterations(100), degenerateCasesThreshold(1.0e-2) {}

    /**
     * Constructs BrownBoost parameter structure
     * \param[in] wlTrain       Pointer to the training algorithm of the weak learner
     * \param[in] wlPredict     Pointer to the prediction algorithm of the weak learner
     * \param[in] acc           Accuracy of the BrownBoost training algorithm
     * \param[in] maxIter       Maximal number of iterations of the BrownBoost training algorithm
     * \param[in] nrAcc         Accuracy threshold for Newton-Raphson iterations in the BrownBoost training algorithm
     * \param[in] nrMaxIter     Maximal number of Newton-Raphson iterations in the BrownBoost training algorithm
     * \param[in] dcThreshold          Threshold needed  to avoid degenerate cases in the BrownBoost training algorithm
     */
    Parameter(services::SharedPtr<weak_learner::training::Batch>   wlTrain,
              services::SharedPtr<weak_learner::prediction::Batch> wlPredict,
              double acc = 0.3, size_t maxIter = 10, double nrAcc = 1.0e-3, size_t nrMaxIter = 100, double dcThreshold = 1.0e-2) :
        boosting::Parameter(wlTrain, wlPredict), accuracyThreshold(acc), maxIterations(maxIter),
        newtonRaphsonAccuracyThreshold(nrAcc), newtonRaphsonMaxIterations(nrMaxIter), degenerateCasesThreshold(dcThreshold) {}

    double accuracyThreshold;       /*!< Accuracy of the BrownBoost training algorithm */
    size_t maxIterations;           /*!< Maximal number of iterations of the BrownBoost training algorithm */
    double newtonRaphsonAccuracyThreshold;  /*!< Accuracy threshold for Newton-Raphson iterations in the BrownBoost training algorithm */
    size_t newtonRaphsonMaxIterations;      /*!< Maximal number of Newton-Raphson iterations in the BrownBoost training algorithm */
    double degenerateCasesThreshold;        /*!< Threshold needed to avoid degenerate cases in the BrownBoost training algorithm */
};
/* [Parameter source code] */

/**
 * <a name="DAAL-CLASS-ALGORITHMS__BROWNBOOST__MODEL"></a>
 * \brief %Model of the classifier trained by the brownboost::training::Batch algorithm.
 *
 * \par References
 *      - \ref training::interface1::Batch "training::Batch" class
 *      - \ref prediction::interface1::Batch "prediction::Batch" class
 */
class Model : public boosting::Model
{
public:
    /**
     *  Constructs the BrownBoost %Model
     * \tparam modelFPType  Data type to store BrownBoost model data, double or float
     * \param[in] dummy     Dummy variable for the templated constructor
     */
    template <typename modelFPType>
    Model(modelFPType dummy) : boosting::Model()
    {
        _alpha = services::SharedPtr<data_management::NumericTable>(new data_management::HomogenNumericTable<modelFPType>());
        _alpha->setNumberOfColumns(1);
    }

    /**
     * Empty constructor for deserialization
     */
    Model() : boosting::Model(), _alpha()
    {}

    virtual ~Model()
    {}

    /**
     *  Returns a pointer to the array of weights of weak learners constructed
     *  during training of the BrownBoost algorithm.
     *  The size of the array equals the number of weak learners
     *  \return Array of weights of weak learners.
     */
    services::SharedPtr<data_management::NumericTable> getAlpha()
    {
        return _alpha;
    }

    int getSerializationTag() { return SERIALIZATION_BROWNBOOST_MODEL_ID; }
    /**
     *  Serializes the BrownBoost model object
     *  \param[in]  archive  Storage for the serialized object or data structure
     */
    void serializeImpl(data_management::InputDataArchive *archive)
    {serialImpl<data_management::InputDataArchive, false>(archive);}

    /**
     *  Deserializes the BrownBoost model object
     *  \param[in]  archive  Storage for the deserialized object or data structure
     */
    void deserializeImpl(data_management::OutputDataArchive *archive)
    {serialImpl<data_management::OutputDataArchive, true>(archive);}

protected:
    services::SharedPtr<data_management::NumericTable> _alpha;     /* Boosting coefficients table */

    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        boosting::Model::serialImpl<Archive, onDeserialize>(arch);
        arch->setSharedPtrObj(_alpha);
    }
}; // class Model
} // namespace interface1
using interface1::Parameter;
using interface1::Model;

} // namespace daal::algorithms::brownboost
}
} // namespace daal
#endif
