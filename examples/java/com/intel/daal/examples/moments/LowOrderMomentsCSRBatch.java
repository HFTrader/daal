/* file: LowOrderMomentsCSRBatch.java */
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
//  Java example of computing low order moments in the batch processing mode.
//
//      Input matrix is stored in the compressed sparse row (CSR) format with
//      one-based indexing.
////////////////////////////////////////////////////////////////////////////////
*/

/**
 * <a name="DAAL-EXAMPLE-JAVA-LOWORDERMOMENTSCSRBATCH">
 * @example LowOrderMomentsCSRBatch.java
 */

package com.intel.daal.examples.moments;

import com.intel.daal.algorithms.low_order_moments.*;
import com.intel.daal.data_management.data.CSRNumericTable;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.examples.utils.Service;
/*
// Input data set is stored in the compressed sparse row format
*/
import com.intel.daal.services.DaalContext;

class LowOrderMomentsCSRBatch {

    /* Input data set parameters */
    private static final String datasetFileName = "../data/batch/covcormoments_csr.csv";

    private static CSRNumericTable dataTable;
    private static Result          result;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Read the input data from a file */
        dataTable = Service.createSparseTable(context, datasetFileName);

        /* Create algorithm objects to compute low order moments using the default method */
        Batch algorithm = new Batch(context, Double.class, Method.fastCSR);

        /* Set input objects for the algorithm */
        algorithm.input.set(InputId.data, dataTable);

        /* Compute low order moments */
        result = algorithm.compute();

        printResults();

        context.dispose();
    }

    private static void printResults() {
        HomogenNumericTable minimum = (HomogenNumericTable) result.get(ResultId.minimum);
        HomogenNumericTable maximum = (HomogenNumericTable) result.get(ResultId.maximum);
        HomogenNumericTable sum = (HomogenNumericTable) result.get(ResultId.sum);
        HomogenNumericTable sumSquares = (HomogenNumericTable) result.get(ResultId.sumSquares);
        HomogenNumericTable sumSquaresCentered = (HomogenNumericTable) result.get(ResultId.sumSquaresCentered);
        HomogenNumericTable mean = (HomogenNumericTable) result.get(ResultId.mean);
        HomogenNumericTable secondOrderRawMoment = (HomogenNumericTable) result.get(ResultId.secondOrderRawMoment);
        HomogenNumericTable variance = (HomogenNumericTable) result.get(ResultId.variance);
        HomogenNumericTable standardDeviation = (HomogenNumericTable) result.get(ResultId.standardDeviation);
        HomogenNumericTable variation = (HomogenNumericTable) result.get(ResultId.variation);

        System.out.println("Low order moments:");
        Service.printNumericTable("Min:", minimum);
        Service.printNumericTable("Max:", maximum);
        Service.printNumericTable("Sum:", sum);
        Service.printNumericTable("SumSquares:", sumSquares);
        Service.printNumericTable("SumSquaredDiffFromMean:", sumSquaresCentered);
        Service.printNumericTable("Mean:", mean);
        Service.printNumericTable("SecondOrderRawMoment:", secondOrderRawMoment);
        Service.printNumericTable("Variance:", variance);
        Service.printNumericTable("StandartDeviation:", standardDeviation);
        Service.printNumericTable("Variation:", variation);
    }
}
