/* file: SGDMiniBatch.java */
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
 //     Java example of dense mini-batch SGD in the batch processing mode
 //     processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-SGDMINIBATCH">
 * @example SGDMiniBatch.java
 */

package com.intel.daal.examples.optimization_solver;

import com.intel.daal.algorithms.optimization_solver.sgd.*;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data.MergedNumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

class SGDMiniBatch {
    private static final long nFeatures = 3;
    private static final double accuracyThreshold = 0.0000001;
    private static final long nIterations = 1000;
    private static final long batchSize = 4;
    private static final double learningRate = 0.5;
    private static double[] startPoint = {8, 2, 1, 4};

    /* Input data set parameters */
    private static final String dataFileName = "../data/batch/mse.csv";

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        /* Retrieve the data from input data sets */
        FileDataSource dataSource = new FileDataSource(context, dataFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for data and values for dependent variable */
        NumericTable data = new HomogenNumericTable(context, Double.class, nFeatures, 0, NumericTable.AllocationFlag.NotAllocate);
        NumericTable dataDependents = new HomogenNumericTable(context, Double.class, 1, 0, NumericTable.AllocationFlag.NotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(data);
        mergedData.addNumericTable(dataDependents);

        /* Retrieve the data from an input file */
        dataSource.loadDataBlock(mergedData);

        /* Create an MSE objective function to compute a mini-batch SGD */
        com.intel.daal.algorithms.optimization_solver.mse.Batch mseFunction =
            new com.intel.daal.algorithms.optimization_solver.mse.Batch(context, Double.class,
                    com.intel.daal.algorithms.optimization_solver.mse.Method.defaultDense, data.getNumberOfRows());

        mseFunction.getInput().set(com.intel.daal.algorithms.optimization_solver.mse.InputId.data, data);
        mseFunction.getInput().set(com.intel.daal.algorithms.optimization_solver.mse.InputId.dependentVariables, dataDependents);

        /* Create algorithm objects to compute mini-batch SGD results */
        Batch sgdAlgorithm = new Batch(context, Double.class, Method.miniBatch);
        ParameterMiniBatch algorithmParameter = (ParameterMiniBatch)sgdAlgorithm.parameter;
        algorithmParameter.setFunction(mseFunction);
        algorithmParameter.setLearningRateSequence(
            new HomogenNumericTable(context, Double.class, 1, 1, NumericTable.AllocationFlag.DoAllocate, learningRate));
        algorithmParameter.setNIterations(nIterations);
        algorithmParameter.setAccuracyThreshold(accuracyThreshold);
        algorithmParameter.setBatchSize(batchSize);
        sgdAlgorithm.getInput().set(InputId.inputArgument, new HomogenNumericTable(context, startPoint, nFeatures + 1, 1));

        /* Compute the mini-batch SGD result for MSE objectiove function matrix */
        Result result = sgdAlgorithm.compute();

        Service.printNumericTable("Minimum:",  result.get(ResultId.minimum));
        Service.printNumericTable("Number of iterations performed:",  result.get(ResultId.nIterations));

        context.dispose();
    }
}
