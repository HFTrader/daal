/* file: DistributedPartialResultId.java */
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

package com.intel.daal.algorithms.svd;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__SVD__DISTRIBUTEDPARTIALRESULTID"></a>
 * @brief Available types of partial results of the second step of the SVD algorithm in the distributed processing mode, stored in the Result object
 */
public final class DistributedPartialResultId {
    private int _value;

    static {
        System.loadLibrary("JavaAPI");
    }

    public DistributedPartialResultId(int value) {
        _value = value;
    }

    public int getValue() {
        return _value;
    }

    private static final int finalResultFromStep2MasterId = 0;

    /** Result object with singular values and the right orthogonal matrix */
    public static final DistributedPartialResultId finalResultFromStep2Master = new DistributedPartialResultId(
            finalResultFromStep2MasterId);
}
