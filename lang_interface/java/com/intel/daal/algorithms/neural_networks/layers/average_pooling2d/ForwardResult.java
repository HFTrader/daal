/* file: ForwardResult.java */
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

package com.intel.daal.algorithms.neural_networks.layers.average_pooling2d;

import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__AVERAGE_POOLING2D__FORWARDRESULT"></a>
 * @brief Class that provides methods to access the result obtained with the compute() method
 *        of the forward two-dimensional average pooling layer
 */
public final class ForwardResult extends com.intel.daal.algorithms.neural_networks.layers.pooling2d.ForwardResult {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    public ForwardResult(DaalContext context, long cObject) {
        super(context, cObject);
    }

    /**
    * Constructs the forward two-dimensional average pooling layer
    * @param context   Context to manage the forward two-dimensional average pooling layer
    */
    public ForwardResult(DaalContext context) {
        super(context);
        this.cObject = cNewResult();
    }

    /**
     * Returns the result of the forward two-dimensional average pooling layer
     * @param  id   Identifier of the result
     * @return Result that corresponds to the given identifier
     */
    public NumericTable get(LayerDataId id) {
        if (id == LayerDataId.auxInputDimensions) {
            return new HomogenNumericTable(getContext(), cGetValue(cObject, id.getValue()));
        }
        else {
            throw new IllegalArgumentException("id unsupported");
        }
    }

    /**
     * Sets the result of the forward two-dimensional average pooling layer
     * @param id   Identifier of the result
     * @param val  Result that corresponds to the given identifier
     */
    public void set(LayerDataId id, NumericTable val) {
        if (id == LayerDataId.auxInputDimensions) {
            cSetValue(cObject, id.getValue(), val.getCObject());
        }
        else {
            throw new IllegalArgumentException("id unsupported");
        }
    }

    private native long cNewResult();
    private native long cGetValue(long cObject, int id);
    private native void cSetValue(long cObject, int id, long ntAddr);
}
