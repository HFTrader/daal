/* file: AveragePooling3DLayerBatch.java */
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

/*
 //  Content:
 //  Java example of neural network three-dimensional average pooling layer forward and backpropagation usage.
 ////////////////////////////////////////////////////////////////////////////////
 */

package com.intel.daal.examples.neural_networks;

import com.intel.daal.algorithms.neural_networks.layers.average_pooling3d.*;
import com.intel.daal.algorithms.neural_networks.layers.pooling3d.SpatialDimensions;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultLayerDataId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputLayerDataId;
import com.intel.daal.data_management.data.Tensor;
import com.intel.daal.data_management.data.HomogenTensor;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-EXAMPLE-JAVA-AVERAGEPOOLING3DLAYERBATCH">
 * @example AveragePooling3DLayerBatch.java
 */
class AveragePooling3DLayerBatch {
    private static DaalContext context = new DaalContext();
    static float dataArray[] = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9, 10, 11, 12,
        13, 14, 15, 16,
        17, 18, 19, 20,
        21, 22, 23, 24
    };
    static long[] dims = {3, 2, 4};

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Read datasetFileName from a file and create a tensor to store input data */

        HomogenTensor data = new HomogenTensor(context, dims, dataArray);

        long nDim = data.getDimensions().length;

        /* Print the input of the forward three-dimensional pooling */
        Service.printTensor("Forward three-dimensional pooling input:", data, 0, 0);

        /* Create an algorithm to compute forward three-dimensional pooling layer results using average method */
        ForwardBatch averagePooling3DLayerForward = new ForwardBatch(context, Double.class, Method.defaultDense, nDim);

        /* Set input objects for the forward three-dimensional pooling */
        averagePooling3DLayerForward.input.set(ForwardInputId.data, data);

        /* Compute forward three-dimensional pooling results */
        ForwardResult forwardResult = averagePooling3DLayerForward.compute();

        /* Print the results of the forward three-dimensional average pooling layer */
        Service.printTensor("Forward three-dimensional pooling result:", forwardResult.get(ForwardResultId.value), 0, 0);
        Service.printNumericTable("Forward three-dimensional average pooling layer input dimensions:",
                                  forwardResult.get(LayerDataId.auxInputDimensions));

        /* Create an algorithm to compute backward three-dimensional pooling layer results using average method */
        BackwardBatch averagePooling3DLayerBackward = new BackwardBatch(context, Double.class, Method.defaultDense, nDim);

        /* Set input objects for the backward three-dimensional average pooling layer */
        averagePooling3DLayerBackward.input.set(BackwardInputId.inputGradient, forwardResult.get(ForwardResultId.value));
        averagePooling3DLayerBackward.input.set(BackwardInputLayerDataId.inputFromForward,
                                                forwardResult.get(ForwardResultLayerDataId.resultForBackward));

        /* Compute backward three-dimensional pooling results */
        BackwardResult backwardResult = averagePooling3DLayerBackward.compute();

        /* Print the results of the backward three-dimensional average pooling layer */
        Service.printTensor("Backward three-dimensional pooling result:", backwardResult.get(BackwardResultId.gradient), 0, 0);

        context.dispose();
    }
}
