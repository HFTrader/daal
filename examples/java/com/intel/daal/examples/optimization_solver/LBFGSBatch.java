/* file: LBFGSBatch.java */
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
 //     Java example of dense LBFGS algorithm in the batch
 //     processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-LBFGSBATCH">
 * @example LBFGSBatch.java
 */

package com.intel.daal.examples.optimization_solver;

import com.intel.daal.algorithms.optimization_solver.lbfgs.*;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.MergedNumericTable;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

class LBFGSBatch {
    private static final long   nFeatures   = 10;
    private static final long   nIterations = 1000;
    private static final double stepLength = 1.0e-4;

    private static double[] startArgument    = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    private static double[] expectedArgument = { 11,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10};

    private static final String datasetFileName = "../data/batch/lbfgs.csv";

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        /* Initialize FileDataSource to retrieve the input data from a .csv file */
        FileDataSource dataSource = new FileDataSource(context, datasetFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for input data and dependent variables */
        NumericTable data = new HomogenNumericTable(context, Double.class, nFeatures, 0, NumericTable.AllocationFlag.NotAllocate);
        NumericTable dependentVariables = new HomogenNumericTable(context, Double.class, 1, 0,
                                                                  NumericTable.AllocationFlag.NotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(data);
        mergedData.addNumericTable(dependentVariables);

        /* Retrieve the data from input file */
        dataSource.loadDataBlock(mergedData);

        /* Create an MSE objective function for LBFGS */
        com.intel.daal.algorithms.optimization_solver.mse.Batch mseObjectiveFunction =
            new com.intel.daal.algorithms.optimization_solver.mse.Batch(context, Double.class,
                    com.intel.daal.algorithms.optimization_solver.mse.Method.defaultDense, data.getNumberOfRows());

        mseObjectiveFunction.getInput().set(com.intel.daal.algorithms.optimization_solver.mse.InputId.data, data);
        mseObjectiveFunction.getInput().set(com.intel.daal.algorithms.optimization_solver.mse.InputId.dependentVariables,
                                            dependentVariables);

        /* Create objects to compute LBFGS result using the default method */
        Batch algorithm = new Batch(context, Double.class, Method.defaultDense);
        algorithm.parameter.setFunction(mseObjectiveFunction);
        algorithm.parameter.setNIterations(nIterations);
        algorithm.parameter.setStepLengthSequence(
            new HomogenNumericTable(context, Double.class, 1, 1, NumericTable.AllocationFlag.DoAllocate, stepLength));
        algorithm.getInput().set(InputId.inputArgument, new HomogenNumericTable(context, startArgument, nFeatures + 1, 1));

        /* Compute LBFGS result */
        Result result = algorithm.compute();

        NumericTable expected = new HomogenNumericTable(context, expectedArgument, nFeatures + 1, 1);
        Service.printNumericTable("Expected coefficients:",          expected);
        Service.printNumericTable("Resulting coefficients:",         result.get(ResultId.minimum));
        Service.printNumericTable("Number of iterations performed:", result.get(ResultId.nIterations));
    }
}
