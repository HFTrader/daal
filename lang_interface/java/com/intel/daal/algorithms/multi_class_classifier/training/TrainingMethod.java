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

package com.intel.daal.algorithms.multi_class_classifier.training;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTI_CLASS_CLASSIFIER__TRAINING__TRAININGMETHOD"></a>
 * @brief Computation methods for the multi-class classifier algorithm
 */
public final class TrainingMethod {

    private int _value;

    public TrainingMethod(int value) {
        _value = value;
    }

    public int getValue() {
        return _value;
    }

    private static final int OneAgainstOne = 0;

    public static final TrainingMethod oneAgainstOne = new TrainingMethod(OneAgainstOne); /*!< One-Against-One method */
}
