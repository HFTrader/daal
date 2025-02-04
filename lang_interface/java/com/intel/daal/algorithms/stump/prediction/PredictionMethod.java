/* file: PredictionMethod.java */
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

/**
 * @brief Contains classes to make prediction based on the decision stump model
 */
package com.intel.daal.algorithms.stump.prediction;

/**
 * <a name="DAAL-ENUM-ALGORITHMS__STUMP__PREDICTION__PREDICTIONMETHOD"></a>
 * \brief Available methods to make prediction based on the decision stump model
 */
public final class PredictionMethod {

    private int _value;

    public PredictionMethod(int value) {
        _value = value;
    }

    public int getValue() {
        return _value;
    }

    private static final int DefaultDense = 0;

    /** Default method */
    public static final PredictionMethod defaultDense = new PredictionMethod(DefaultDense);
}
