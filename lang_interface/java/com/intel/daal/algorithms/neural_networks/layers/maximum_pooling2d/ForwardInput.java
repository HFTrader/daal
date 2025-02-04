/* file: ForwardInput.java */
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

package com.intel.daal.algorithms.neural_networks.layers.maximum_pooling2d;

import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__MAXIMUM_POOLING2D__FORWARDINPUT"></a>
 * @brief %Input object for the forward two-dimensional maximum pooling layer
 */
public class ForwardInput extends com.intel.daal.algorithms.neural_networks.layers.pooling2d.ForwardInput {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    public ForwardInput(DaalContext context, long cObject) {
        super(context, cObject);
    }
}
