/* file: TrainingMethod.java */
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

package com.intel.daal.algorithms.svm.training;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__SVM__TRAINING__TRAININGMETHOD"></a>
 * @brief Available methods to train the SVM model
 */
public final class TrainingMethod {

    private int _value;

    public TrainingMethod(int value) {
        _value = value;
    }

    public int getValue() {
        return _value;
    }

    private static final int BoserValue = 0;

    public static final TrainingMethod boser = new TrainingMethod(BoserValue); /*!< Method proposed by Boser et al. */
}
