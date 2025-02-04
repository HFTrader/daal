/* file: MaximumPooling1DLayerBatch.java */
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
 //  Java example of neural network one-dimensional maximum pooling layer forward and backpropagation usage.
 ////////////////////////////////////////////////////////////////////////////////
 */

package com.intel.daal.examples.neural_networks;

import com.intel.daal.algorithms.neural_networks.layers.maximum_pooling1d.*;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultLayerDataId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputLayerDataId;
import com.intel.daal.data_management.data.Tensor;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-EXAMPLE-JAVA-MAXIMUMPOOLING1DLAYERBATCH">
 * @example MaximumPooling1DLayerBatch.java
 */
class MaximumPooling1DLayerBatch {
    private static final String datasetFileName = "../data/batch/layer.csv";
    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Read datasetFileName from a file and create a tensor to store input data */
        Tensor data = Service.readTensorFromCSV(context, datasetFileName);
        long nDim = data.getDimensions().length;

        /* Print the input of the forward one-dimensional pooling */
        Service.printTensor("Forward one-dimensional maximum pooling layer input (first 10 rows):", data, 10, 0);

        /* Create an algorithm to compute forward one-dimensional pooling layer results using maximum method */
        ForwardBatch maximumPooling1DLayerForward = new ForwardBatch(context, Double.class, Method.defaultDense, nDim);

        /* Set input objects for the forward one-dimensional pooling */
        maximumPooling1DLayerForward.input.set(ForwardInputId.data, data);

        /* Compute forward one-dimensional pooling results */
        ForwardResult forwardResult = maximumPooling1DLayerForward.compute();

        /* Print the results of the forward one-dimensional maximum pooling layer */
        Service.printTensor("Forward one-dimensional pooling result (first 5 rows):", forwardResult.get(ForwardResultId.value), 5, 0);
        Service.printTensor("Forward one-dimensional maximum pooling layer mask (first 5 rows):", forwardResult.get(LayerDataId.auxMask), 5, 0);

        /* Create an algorithm to compute backward one-dimensional pooling layer results using maximum method */
        BackwardBatch maximumPooling1DLayerBackward = new BackwardBatch(context, Double.class, Method.defaultDense, nDim);

        /* Set input objects for the backward one-dimensional maximum pooling layer */
        maximumPooling1DLayerBackward.input.set(BackwardInputId.inputGradient, forwardResult.get(ForwardResultId.value));
        maximumPooling1DLayerBackward.input.set(BackwardInputLayerDataId.inputFromForward,
                                                forwardResult.get(ForwardResultLayerDataId.resultForBackward));

        /* Compute backward one-dimensional pooling results */
        BackwardResult backwardResult = maximumPooling1DLayerBackward.compute();

        /* Print the results of the backward one-dimensional maximum pooling layer */
        Service.printTensor("Backward one-dimensional pooling result (first 10 rows):", backwardResult.get(BackwardResultId.gradient), 10, 0);

        context.dispose();
    }
}
