/* file: LinearRegressionQROnline.java */
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
 //     Java example of multiple linear regression in the online processing mode.
 //
 //     The program trains the multiple linear regression model on a training
 //     data set with a QR decomposition-based method and computes regression
 //     for the test data.
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-LINEARREGRESSIONQRONLINE">
 * @example LinearRegressionQROnline.java
 */

package com.intel.daal.examples.linear_regression;

import com.intel.daal.algorithms.linear_regression.Model;
import com.intel.daal.algorithms.linear_regression.prediction.*;
import com.intel.daal.algorithms.linear_regression.training.*;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.MergedNumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

class LinearRegressionQROnline {
    /* Input data set parameters */
    private static final String trainDatasetFileName = "../data/online/linear_regression_train.csv";

    private static final String testDatasetFileName  = "../data/online/linear_regression_test.csv";

    private static final int nFeatures            = 10;
    private static final int nDependentVariables  = 2;
    private static final int nTrainVectorsInBlock = 250;

    static Model        model;
    static NumericTable results;
    static NumericTable testDependentVariables;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        trainModel();

        testModel();

        printResults();

        context.dispose();
    }

    private static void trainModel() {

        /* Initialize FileDataSource to retrieve the input data from a .csv file */
        FileDataSource trainDataSource = new FileDataSource(context, trainDatasetFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for training data and labels */
        NumericTable trainData = new HomogenNumericTable(context, Double.class, nFeatures, 0, NumericTable.AllocationFlag.NotAllocate);
        NumericTable trainDependentVariables = new HomogenNumericTable(context, Double.class, nDependentVariables, 0,
                                                                       NumericTable.AllocationFlag.NotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(trainData);
        mergedData.addNumericTable(trainDependentVariables);

        TrainingOnline linearRegressionTraining = new TrainingOnline(context, Double.class, TrainingMethod.qrDense);

        linearRegressionTraining.input.set(TrainingInputId.data, trainData);
        linearRegressionTraining.input.set(TrainingInputId.dependentVariable, trainDependentVariables);

        while (trainDataSource.loadDataBlock(nTrainVectorsInBlock, mergedData) == nTrainVectorsInBlock) {
            linearRegressionTraining.compute();
        }

        TrainingResult trainingResult = linearRegressionTraining.finalizeCompute();
        model = trainingResult.get(TrainingResultId.model);
    }

    private static void testModel() {
        /* Initialize FileDataSource to retrieve the input data from a .csv file */
        FileDataSource testDataSource = new FileDataSource(context, testDatasetFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for testing data and labels */
        NumericTable testData = new HomogenNumericTable(context, Double.class, nFeatures, 0, NumericTable.AllocationFlag.NotAllocate);
        testDependentVariables = new HomogenNumericTable(context, Double.class, nDependentVariables, 0, NumericTable.AllocationFlag.NotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(testData);
        mergedData.addNumericTable(testDependentVariables);

        /* Retrieve the data from an input file */
        testDataSource.loadDataBlock(mergedData);

        /* Create algorithm objects to predict values of multiple linear regression with the default method */
        PredictionBatch linearRegressionPredict = new PredictionBatch(context, Double.class,
                PredictionMethod.defaultDense);

        linearRegressionPredict.input.set(PredictionInputId.data, testData);
        linearRegressionPredict.input.set(PredictionInputId.model, model);

        /* Compute the prediction results */
        PredictionResult predictionResult = linearRegressionPredict.compute();

        results = predictionResult.get(PredictionResultId.prediction);
    }

    private static void printResults() {
        NumericTable beta = model.getBeta();
        NumericTable expected = testDependentVariables;
        Service.printNumericTable("Coefficients: ", beta);
        Service.printNumericTable("First 10 rows of results (obtained): ", results, 10);
        Service.printNumericTable("First 10 rows of results (expected): ", expected, 10);
    }
}
