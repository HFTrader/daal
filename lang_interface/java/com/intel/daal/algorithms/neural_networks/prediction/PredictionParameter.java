/* file: PredictionParameter.java */
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

package com.intel.daal.algorithms.neural_networks.prediction;

import com.intel.daal.services.DaalContext;
import com.intel.daal.algorithms.Precision;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__PREDICTION__PREDICTIONPARAMETER"></a>
 * \brief Class representing the parameters of neural network
 */
public class PredictionParameter extends com.intel.daal.algorithms.Parameter {
    /**
     * Constructs the parameters of neural network algorithm
     * @param context   Context to manage the parameter object
     * @param cls       Data type to use in intermediate computations, Double.class or Float.class
     */
    public PredictionParameter(DaalContext context, Class <? extends Number> cls) {
        super(context);
        cObject = cInit();
    }

    public PredictionParameter(DaalContext context, long cParameter) {
        super(context, cParameter);
    }

    private native long cInit();
}
