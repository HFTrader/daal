/* file: Method.java */
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

package com.intel.daal.algorithms.kmeans;

/**
 * <a name="DAAL-CLASS-ALGORITHM__KMEANS__METHOD"></a>
 * @brief Available methods of the K-Means algorithm
 */
public final class Method {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    private int _value;

    public Method(int value) {
        _value = value;
    }

     /**
     * Returns a value corresponding to the identifier of the input object
     * \return Value corresponding to the identifier
     */
    public int getValue() {
        return _value;
    }

    private static final int lloydDenseValue = 0;
    private static final int lloydCSRValue   = 1;

    public static final Method defaultDense = new Method(lloydDenseValue); /*!< Default: performance-oriented method, synonym of lloydDense */
    public static final Method lloydDense   = new Method(lloydDenseValue); /*!< Default: performance-oriented method, synonym of defaultDense */
    public static final Method lloydCSR     = new Method(lloydCSRValue);   /*!< Method for sparse data in the CSR format */
}
