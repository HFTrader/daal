/* file: pca_types.h */
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
//  Implementation of PCA algorithm interface.
//--
*/

#ifndef __PCA_TYPES_H__
#define __PCA_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/covariance/covariance_batch.h"
#include "algorithms/covariance/covariance_online.h"
#include "algorithms/covariance/covariance_distributed.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes for computing the results of the principal component analysis (PCA) algorithm
 */
namespace pca
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__METHOD"></a>
 * Available methods for computing the PCA algorithm
 */
enum Method
{
    correlationDense = 0, /*!< PCA Correlation method */
    defaultDense = 0, /*!< PCA Default method */
    svdDense = 1 /*!< PCA SVD method */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__INPUT_DATASET_ID"></a>
 * Available identifiers of input dataset objects for the PCA algorithm
 */
enum InputDatasetId
{
    data = 0 /*!< Input data table */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__INPUT_CORRELATION_ID"></a>
 * Available identifiers of input objects for the PCA Correlation algorithm
 */
enum InputCorrelationId
{
    correlation = 0 /*!< Input correlation table */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__MASTER_INPUT_ID"></a>
 * Available identifiers of input objects for the PCA algorithm on the second step in the distributed processing mode
 */
enum Step2MasterInputId
{
    partialResults = 0 /*!< Collection of partial results computed on local nodes */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__PARTIAL_CORRELATION_RESULT_ID"></a>
 * Available identifiers of partial results of the PCA Correlation algorithm
 */
enum PartialCorrelationResultId
{
    nObservationsCorrelation = 0, /* Number of processed observations */
    crossProductCorrelation = 1, /* Cross-product of the processed data */
    sumCorrelation = 2 /* Feature sums of the processed data */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__PARTIAL_SVD_TABLE_RESULT_ID"></a>
 * Available identifiers of partial results of the PCA SVD algorithm
 */
enum PartialSVDTableResultId
{
    nObservationsSVD = 0, /* Number of processed observations */
    sumSVD = 1, /* Feature sums of the processed data */
    sumSquaresSVD = 2 /* Feature sums of squares of the processed data */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__PARTIAL_SVD_TABLE_RESULT_ID"></a>
 * Available identifiers of partial results of the PCA SVD  algorithm
 */
enum PartialSVDCollectionResultId
{
    auxiliaryData = 3, /*!< Auxiliary data of the PCA SVD method */
    distributedInputs = 4 /*!< Auxiliary data of the PCA SVD method on the second step in the distributed processing mode */
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__PCA__PARTIAL_SVD_TABLE_RESULT_ID"></a>
 * Available identifiers of the results of the PCA algorithm
 */
enum ResultId
{
    eigenvalues = 0, /*!< Eigenvalues of the correlation matrix */
    eigenvectors = 1 /*!< Eigenvectors of the correlation matrix */
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__INPUT_IFACE"></a>
 * \brief Abstract class that specifies interface for classes that declare input of the PCA algorithm */
class InputIface : public daal::algorithms::Input
{
public:
    InputIface(size_t nElements) : daal::algorithms::Input(nElements), _isCorrelation(false) {};

    /**
     * Returns the number of columns in the input data set
     * \return Number of columns in the input data set
     */
    virtual size_t getNFeatures() const = 0;

    /**
    * Returns flag defining whether the input data contains correlation matrix or not
    * \return Flag defining whether the input data contains correlation matrix or not
    */
    virtual bool isCorrelation() { return _isCorrelation; };

    virtual ~InputIface() {};

protected:
    bool _isCorrelation;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__INPUT"></a>
 * \brief Input objects for the PCA algorithm
 */
class Input : public InputIface
{
public:
    Input() : InputIface(1) {};

    virtual ~Input() {};

    /**
    * Returns the input object of the PCA algorithm
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
    */
    services::SharedPtr<data_management::NumericTable> get(InputDatasetId id) const
    {
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Sets input dataset for the PCA algorithm
     * \param[in] id      Identifier of the input object
     * \param[in] value   Pointer to the input object
     */
    void set(InputDatasetId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
        _isCorrelation = false;
    }

    /**
     * Sets input correlation matrix for the PCA algorithm
     * \param[in] id      Identifier of the input object
     * \param[in] value   Pointer to the input object
     */
    void set(InputCorrelationId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
        _isCorrelation = true;
    }

    /**
     * Returns the number of columns in the input data set
     * \return Number of columns in the input data set
     */
    size_t getNFeatures() const
    {
        return (services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(
                                                                                                                    data)))->getNumberOfColumns();
    }

    /**
    * Checks input algorithm parameters
    * \param[in] par     Algorithm %parameter
    * \param[in] method  Computation method
    * \return Errors detected while checking
    */
    void check(const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE
    {
        if(Argument::size() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfInputNumericTables); return; }

        services::SharedPtr<data_management::NumericTable> inTable = get(data);

        if(inTable.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(inTable->getNumberOfRows() == 0)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
        if(inTable->getNumberOfColumns() == 0)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
    }
};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULTBASE"></a>
 * \brief Provides interface to access partial results obtained with the compute() method of the
 *        PCA algorithm in the online or distributed processing mode
 */
class PartialResultBase :  public daal::algorithms::PartialResult
{
public:
    PartialResultBase(const size_t nElements) : daal::algorithms::PartialResult(nElements) {};

    virtual size_t getNFeatures() const = 0;

    virtual ~PartialResultBase() {};
};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULT"></a>
 * \brief Provides methods to access partial results obtained with the compute() method of the
 *        PCA algorithm in the online or distributed processing mode
 */
template<Method method>
class PartialResult :  public PartialResultBase {};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULT"></a>
 * \brief Provides methods to access partial results obtained with the compute() method of the PCA Correlation algorithm
 *        in the online or distributed processing mode
 */
template<> class PartialResult<correlationDense> :  public PartialResultBase
{
public:
    PartialResult() : PartialResultBase(3) {};

    /**
     * Gets partial results of the PCA Correlation algorithm
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
     */
    services::SharedPtr<data_management::NumericTable> get(PartialCorrelationResultId id) const
    {
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(id));
    }

    virtual size_t getNFeatures() const { return get(sumCorrelation)->getNumberOfColumns(); }

    /**
     * Sets partial result of the PCA Correlation algorithm
     * \param[in] id      Identifier of the result
     * \param[in] value   Pointer to the object
     */
    void set(const PartialCorrelationResultId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
    }

    virtual ~PartialResult() {};

    /**
    * Checks partial results of the PCA Correlation algorithm
    * \param[in] input      %Input object of the algorithm
    * \param[in] parameter  Algorithm %parameter
    * \param[in] method     Computation method
    */
    void check(const daal::algorithms::Input *input,
               const daal::algorithms::Parameter *parameter,
               int method) const DAAL_C11_OVERRIDE
    {
        size_t nFeatures = (static_cast<const InputIface *>(input))->getNFeatures();

        services::SharedPtr<data_management::NumericTable> nObservationsCorrelation = get(pca::nObservationsCorrelation);
        if(nObservationsCorrelation.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(nObservationsCorrelation->getNumberOfColumns() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(nObservationsCorrelation->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> sumCorrelation = get(pca::sumCorrelation);
        if(sumCorrelation.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(sumCorrelation->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(sumCorrelation->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> crossProductCorrelation = get(pca::crossProductCorrelation);
        if(crossProductCorrelation.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(crossProductCorrelation->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(crossProductCorrelation->getNumberOfRows() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
    }


    /**
    * Checks partial results of the PCA Ccorrelation algorithm
    * \param[in] par        Algorithm %parameter
    * \param[in] method     Computation method
    */
    void check(const daal::algorithms::Parameter *par, int method) const
    {
        services::SharedPtr<data_management::NumericTable> nObservationsCorrelation = get(pca::nObservationsCorrelation);
        if(nObservationsCorrelation.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(nObservationsCorrelation->getNumberOfColumns() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(nObservationsCorrelation->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> sumCorrelation = get(pca::sumCorrelation);
        if(sumCorrelation.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }

        size_t nFeatures = sumCorrelation->getNumberOfColumns();
        if(sumCorrelation->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> crossProductCorrelation = get(pca::crossProductCorrelation);
        if(crossProductCorrelation.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(crossProductCorrelation->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(crossProductCorrelation->getNumberOfRows() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
    }

    int getSerializationTag() { return SERIALIZATION_PCA_PARTIAL_RESULT_CORRELATION_ID; }

    /**
    *  Serializes the object
    *  \param[in]  arch  Storage for the serialized object or data structure
    */
    void serializeImpl(data_management::InputDataArchive  *arch)
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
    *  Deserializes the object
    *  \param[in]  arch  Storage for the deserialized object or data structure
    */
    void deserializeImpl(data_management::OutputDataArchive *arch)
    {serialImpl<data_management::OutputDataArchive, true>(arch);}

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        daal::algorithms::PartialResult::serialImpl<Archive, onDeserialize>(arch);
    }
};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULT"></a>
 * \brief Provides methods to access partial results obtained with the compute() method of PCA SVD algorithm
 *         in the online or distributed processing mode
 */
template<> class PartialResult<svdDense> : public PartialResultBase
{
public:
    PartialResult() : PartialResultBase(4) {};

    /**
    * Gets partial results of the PCA SVD algorithm
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
    */
    services::SharedPtr<data_management::NumericTable> get(PartialSVDTableResultId id) const
    {
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(id));
    }

    virtual size_t getNFeatures() const { return get(sumSVD)->getNumberOfColumns(); }

    /**
    * Gets partial results of the PCA SVD algorithm
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
    */
    services::SharedPtr<data_management::DataCollection> get(PartialSVDCollectionResultId id) const
    {
        return services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(id));
    }

    /**
    * Gets partial results of the PCA SVD algorithm
     * \param[in] id            Identifier of the input object
     * \param[in] elementId     Identifier of the collection element
     * \return                  Input object that corresponds to the given identifier
    */
    services::SharedPtr<data_management::NumericTable> get(PartialSVDCollectionResultId id, const size_t &elementId) const
    {
        services::SharedPtr<data_management::DataCollection> collection = get(id);
        if(elementId >= collection->size())
        {
            return services::SharedPtr<data_management::NumericTable>();
        }
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>((*collection)[elementId]);
    }

    /**
     * Sets partial result of the PCA SVD algorithm
     * \param[in] id      Identifier of the result
     * \param[in] value   Pointer to  the object
     */
    void set(PartialSVDTableResultId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
    }

    /**
     * Sets partial result of the PCA SVD algorithm
     * \param[in] id      Identifier of the result
     * \param[in] value   Pointer to the object
     */
    void set(PartialSVDCollectionResultId id, const services::SharedPtr<data_management::DataCollection> &value)
    {
        Argument::set(id, services::staticPointerCast<data_management::SerializationIface, data_management::DataCollection>(value));
    }

    /**
     * Adds partial result of the PCA SVD algorithm
     * \param[in] id      Identifier of the argument
     * \param[in] value   Pointer to the object
     */
    void add(const PartialSVDCollectionResultId &id, const services::SharedPtr<data_management::DataCollection> &value)
    {
        services::SharedPtr<data_management::DataCollection> collection =
            services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(id));
        collection->push_back(value);
    }

    /**
    * Checks partial results of the PCA SVD algorithm
    * \param[in] input      %Input of algorithm
    * \param[in] parameter  %Parameter of algorithm
    * \param[in] method     Computation method
    */
    void check(const daal::algorithms::Input *input,
               const daal::algorithms::Parameter *parameter,
               int method) const DAAL_C11_OVERRIDE
    {
        size_t nFeatures = (static_cast<const InputIface *>(input))->getNFeatures();

        services::SharedPtr<data_management::NumericTable> nObservationsSVD = get(pca::nObservationsSVD);
        if(nObservationsSVD.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(nObservationsSVD->getNumberOfColumns() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(nObservationsSVD->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> sumSquaresSVD = get(pca::sumSquaresSVD);
        if(sumSquaresSVD.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(sumSquaresSVD->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(sumSquaresSVD->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> sumSVD = get(pca::sumSVD);
        if(sumSVD.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(sumSVD->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(sumSVD->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
    }

    /**
    * Checks partial results of the PCA SVD algorithm
    * \param[in] method     Computation method
    * \param[in] par        %Parameter of algorithm
    */
    void check(const daal::algorithms::Parameter *par, int method) const
    {
        services::SharedPtr<data_management::NumericTable> nObservationsSVD = get(pca::nObservationsSVD);
        if(nObservationsSVD.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(nObservationsSVD->getNumberOfColumns() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(nObservationsSVD->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> sumSquaresSVD = get(pca::sumSquaresSVD);
        if(sumSquaresSVD.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }

        size_t nFeatures = sumSquaresSVD->getNumberOfColumns();
        if(sumSquaresSVD->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> sumSVD = get(pca::sumSVD);
        if(sumSVD.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(sumSVD->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(sumSVD->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
    }

    virtual ~PartialResult() {};

    int getSerializationTag() { return SERIALIZATION_PCA_PARTIAL_RESULT_SVD_ID; }

    /**
    *  Serializes the object
    *  \param[in]  arch  Storage for the serialized object or data structure
    */
    void serializeImpl(data_management::InputDataArchive  *arch)
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
    *  Deserializes the object
    *  \param[in]  arch  Storage for the deserialized object or data structure
    */
    void deserializeImpl(data_management::OutputDataArchive *arch)
    {serialImpl<data_management::OutputDataArchive, true>(arch);}

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        daal::algorithms::PartialResult::serialImpl<Archive, onDeserialize>(arch);
    }
};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULTIMPL"></a>
 * \brief Provides methods to allocate partial results obtained with the compute() method of the PCA SVD algorithm
 *         in the online or distributed processing mode
 */
template<typename algorithmFPType, Method method>
class PartialResultImpl : public PartialResult<method> {};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULTIMPL"></a>
 * \brief Provides methods to allocate partial results obtained with the compute() method of PCA SVD algorithm
 *         in the online or distributed processing mode
 */
template<typename algorithmFPType> class PartialResultImpl<algorithmFPType, correlationDense> :
    public PartialResult<correlationDense>
{
public:
    PartialResultImpl<algorithmFPType, correlationDense>() {};

    /**
     * Allocates memory to store partial results of the PCA  SVD algorithm
     * \param[in] input     Pointer to an object containing input data
     * \param[in] parameter Pointer to the structure of algorithm parameters
     * \param[in] method    Computation method
     */
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        set(nObservationsCorrelation,
            services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<double>(1, 1, data_management::NumericTableIface::doAllocate, 0)));
        set(sumCorrelation,
            services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<double>((static_cast<const Input *>(input))->getNFeatures(), 1,
                                                                 data_management::NumericTableIface::doAllocate, 0)));
        set(crossProductCorrelation,
            services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<double>((static_cast<const Input *>(input))->getNFeatures(),
                                                                 (static_cast<const Input *>(input))->getNFeatures(),
                                                                 data_management::NumericTableIface::doAllocate, 0)));
    };
};

/**
 * <a name="DAAL-CLASS-PCA__PARTIALRESULTIMPL"></a>
 * \brief Provides methods to allocate partial results obtained with the compute() method of the PCA SVD algorithm
 *         in the online or distributed processing mode
 */
template<typename algorithmFPType> class PartialResultImpl<algorithmFPType, svdDense> : public PartialResult<svdDense>
{
public:
    PartialResultImpl<algorithmFPType, svdDense>() {};

    /**
     * Allocates memory for storing partial results of the PCA SVD algorithm
     * \param[in] input     Pointer to an object containing input data
     * \param[in] parameter Pointer to the structure of algorithm parameters
     * \param[in] method    Computation method
     */
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        set(nObservationsSVD,
            services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<double>(1, 1, data_management::NumericTableIface::doAllocate, 0)));
        set(sumSquaresSVD,
            services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<double>((static_cast<const Input *>(input))->getNFeatures(), 1,
                                                                 data_management::NumericTableIface::doAllocate, 0)));
        set(sumSVD,
            services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<double>((static_cast<const Input *>(input))->getNFeatures(), 1,
                                                                 data_management::NumericTableIface::doAllocate, 0)));
        set(auxiliaryData, services::SharedPtr<data_management::DataCollection>(new data_management::DataCollection()));
    };
};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__PARTIALRESULTINITIFACE"></a>
 * \brief Abstract interface class for partial results initialization
 */
template<Method method>
struct PartialResultsInitIface
{
    virtual ~PartialResultsInitIface() {}

    /**
     * Initializes partial results
     * \param[in]       input     Input objects for the PCA algorithm
     * \param[in,out]   pres      Partial results of the PCA algorithm
     * \return                    Initialized partial results
     */
    virtual void operator()(const Input &input, services::SharedPtr<PartialResult<method> > &pres) = 0;
};

static inline void setToZero(data_management::NumericTable *table)
{
    data_management::BlockDescriptor<double> block;
    size_t nCols = table->getNumberOfColumns();
    size_t nRows = table->getNumberOfRows();

    double *tableArray;
    table->getBlockOfRows(0, nRows, data_management::writeOnly, block);
    tableArray = block.getBlockPtr();

    for(size_t i = 0; i < nCols * nRows; i++)
    {
        tableArray[i] = 0;
    };

    table->releaseBlockOfRows(block);
};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__PARTIALRESULTINITIFACE"></a>
 * \brief Abstract interface class for partial results initialization
 */
template<Method method>
struct DefaultPartialResultsInit : public PartialResultsInitIface<method>
{};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__DEFAULTPARTIALRESULTSINIT"></a>
 * \brief Class that specifies the default method for partial results initialization
 */
template<> struct DefaultPartialResultsInit<correlationDense> : public PartialResultsInitIface<correlationDense>
{
    virtual ~DefaultPartialResultsInit() {}

    /**
     * Initialize partial results
     * \param[in]       input     Input objects for the PCA algorithm
     * \param[in,out]   pres      Partial results of the PCA algorithm
     * \return                    Initialized partial results
     */
    void operator()(const Input &input, services::SharedPtr<PartialResult<correlationDense> > &pres)
    {
        setToZero(pres->get(pca::nObservationsCorrelation).get());
        setToZero(pres->get(pca::sumCorrelation).get());
        setToZero(pres->get(pca::crossProductCorrelation).get());
    };
};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__DEFAULTPARTIALRESULTSINIT"></a>
 * \brief Class that specifies the default method for partial results initialization
 */
template<> struct DefaultPartialResultsInit<svdDense> : public PartialResultsInitIface<svdDense>
{
    virtual ~DefaultPartialResultsInit() {}

    /**
     * Initialize partial results
     * \param[in]       input     Input objects for the PCA algorithm
     * \param[in,out]   pres      Partial results of the PCA algorithm
     * \return                    Initialized partial results
     */
    void operator()(const Input &input, services::SharedPtr<PartialResult<svdDense> > &pres)
    {
        setToZero(pres->get(pca::nObservationsSVD).get());
        setToZero(pres->get(pca::sumSVD).get());
        setToZero(pres->get(pca::sumSquaresSVD).get());
    };
};

/**
 * <a name="DAAL-CLASS-CLASS-PCABASEPARAMETER__"></a>
 * \brief Class that specifies the common parameters of the PCA algorithm
 */
template<typename algorithmFPType, Method method = correlationDense>
class BaseParameter : public daal::algorithms::Parameter
{
public:
    /** Constructs PCA parameters */
    BaseParameter() :
        initializationProcedure(services::SharedPtr<PartialResultsInitIface<method> >(new DefaultPartialResultsInit<method>()))
    {};

    services::SharedPtr<PartialResultsInitIface<method> > initializationProcedure; /**< Functor for partial results initialization */
};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__BATCHPARAMETER"></a>
 * \brief Class that specifies the parameters of the PCA algorithm in the batch computing mode
 */
template<typename algorithmFPType, Method method>
class BatchParameter : public BaseParameter<algorithmFPType, method> {};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__BATCHPARAMETER"></a>
 * \brief Class that specifies the parameters of the PCA Correlation algorithm in the batch computing mode
 */
template<typename algorithmFPType>
class BatchParameter<algorithmFPType, correlationDense> : public BaseParameter<algorithmFPType, correlationDense>
{
public:
    /** Constructs PCA parameters */
    BatchParameter(const services::SharedPtr<covariance::BatchIface> &covariance =
                       services::SharedPtr<covariance::Batch<algorithmFPType, covariance::defaultDense> >
                   (new covariance::Batch<algorithmFPType, covariance::defaultDense>())) : covariance(covariance) {};

    services::SharedPtr<covariance::BatchIface> covariance; /*!< Pointer to batch covariance */
};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__ONLINEPARAMETER"></a>
  * \brief Class that specifies the parameters of the PCA algorithm in the online computing mode
 */
template<typename algorithmFPType, Method method>
class OnlineParameter : public BaseParameter<algorithmFPType, method> {};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__ONLINEPARAMETER"></a>
  * \brief Class that specifies the parameters of the PCA Correlation algorithm in the online computing mode
 */
template<typename algorithmFPType>
class OnlineParameter<algorithmFPType, correlationDense> : public BaseParameter<algorithmFPType, correlationDense>
{
public:
    /** Constructs PCA parameters */
    OnlineParameter(const services::SharedPtr<covariance::OnlineIface> &covariance =
                        services::SharedPtr<covariance::Online<algorithmFPType, covariance::defaultDense> >
                    (new covariance::Online<algorithmFPType, covariance::defaultDense>()),
                    const services::SharedPtr<PartialResultsInitIface<correlationDense> > &initializationProcedure =
                        services::SharedPtr<PartialResultsInitIface<correlationDense> >
                        (new DefaultPartialResultsInit<correlationDense>())) :
        covariance(covariance), initializationProcedure(initializationProcedure) {};

    services::SharedPtr<covariance::OnlineIface> covariance; /*!< Pointer to Online covariance */
    services::SharedPtr<PartialResultsInitIface<correlationDense> > initializationProcedure; /**< Functor for partial results initialization */
};


/**
 * <a name="DAAL-CLASS-CLASS-PCA__ONLINEPARAMETER"></a>
  * \brief Class that specifies the parameters of the PCA SVD algorithm in the online computing mode
 */
template<typename algorithmFPType>
class OnlineParameter<algorithmFPType, svdDense> : public BaseParameter<algorithmFPType, svdDense>
{
public:
    /** Constructs PCA parameters */
    OnlineParameter(const services::SharedPtr<PartialResultsInitIface<svdDense> > &initializationProcedure =
                        services::SharedPtr<PartialResultsInitIface<svdDense> >
                        (new DefaultPartialResultsInit<svdDense>())) :
        initializationProcedure(initializationProcedure) {};

    services::SharedPtr<PartialResultsInitIface<svdDense> > initializationProcedure; /**< Functor for partial results initialization */
};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__DISTRIBUTEDPARAMETER"></a>
 * \brief Class that specifies the parameters of the PCA algorithm in the distributed computing mode
 */
template<ComputeStep step, typename algorithmFPType, Method method>
class DistributedParameter : public BaseParameter<algorithmFPType, method> {};

/**
 * <a name="DAAL-CLASS-CLASS-PCA__DISTRIBUTEDPARAMETER"></a>
 * \brief Class that specifies the parameters of the PCA Correlation algorithm in the distributed computing mode
 */
template<typename algorithmFPType>
class DistributedParameter<step2Master, algorithmFPType, correlationDense> : public BaseParameter<algorithmFPType, correlationDense>
{
public:
    /** Constructs PCA parameters */
    DistributedParameter(const services::SharedPtr<covariance::DistributedIface<step2Master> > &covariance =
                             services::SharedPtr<covariance::Distributed<step2Master, algorithmFPType, covariance::defaultDense> >
                         (new covariance::Distributed<step2Master, algorithmFPType, covariance::defaultDense>())) : covariance(covariance) {};

    services::SharedPtr<covariance::DistributedIface<step2Master> > covariance; /*!< Pointer to Distributed covariance */
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__DISTRIBUTED_INPUT"></a>
 * \brief Input objects for the PCA algorithm in the distributed processing mode
 */
template<Method method>
class DistributedInput {};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__DISTRIBUTED_INPUT"></a>
 * \brief Input objects for the PCA Correlation algorithm in the distributed processing mode
 */
template<> class DistributedInput<correlationDense> : public InputIface
{
public:
    DistributedInput() : InputIface(1)
    {
        Argument::set(partialResults, services::SharedPtr<data_management::DataCollection>(new data_management::DataCollection()));
    }

    /**
     * Sets input objects for the PCA on the second step in the distributed processing mode
     * \param[in] id    Identifier of the input object
     * \param[in] ptr   Input object that corresponds to the given identifier
     */
    void set(Step2MasterInputId id, const services::SharedPtr<data_management::DataCollection> &ptr)
    {
        Argument::set(id, ptr);
    }

    /**
     * Gets input objects for the PCA on the second step in the distributed processing mode
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
     */
    services::SharedPtr<data_management::DataCollection> get(Step2MasterInputId id) const
    {
        return services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Retrieves specific partial result from the input objects of the PCA algorithm on the second step in the distributed processing mode
     * \param[in] id      Identifier of the partial result
     */
    services::SharedPtr<PartialResult<correlationDense> > getPartialResult(size_t id) const
    {
        services::SharedPtr<data_management::DataCollection> partialResultsCollection
            = services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(partialResults));
        if(partialResultsCollection->size() <= id)
        {
            return services::SharedPtr<PartialResult<correlationDense> >();
        }
        return services::staticPointerCast<PartialResult<correlationDense>,
               data_management::SerializationIface>((*partialResultsCollection)[id]);
    }

    /**
     * Adds input objects of the PCA algorithm on the second step in the distributed processing mode
     * \param[in] id      Identifier of the argument
     * \param[in] value   Pointer to the argument
     */
    void add(Step2MasterInputId id, const services::SharedPtr<PartialResult<correlationDense> > &value)
    {
        services::SharedPtr<data_management::DataCollection> collection
            = services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(id));
        collection->push_back(value);
    }

    /**
     * Returns the number of columns in the input data set
     * \return Number of columns in the input data set
     */
    size_t getNFeatures() const
    {
        return getPartialResult(0)->get(pca::crossProductCorrelation)->getNumberOfColumns();
    }

    void check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        services::SharedPtr<data_management::DataCollection> collection =
            services::dynamicPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(0));
        size_t nBlocks = collection->size();
        if(collection->size() == 0)
        { this->_errors->add(services::ErrorIncorrectNumberOfInputNumericTables); return; }

        size_t nFeatures = getPartialResult(0)->get(pca::crossProductCorrelation)->getNumberOfColumns();
        if(nFeatures == 0)
        { this->_errors->add(services::ErrorIncorrectSizeOfInputNumericTable); return; }

        for(size_t j = 0; j < nBlocks; j++)
        {
            services::SharedPtr<data_management::NumericTable> nObservationsCorrelation = getPartialResult(j)->get(pca::
                                                                                                                   nObservationsCorrelation);
            if((nObservationsCorrelation->getNumberOfRows() != 1) || (nObservationsCorrelation->getNumberOfColumns() != 1))
            { this->_errors->add(services::ErrorIncorrectSizeOfInputNumericTable); return; }

            services::SharedPtr<data_management::NumericTable> crossProductCorrelation = getPartialResult(j)->get(
                                                                                             pca::crossProductCorrelation);
            if((crossProductCorrelation->getNumberOfRows() != nFeatures) ||
               (crossProductCorrelation->getNumberOfColumns() != nFeatures))
            { this->_errors->add(services::ErrorIncorrectSizeOfInputNumericTable); return; }

            services::SharedPtr<data_management::NumericTable> sumCorrelation = getPartialResult(j)->get(pca::sumCorrelation);
            if((sumCorrelation->getNumberOfRows() != 1) || (sumCorrelation->getNumberOfColumns() != nFeatures))
            { this->_errors->add(services::ErrorIncorrectSizeOfInputNumericTable); return; }
        }
    }
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__DISTRIBUTED_INPUT"></a>
 * \brief Input objects of the PCA SVD algorithm in the distributed processing mode
 */
template<> class DistributedInput<svdDense> : public InputIface
{
public:
    DistributedInput() : InputIface(1)
    {
        Argument::set(partialResults, services::SharedPtr<data_management::DataCollection>(new data_management::DataCollection()));
    };

    /**
     * Sets input objects for the PCA on the second step in the distributed processing mode
     * \param[in] id    Identifier of the input object
     * \param[in] ptr   Input object that corresponds to the given identifier
     */
    void set(Step2MasterInputId id, const services::SharedPtr<data_management::DataCollection> &ptr)
    {
        Argument::set(id, ptr);
    }

    /**
     * Gets input objects for the PCA algorithm on the second step in the distributed processing mode
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
     */
    services::SharedPtr<data_management::DataCollection> get(Step2MasterInputId id) const
    {
        return services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Adds input objects of the PCA algorithm on the second step in the distributed processing mode
     * \param[in] id      Identifier of the input object
     * \param[in] value   Pointer to the input object
     */
    void add(Step2MasterInputId id, const services::SharedPtr<PartialResult<svdDense> > &value)
    {
        services::SharedPtr<data_management::DataCollection> collection =
            services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(id));
        collection->push_back(value);
    }

    /**
     * Retrieves specific partial result from the input objects of the PCA algorithm on the second step in the distributed processing mode
     * \param[in] id      Identifier of the partial result
     */
    services::SharedPtr<PartialResult<svdDense> > getPartialResult(size_t id) const
    {
        services::SharedPtr<data_management::DataCollection> partialResultsCollection
            = services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(partialResults));
        if(partialResultsCollection->size() <= id)
        {
            return services::SharedPtr<PartialResult<svdDense> >();
        }
        return services::staticPointerCast<PartialResult<svdDense>, data_management::SerializationIface>((*partialResultsCollection)[id]);
    }

    void check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        services::SharedPtr<data_management::DataCollection> collection =
            services::staticPointerCast<data_management::DataCollection, data_management::SerializationIface>(Argument::get(partialResults));
        size_t nBlocks = collection->size();
        if(collection->size() == 0)
        { this->_errors->add(services::ErrorIncorrectNumberOfInputNumericTables); return; }

        size_t nFeatures = getPartialResult(0)->get(pca::sumSquaresSVD)->getNumberOfColumns();
        if(nFeatures == 0)
        { this->_errors->add(services::ErrorIncorrectSizeOfInputNumericTable); return; }

        for(size_t j = 0; j < nBlocks; j++)
        {
            services::SharedPtr<data_management::NumericTable> nObservationsSVD = getPartialResult(j)->get(pca::nObservationsSVD);
            if(nObservationsSVD.get() == 0)
            { this->_errors->add(services::ErrorNullInputNumericTable); return; }
            if(nObservationsSVD->getNumberOfColumns() != 1)
            { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
            if(nObservationsSVD->getNumberOfRows() != 1)
            { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

            services::SharedPtr<data_management::NumericTable> sumSquaresSVD = getPartialResult(j)->get(pca::sumSquaresSVD);
            if(sumSquaresSVD.get() == 0)
            { this->_errors->add(services::ErrorNullInputNumericTable); return; }
            if(sumSquaresSVD->getNumberOfColumns() != nFeatures)
            { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
            if(sumSquaresSVD->getNumberOfRows() != 1)
            { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

            services::SharedPtr<data_management::NumericTable> sumSVD = getPartialResult(j)->get(pca::sumSVD);
            if(sumSVD.get() == 0)
            { this->_errors->add(services::ErrorNullInputNumericTable); return; }
            if(sumSVD->getNumberOfColumns() != nFeatures)
            { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
            if(sumSVD->getNumberOfRows() != 1)
            { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

            services::SharedPtr<data_management::DataCollection> auxiliaryData = getPartialResult(j)->get(pca::auxiliaryData);
            if(auxiliaryData->size() == 0)
            { this->_errors->add(services::ErrorIncorrectNumberOfOutputNumericTables); return; }
            for(size_t i = 0; i < auxiliaryData->size(); i++)
            {
                services::SharedPtr<data_management::NumericTable> table =
                    services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>((*auxiliaryData)[i]);
                if(table.get() == 0)
                { this->_errors->add(services::ErrorNullInputNumericTable); return; }
                if(table->getNumberOfColumns() != nFeatures)
                { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
                if(table->getNumberOfRows() != nFeatures)
                { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
            }
        }
    }

    /**
     * Returns the number of columns in the input data set
     * \return Number of columns in the input data set
     */
    size_t getNFeatures() const
    {
        return getPartialResult(0)->get(pca::sumSVD)->getNumberOfColumns();
    }
};

/**
 * <a name="DAAL-CLASS-PCA__RESULT"></a>
 * \brief Provides methods to access results obtained with the PCA algorithm
 */
class Result : public daal::algorithms::Result
{
public:
    Result() : daal::algorithms::Result(2) {};

    virtual ~Result() {};

    /**
    * Gets the results of the PCA algorithm
     * \param[in] id    Identifier of the input object
     * \return          Input object that corresponds to the given identifier
    */
    services::SharedPtr<data_management::NumericTable> get(ResultId id) const
    {
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Sets results of the PCA algorithm
     * \param[in] id      Identifier of the result
     * \param[in] value   Pointer to the object
     */
    void set(ResultId id, const services::SharedPtr<data_management::NumericTable> &value)
    {
        Argument::set(id, value);
    }

    /**
     * Allocates memory for storing partial results of the PCA algorithm
     * \param[in] input Pointer to an object containing input data
     * \param[in] parameter Algorithm parameter
     * \param[in] method Computation method
     */
    template<typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, daal::algorithms::Parameter *parameter, const Method method)
    {
        const Input *in = static_cast<const Input *>(input);
        size_t nFeatures = in->getNFeatures();

        set(eigenvalues,
            services::SharedPtr<data_management::NumericTable>(new data_management::HomogenNumericTable<algorithmFPType>
                                                               (nFeatures, 1, data_management::NumericTableIface::doAllocate, 0)));
        set(eigenvectors,
            services::SharedPtr<data_management::NumericTable>(new data_management::HomogenNumericTable<algorithmFPType>
                                                               (nFeatures, nFeatures, data_management::NumericTableIface::doAllocate, 0)));
    }

    /**
     * Allocates memory for storing partial results of the PCA algorithm     * \param[in] partialResult Pointer to an object containing input data
     * \param[in] parameter Parameter of the algorithm
     * \param[in] method        Computation method
     */
    template<typename algorithmFPType>
    void allocate(const daal::algorithms::PartialResult *partialResult, daal::algorithms::Parameter *parameter, const Method method)
    {
        const PartialResultBase *partialRes = static_cast<const PartialResultBase *>(partialResult);
        size_t nFeatures = partialRes->getNFeatures();

        set(eigenvalues,
            services::SharedPtr<data_management::NumericTable>(new data_management::HomogenNumericTable<algorithmFPType>
                                                               (nFeatures, 1,
                                                                data_management::NumericTableIface::doAllocate, 0)));
        set(eigenvectors,
            services::SharedPtr<data_management::NumericTable>(new data_management::HomogenNumericTable<algorithmFPType>
                                                               (nFeatures,
                                                                nFeatures, data_management::NumericTableIface::doAllocate, 0)));
    }

    /**
    * Checks the results of the PCA algorithm
    * \param[in] _input  %Input object of algorithm
    * \param[in] par     Algorithm %parameter
    * \param[in] method  Computation  method
    */
    void check(const daal::algorithms::Input *_input, const daal::algorithms::Parameter *par,
               int method) const DAAL_C11_OVERRIDE
    {
        const InputIface *input = static_cast<const InputIface *>(_input);
        if(Argument::size() != 2)
        { this->_errors->add(services::ErrorIncorrectNumberOfOutputNumericTables); return; }

        services::SharedPtr<data_management::NumericTable> eigenvaluesTable = get(eigenvalues);
        if(eigenvaluesTable.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(eigenvaluesTable->getNumberOfColumns() != input->getNFeatures())
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(eigenvaluesTable->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> eigenvectorsTable = get(eigenvectors);
        if(eigenvectorsTable.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(eigenvectorsTable->getNumberOfColumns() != input->getNFeatures())
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(eigenvectorsTable->getNumberOfRows() != input->getNFeatures())
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
    }

    /**
    * Checks the results of the PCA algorithm
    * \param[in] pr             Partial results of the algorithm
    * \param[in] method         Computation method
    * \param[in] parameter      Algorithm %parameter
    */
    void check(const daal::algorithms::PartialResult *pr, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        if(Argument::size() != 2)
        { this->_errors->add(services::ErrorIncorrectNumberOfOutputNumericTables); return; }

        services::SharedPtr<data_management::NumericTable> eigenvaluesTable = get(eigenvalues);
        if(eigenvaluesTable.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }

        size_t nFeatures = eigenvaluesTable->getNumberOfColumns();
        if(eigenvaluesTable->getNumberOfRows() != 1)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }

        services::SharedPtr<data_management::NumericTable> eigenvectorsTable = get(eigenvectors);
        if(eigenvectorsTable.get() == 0)
        { this->_errors->add(services::ErrorNullInputNumericTable); return; }
        if(eigenvectorsTable->getNumberOfColumns() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfFeatures); return; }
        if(eigenvectorsTable->getNumberOfRows() != nFeatures)
        { this->_errors->add(services::ErrorIncorrectNumberOfObservations); return; }
    }

    int getSerializationTag() { return SERIALIZATION_PCA_RESULT_ID; }

    /**
    *  Serializes the object
    *  \param[in]  arch  Storage for the serialized object or data structure
    */
    void serializeImpl(data_management::InputDataArchive  *arch)
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
    *  Deserializes the object
    *  \param[in]  arch  Storage for the deserialized object or data structure
    */
    void deserializeImpl(data_management::OutputDataArchive *arch)
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
using interface1::InputIface;
using interface1::Input;
using interface1::PartialResultBase;
using interface1::PartialResult;
using interface1::PartialResultImpl;
using interface1::PartialResultsInitIface;
using interface1::DefaultPartialResultsInit;
using interface1::BatchParameter;
using interface1::OnlineParameter;
using interface1::DistributedParameter;
using interface1::DistributedInput;
using interface1::Result;

}
}
} // namespace daal
#endif
