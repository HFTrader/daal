/* file: InputDataCollection.java */
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

package com.intel.daal.algorithms.logitboost.quality_metric_set;

import com.intel.daal.algorithms.ComputeMode;
import com.intel.daal.algorithms.classifier.quality_metric.multi_class_confusion_matrix.MultiClassConfusionMatrixInput;
import com.intel.daal.services.DaalContext;

/**
 *  <a name="DAAL-CLASS-ALGORITHMS__LOGITBOOST__QUALITYMETRICSET__INPUTDATACOLLECTION"></a>
 *  @brief Class that implements functionality of the collection of input objects for the quality metrics algorithm
 */
public class InputDataCollection extends com.intel.daal.algorithms.quality_metric_set.InputDataCollection {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    public InputDataCollection(DaalContext context, long cAlgorithm, ComputeMode cmode) {
        super(context, cAlgorithm, cmode);
    }

    /**
     * Returns the element that matches the identifier
     * @param  id    Identifier of the quality metric
     * @return Input object
     */
    public MultiClassConfusionMatrixInput getInput(QualityMetricId id) {
        if (id != QualityMetricId.confusionMatrix) {
            throw new IllegalArgumentException("id unsupported");
        }
        return new MultiClassConfusionMatrixInput(getContext(), cGetInput(getCObject(), id.getValue()));
    }
}
