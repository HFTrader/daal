/* file: string_data_source.h */
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
//  Implementation of the string data source class.
//--
*/

#ifndef __STRING_DATA_SOURCE_H__
#define __STRING_DATA_SOURCE_H__

#include <sstream>
#include "services/daal_memory.h"
#include "data_management/data_source/data_source.h"
#include "data_management/data/data_dictionary.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/homogen_numeric_table.h"

namespace daal
{
namespace data_management
{

namespace interface1
{
/**
 *  <a name="DAAL-CLASS-STRINGDATASOURCE"></a>
 *  \brief Specifies methods to access data stored in byte arrays in the C-string format
 *  \tparam _featureManager     FeatureManager used to get numeric data from file strings
 */
template< typename _featureManager, typename _summaryStatisticsType = double >
class StringDataSource : public DataSourceTemplate<data_management::HomogenNumericTable<double>, _summaryStatisticsType>
{
public:
    using DataSourceIface::NumericTableAllocationFlag;
    using DataSourceIface::DictionaryCreationFlag;
    using DataSourceIface::DataSourceStatus;

    using DataSource::checkDictionary;
    using DataSource::checkNumericTable;
    using DataSource::freeNumericTable;
    using DataSource::_dict;
    using DataSource::_initialMaxRows;

    /**
     *  Typedef that stores the Feature Manager data type
     */
    typedef _featureManager FeatureManager;

protected:
    typedef data_management::HomogenNumericTable<double> DefaultNumericTableType;

    FeatureManager featureManager;

public:
    /**
     *  Main constructor for a Data Source
     *  \param[in]  data                            Byte array in the C-string format
     *  \param[in]  doAllocateNumericTable          Flag that specifies whether a Numeric Table
     *                                              associated with a File Data Source is allocated inside the Data Source
     *  \param[in]  doCreateDictionaryFromContext   Flag that specifies whether a Data Dictionary
     *                                              is created from the context of the File Data Source
     *  \param[in]  initialMaxRows                  Initial value of maximum number of rows in Numeric Table allocated in loadDataBlock() method
     */
    StringDataSource( const byte *data,
                      DataSourceIface::NumericTableAllocationFlag doAllocateNumericTable    = DataSource::notAllocateNumericTable,
                      DataSourceIface::DictionaryCreationFlag doCreateDictionaryFromContext = DataSource::notDictionaryFromContext,
                      size_t initialMaxRows = 10):
        DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>(doAllocateNumericTable, doCreateDictionaryFromContext)
    {
        _rawLineBufferLen = 1024;
        _rawLineBuffer    = (char *)daal::services::daal_malloc( _rawLineBufferLen );
        if( _rawLineBuffer == 0 ) { this->_errors->add(services::ErrorMemoryAllocationFailed); return; }

        setData( data );

        _contextDictFlag = false;

        _initialMaxRows = initialMaxRows;
    }

    ~StringDataSource()
    {
        daal::services::daal_free( _rawLineBuffer );
        DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::freeNumericTable();
        if( _contextDictFlag )
        {
            delete _dict;
        }
    }

    /**
     *  Sets a new string as a source for data
     *  \param[in]  data  Byte array in the C-string format
     */
    void setData( const byte *data )
    {
        _istream.str( (char*)data );
        _istream.clear();
    }

    /**
     *  Gets data source string data
     *  \return  Byte array in the C-string format
     */
    const byte *getData()
    {
        return (const byte *)(_istream.str().c_str());
    }

    /**
     *  Resets a data source string
     */
    void resetData()
    {
        _istream.str("");
    }

    /**
     *  Returns a Feature Manager associated with a String Data Source
     *  \return Feature Manager associated with the String Data Source
     */
    FeatureManager &getFeatureManager()
    {
        return featureManager;
    }

public:
    size_t loadDataBlock(size_t maxRows) DAAL_C11_OVERRIDE
    {
        checkDictionary();
        if( this->getErrors()->size() != 0 ) { return 0; }

        checkNumericTable();
        if( this->getErrors()->size() != 0 ) { return 0; }

        return loadDataBlock(maxRows, this->DataSource::_spnt.get());
    }

    size_t loadDataBlock(size_t maxRows, NumericTable *nt) DAAL_C11_OVERRIDE
    {
        checkDictionary();
        if( this->getErrors()->size() != 0 ) { return 0; }

        if( nt == NULL ) { this->_errors->add(services::ErrorNullInputNumericTable); return 0; }

        size_t j;

        DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::resizeNumericTableImpl( maxRows, nt );

        nt->setNormalizationFlag(NumericTable::nonNormalized);

        for( j = 0; j < maxRows && !_istream.eof() ; j++ )
        {
            readLine();
            if (_rawLineLength == 0) { break; }
            if(this->_errors->size() != 0) { break; }
            featureManager.parseRowIn( _rawLineBuffer, _rawLineLength, _dict, nt, j );

            DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::updateStatistics( j, nt );
        }

        nt->setNumberOfRows( j );

        NumericTableDictionary *ntDict = nt->getDictionary();
        size_t nFeatures = _dict->getNumberOfFeatures();
        ntDict->setNumberOfFeatures(nFeatures);
        for (size_t i = 0; i < nFeatures; i++)
        {
            ntDict->setFeature((*_dict)[i].ntFeature, i);
        }

        return j;
    }

    size_t loadDataBlock(size_t maxRows, size_t rowOffset, size_t fullRows) DAAL_C11_OVERRIDE
    {
        checkDictionary();
        if( this->getErrors()->size() != 0 ) { return 0; }

        checkNumericTable();
        if( this->getErrors()->size() != 0 ) { return 0; }

        return loadDataBlock(maxRows, rowOffset, fullRows, this->DataSource::_spnt.get());
    }

    size_t loadDataBlock(size_t maxRows, size_t rowOffset, size_t fullRows, NumericTable *nt) DAAL_C11_OVERRIDE
    {
        checkDictionary();
        if( this->getErrors()->size() != 0 ) { return 0; }

        if( nt == NULL ) { this->_errors->add(services::ErrorNullInputNumericTable); return 0; }

        DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::resizeNumericTableImpl( fullRows, nt );

        nt->setNormalizationFlag(NumericTable::nonNormalized);

        size_t j;

        for( j = 0; j < maxRows && !_istream.eof() ; j++ )
        {
            readLine();
            if (_rawLineLength == 0) { break; }
            if(this->_errors->size() != 0) { break; }
            featureManager.parseRowIn( _rawLineBuffer, _rawLineLength, _dict, nt, rowOffset + j );

            DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::updateStatistics( rowOffset + j, nt );
        }

        NumericTableDictionary *ntDict = nt->getDictionary();
        size_t nFeatures = _dict->getNumberOfFeatures();
        ntDict->setNumberOfFeatures(nFeatures);
        for (size_t i = 0; i < nFeatures; i++)
        {
            ntDict->setFeature((*_dict)[i].ntFeature, i);
        }

        return fullRows;
    }

    size_t loadDataBlock() DAAL_C11_OVERRIDE
    {
        checkDictionary();
        if( this->_errors->size() != 0 ) { return 0; }

        checkNumericTable();
        if( this->_errors->size() != 0 ) { return 0; }

        return loadDataBlock(this->DataSource::_spnt.get());
    }

    size_t loadDataBlock(NumericTable* nt) DAAL_C11_OVERRIDE
    {
        checkDictionary();
        if( this->_errors->size() != 0 ) { return 0; }

        if( nt == NULL ) { this->_errors->add(services::ErrorNullInputNumericTable); return 0; }

        size_t maxRows = (_initialMaxRows > 0 ? _initialMaxRows : 10);
        size_t nrows = 0;
        size_t ncols = _dict->getNumberOfFeatures();

        DataCollection tables;

        for( ; ; )
        {
            NumericTable *ntCurrent = new HomogenNumericTable<double>(ncols, maxRows, NumericTableIface::doAllocate);
            if (ntCurrent == NULL)
            {
                this->_errors->add(services::ErrorNumericTableNotAllocated);
                break;
            }
            tables.push_back(services::SharedPtr<NumericTable>(ntCurrent));
            size_t rows = loadDataBlock(maxRows, ntCurrent);
            nrows += rows;
            if (rows < maxRows) { break; }
            maxRows *= 2;
        }

        DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::resizeNumericTableImpl( nrows, nt );
        nt->setNormalizationFlag(NumericTable::nonNormalized);

        BlockDescriptor<double> blockCurrent, block;

        size_t pos = 0;

        for (size_t i = 0; i < tables.size(); i++) {
            NumericTable *ntCurrent = (NumericTable*)(tables[i].get());
            size_t rows = ntCurrent->getNumberOfRows();

            if (rows == 0) { continue; }

            ntCurrent->getBlockOfRows(0, rows, readOnly, blockCurrent);
            nt->getBlockOfRows(pos, rows, writeOnly, block);

            services::daal_memcpy_s(block.getBlockPtr(), rows * ncols * sizeof(double), blockCurrent.getBlockPtr(), rows * ncols * sizeof(double));

            ntCurrent->releaseBlockOfRows(blockCurrent);
            nt->releaseBlockOfRows(block);

            DataSourceTemplate<DefaultNumericTableType, _summaryStatisticsType>::combineStatistics( ntCurrent, nt, pos == 0);
            pos += rows;
        }

        NumericTableDictionary *ntDict = nt->getDictionary();
        size_t nFeatures = _dict->getNumberOfFeatures();
        ntDict->setNumberOfFeatures(nFeatures);
        for (size_t i = 0; i < nFeatures; i++)
        {
            ntDict->setFeature((*_dict)[i].ntFeature, i);
        }

        return nrows;
    }

    void createDictionaryFromContext() DAAL_C11_OVERRIDE
    {
        if( _dict != NULL ) { this->_errors->add(services::ErrorDictionaryAlreadyAvailable); return; }

        _contextDictFlag = true;
        _dict = new DataSourceDictionary();

        readLine();
        if( this->_errors->size() != 0 ) { return; }

        featureManager.parseRowAsDictionary( _rawLineBuffer, _rawLineLength, _dict );

        if( this->_errors->size() != 0 )
        {
            delete _dict;
            _dict = NULL;
        }

        _istream.seekg(0);
        _istream.clear();
    }

    DataSourceIface::DataSourceStatus getStatus() DAAL_C11_OVERRIDE
    {
        if( _istream.eof() )
        {
            return DataSourceIface::endOfData;
        }
        else
        {
            return DataSourceIface::readyForLoad;
        }
    }

    size_t getNumberOfAvailableRows() DAAL_C11_OVERRIDE
    {
        return 0;
    }

protected:
    void enlargeBuffer()
    {
        _rawLineBufferLen *= 2;
        daal::services::daal_free( _rawLineBuffer );
        _rawLineBuffer = (char *)daal::services::daal_malloc( _rawLineBufferLen );
        if( _rawLineBuffer == 0 ) { this->_errors->add(services::ErrorMemoryAllocationFailed); return; }
    }

    void readLine()
    {
        std::streampos position = _istream.tellg();

        _istream.getline( _rawLineBuffer, _rawLineBufferLen );
        while( _istream.rdstate() & std::istringstream::failbit )
        {
            if( _istream.rdstate() & std::istringstream::eofbit )
            {
                _rawLineLength = 0;
                return;
            }
            enlargeBuffer();
            if( this->_errors->size() != 0 ) { return; }

            _istream.clear();
            _istream.seekg( position );
            _istream.getline( _rawLineBuffer, _rawLineBufferLen );
        }

        _rawLineLength = (size_t)_istream.gcount();
    }

private:
    std::istringstream _istream;

    char *_rawLineBuffer;
    int   _rawLineBufferLen;

    size_t _rawLineLength;

    bool _contextDictFlag;
};
} // namespace interface1
using interface1::StringDataSource;

}
}
#endif
