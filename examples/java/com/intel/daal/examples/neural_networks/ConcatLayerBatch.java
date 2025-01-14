/* file: ConcatLayerBatch.java */
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
 //     Java example of concat layer in the batch processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

package com.intel.daal.examples.neural_networks;

import com.intel.daal.algorithms.neural_networks.layers.concat.*;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultLayerDataId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardInputLayerDataId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardResultLayerDataId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputLayerDataId;
import com.intel.daal.data_management.data.Tensor;
import com.intel.daal.data_management.data.HomogenTensor;
import com.intel.daal.data_management.data.KeyValueDataCollection;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-EXAMPLE-JAVA-CONCATLAYERBATCH">
 * @example ConcatLayerBatch.java
 */
class ConcatLayerBatch {
    private static final String datasetFileName = "../data/batch/layer.csv";
    private static DaalContext context = new DaalContext();
    private static final long concatDimension = 1;

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Read datasetFileName from a file and create a tensor to store forward input data */
        Tensor data = Service.readTensorFromCSV(context, datasetFileName);
        KeyValueDataCollection dataCollection = new KeyValueDataCollection(context);

        for (int i = 0; i < 3; i++) {
            dataCollection.set(i, data);
        }

        /* Create an algorithm to compute forward concat layer results using default method */
        ForwardBatch forwardLayer = new ForwardBatch(context, Double.class, Method.defaultDense);
        forwardLayer.parameter.setConcatDimension(concatDimension);

        /* Set input objects for the forward concat layer */
        forwardLayer.input.set(ForwardInputLayerDataId.inputLayerData, dataCollection);

        /* Compute forward concat layer results */
        ForwardResult forwardResult = forwardLayer.compute();

        /* Print the results of the forward concat layer */
        Service.printTensor("Forward concatenation layer result (first 5 rows):", forwardResult.get(ForwardResultId.value), 5, 0);

        /* Create an algorithm to compute backward concat layer results using default method */
        BackwardBatch backwardLayer = new BackwardBatch(context, Double.class, Method.defaultDense);
        backwardLayer.parameter.setConcatDimension(concatDimension);

        /* Set input objects for the backward concat layer */
        backwardLayer.input.set(BackwardInputId.inputGradient, forwardResult.get(ForwardResultId.value));
        backwardLayer.input.set(BackwardInputLayerDataId.inputFromForward, forwardResult.get(ForwardResultLayerDataId.resultForBackward));

        Service.printNumericTable("auxInputDimension", forwardResult.get(LayerDataId.auxInputDimensions), 5, 0);

        /* Compute backward concat layer results */
        BackwardResult backwardResult = backwardLayer.compute();

        /* Print the results of the backward concat layer */
        for (int i = 0; i < dataCollection.size(); i++) {
            Service.printTensor("Backward concatenation layer result (first 5 rows):",
                                backwardResult.get(BackwardResultLayerDataId.resultLayerData, i), 5, 0);
        }
        context.dispose();
    }
}
