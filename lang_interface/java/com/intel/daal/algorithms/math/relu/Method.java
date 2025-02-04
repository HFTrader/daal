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

package com.intel.daal.algorithms.math.relu;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__RELU__METHOD"></a>
 * @brief Available methods for rectified linear function
 */
public final class Method {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    private int _value;

    /**
     * Constructs the method object using the provided identifier
     */
    public Method(int value) {
        _value = value;
    }

    /**
     * Returns the value of the method identifier
     * @return Value of the method identifier
     */
    public int getValue() {
        return _value;
    }

    private static final int   DefaultMethodValue = 0;
    private static final int   FastCSRMethodValue = 1;
    public static final Method defaultDense       = new Method(DefaultMethodValue); /*!< Default method */
    public static final Method fastCSR            = new Method(FastCSRMethodValue); /*!< Default: performance-oriented method.
                                                                                    Works with Compressed Sparse Rows(CSR)
                                                                                    input numeric tables */
}
