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

package com.intel.daal.algorithms.multivariate_outlier_detection;

/**
 * <a name="DAAL-CLASS-ALGORITHM__MULTIVARIATE_OUTLIER_DETECTION__METHOD"></a>
 * @brief Available methods for computing the results of the multivariate outlier detection
 */
public final class Method {

    private int _value;

    public Method(int value) {
        _value = value;
    }

    public int getValue() {
        return _value;
    }

    private static final int defaultDenseValue = 0;
    private static final int baconDenseValue   = 1;

    /** Default method */
    public static final Method defaultDense = new Method(defaultDenseValue);

    /** Blocked Adaptive Computationally-efficient Outlier Nominators(BACON) method */
    public static final Method baconDense = new Method(baconDenseValue);
}
