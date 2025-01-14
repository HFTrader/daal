/* file: linear_regression_predict_types.h */
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
//  Implementation of the linear regression algorithm interface
//--
*/

#ifndef __LINEAR_REGRESSION_PREDICT_TYPES_H__
#define __LINEAR_REGRESSION_PREDICT_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/data_serialize.h"
#include "services/daal_defines.h"
#include "algorithms/linear_regression/linear_regression_model.h"
#include "algorithms/linear_regression/linear_regression_ne_model.h"
#include "algorithms/linear_regression/linear_regression_qr_model.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes of the linear regression algorithm
 */
namespace linear_regression
{
/**
 * \brief Contains a class for making linear regression model-based prediction
 */
namespace prediction
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__PREDICTION__METHOD"></a>
 * \brief Available methods for making linear regression model-based prediction
 */
enum Method { defaultDense };

/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__PREDICTION__NUMERIC_TABLE_INPUT_ID"></a>
 * \brief Available identifiers of input numeric tables for making linear regression model-based prediction
 */
enum NumericTableInputId
{
    data = 0 /*!< Input data table */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__PREDICTION__MODEL_INPUT_ID"></a>
 * \brief Available identifiers of input models for making linear regression model-based prediction
 */
enum ModelInputId
{
    model = 1 /*!< Trained linear regression model */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__LINEAR_REGRESSION__PREDICTION__MASTER_INPUT_ID"></a>
 * \brief Available identifiers of the result for making linear regression model-based prediction
 */
enum ResultId
{
    prediction = 0 /*!< Result of linear regression model-based prediction */
};

/**
 * \brief Contains version 1.0 of the Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-LINEAR_REGRESSION__PREDICTION__INPUT"></a>
 * \brief Provides an interface for input objects for making linear regression model-based prediction
 */
class Input : public daal::algorithms::Input
{
public:
/** Default constructor */
    Input() : daal::algorithms::Input(2) {};

    /**
     * Returns an input object for making linear regression model-based prediction
     * \param[in] id    Identifier of the input object
     * \return          %Input object that corresponds to the given identifier
     */
    services::SharedPtr<data_management::NumericTable> get(NumericTableInputId id) const
    {
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Returns an input object for making linear regression model-based prediction
     * \param[in] id    Identifier of the input object
     * \return          %Input object that corresponds to the given identifier
     */
    services::SharedPtr<linear_regression::Model> get(ModelInputId id) const
    {
        return services::staticPointerCast<linear_regression::Model, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Sets an input object for making linear regression model-based prediction
     * \param[in] id      Identifier of the input object
     * \param[in] value   %Input object
     */
    void set(NumericTableInputId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
    }

    /**
     * Sets an input object for making linear regression model-based prediction
     * \param[in] id      Identifier of the input object
     * \param[in] value   %Input object
     */
    void set(ModelInputId id, const services::SharedPtr<linear_regression::Model> &value)
    {
        Argument::set(id, value);
    }

    /**
     * Checks an input object for making linear regression model-based prediction
     */
    void check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        if(Argument::size() != 2) { this->_errors->add(services::ErrorIncorrectNumberOfInputNumericTables); return; }

        services::SharedPtr<data_management::NumericTable> dataTable = get(data);
        if(dataTable.get() == 0)                 { this->_errors->add(services::ErrorNullInputNumericTable); return;         }
        if(dataTable->getNumberOfRows() == 0)    { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
        if(dataTable->getNumberOfColumns() == 0) { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return;     }

        services::SharedPtr<linear_regression::Model> model = get(prediction::model);
        if(model->getBeta() == 0) { this->_errors->add(services::ErrorNullInputNumericTable); return; }
    }
};

/**
 * <a name="DAAL-CLASS-LINEAR_REGRESSION__PREDICTION__RESULT"></a>
 * \brief Provides interface for the result of linear regression model-based prediction
 */
class Result : public daal::algorithms::Result
{
public:
    Result() : daal::algorithms::Result(1) {};

    /**
     * Returns the result of linear regression model-based prediction
     * \param[in] id    Identifier of the result
     * \return          Result that corresponds to the given identifier
     */
    services::SharedPtr<data_management::NumericTable> get(ResultId id) const
    {
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Sets the result of linear regression model-based prediction
     * \param[in] id      Identifier of the input object
     * \param[in] value   %Input object
     */
    void set(ResultId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
    }

    /**
     * Allocates memory to store a partial result of linear regression model-based prediction
     * \param[in] input   %Input object
     * \param[in] par     %Parameter of the algorithm
     * \param[in] method  Algorithm method
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, const int method)
    {
        size_t nVectors = (static_cast<const Input *>(input))->get(data)->getNumberOfRows();
        size_t nDependentVariables = (static_cast<const Input *>(input))->get(model)->getNumberOfResponses();

        Argument::set(prediction,
                      services::SharedPtr<data_management::SerializationIface>(
                          new data_management::HomogenNumericTable<algorithmFPType>
                          (nDependentVariables, nVectors, data_management::NumericTableIface::doAllocate)));
    }

    /**
     * Checks the result of linear regression model-based prediction
     * \param[in] input   %Input object
     * \param[in] par     %Parameter of the algorithm
     * \param[in] method  Computation method
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE
    {
        if(Argument::size() != 1) { this->_errors->add(services::ErrorIncorrectNumberOfOutputNumericTables); return; }

        services::SharedPtr<data_management::NumericTable> predictionTable = get(prediction);
        if(predictionTable.get() == 0)
        { this->_errors->add(services::ErrorNullOutputNumericTable); return; }
        if(predictionTable->getNumberOfRows() != (static_cast<const Input *>(input))->get(
               data)->getNumberOfRows())
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
        if(predictionTable->getNumberOfColumns() != (static_cast<const Input *>(input))->get(
               model)->getNumberOfResponses())
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
    }

    /**
     * Returns the serialization tag of the linear regression model-based prediction result
     * \return         Serialization tag of the linear regression model-based prediction result
     */

    int getSerializationTag() { return SERIALIZATION_LINEAR_REGRESSION_PREDICTION_RESULT_ID; }

    /**
    *  Serializes an object
    *  \param[in]  arch  Storage for a serialized object or data structure
    */
    void serializeImpl(data_management::InputDataArchive  *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
    *  Deserializes an object
    *  \param[in]  arch  Storage for a deserialized object or data structure
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
using interface1::Input;
using interface1::Result;

}
}
}
} // namespace daal
#endif
