/* file: FileDataSource.java */
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

package com.intel.daal.data_management.data_source;

import com.intel.daal.services.DaalContext;

/**
 *  <a name="DAAL-CLASS-DATASOURCE__FILEDATASOURCE__FILEDATASOURCE"></a>
 * @brief Specifies the methods for accessing the data stored in files
 */
public class FileDataSource extends DataSource {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     *Default constructor
     */
    public FileDataSource(DaalContext context, String filename) {
        super(context);

        cObject = cInit(filename);
    }

    /**
     * Constructor
     */
    public FileDataSource(DaalContext context, String filename, DictionaryCreationFlag doDict,
            NumericTableAllocationFlag doNT) {
        super(context);

        cObject = cInit(filename);
        if (doDict.ordinal() == DictionaryCreationFlag.DoDictionaryFromContext.ordinal()) {
            this.createDictionaryFromContext();
        }

        if (doNT.ordinal() == NumericTableAllocationFlag.DoAllocateNumericTable.ordinal()) {
            this.allocateNumericTable();
        }
    }

    protected native long cInit(String filename);
}
