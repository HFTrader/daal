/* file: KMeansDenseDistributed.java */
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
 //     Java example of dense K-Means clustering in the distributed processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-KMEANSDENSEDISTRIBUTED">
 * @example KMeansDenseDistributed.java
 */

package com.intel.daal.examples.kmeans;

import com.intel.daal.algorithms.kmeans.*;
import com.intel.daal.algorithms.kmeans.init.*;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

class KMeansDenseDistributed {
    /* Input data set parameters */
    private static final String[] datasetFileNames = {
        "../data/distributed/kmeans_dense_1.csv", "../data/distributed/kmeans_dense_2.csv",
        "../data/distributed/kmeans_dense_3.csv", "../data/distributed/kmeans_dense_4.csv"};

    private static final int    nClusters       = 20;
    private static final int    nBlocks         = 4;
    private static final int    nIterations     = 5;
    private static final int    nVectorsInBlock = 2500;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        /* Get initial centroids */
        InitDistributedStep2Master initMaster = new InitDistributedStep2Master(context, Double.class,
                InitMethod.randomDense, nClusters);

        for (int node = 0; node < nBlocks; node++) {
            /* Initialize FileDataSource<CSVFeatureManager> to retrieve the input data from a .csv file */
            FileDataSource dataSource = new FileDataSource(context, datasetFileNames[node],
                    DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                    DataSource.NumericTableAllocationFlag.DoAllocateNumericTable);

            /* Retrieve the input data */
            dataSource.loadDataBlock();

            NumericTable data = dataSource.getNumericTable();

            /* Create an algorithm object to initialize the K-Means algorithm */
            InitDistributedStep1Local initLocal = new InitDistributedStep1Local(context, Double.class,
                    InitMethod.randomDense, nClusters, nBlocks * nVectorsInBlock, node * nVectorsInBlock);

            /* Set the input data to the algorithm */
            initLocal.input.set(InitInputId.data, data);

            InitPartialResult initPres = initLocal.compute();
            initMaster.input.add(InitDistributedStep2MasterInputId.partialResults, initPres);
        }

        initMaster.compute();
        InitResult initResult = initMaster.finalizeCompute();

        NumericTable centroids = initResult.get(InitResultId.centroids);
        NumericTable[] assignments = new NumericTable[nBlocks];
        NumericTable goalFunction = null;

        /* Create an algorithm for K-Means clustering */
        DistributedStep2Master masterAlgorithm = new DistributedStep2Master(context, Double.class, Method.defaultDense,
                nClusters);

        for (int it = 0; it < nIterations + 1; it++) {
            for (int node = 0; node < nBlocks; node++) {
                /* Initialize FileDataSource<CSVFeatureManager> to retrieve the input data from a .csv file */
                FileDataSource dataSource = new FileDataSource(context, datasetFileNames[node],
                        DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                        DataSource.NumericTableAllocationFlag.DoAllocateNumericTable);

                /* Retrieve the input data */
                dataSource.loadDataBlock();

                NumericTable data = dataSource.getNumericTable();

                /* Create an algorithm object for the K-Means algorithm */
                DistributedStep1Local algorithm = new DistributedStep1Local(context, Double.class, Method.defaultDense,
                        nClusters);

                if (it == nIterations) {
                    algorithm.parameter.setAssignFlag(true);
                }

                /* Set the input data to the algorithm */
                algorithm.input.set(InputId.data, data);
                algorithm.input.set(InputId.inputCentroids, centroids);

                PartialResult pres = algorithm.compute();

                if (it == nIterations) {
                    Result result = algorithm.finalizeCompute();
                    assignments[node] = result.get(ResultId.assignments);
                } else {
                    masterAlgorithm.input.add(DistributedStep2MasterInputId.partialResults, pres);
                }
            }

            if (it == nIterations)
                break;

            masterAlgorithm.compute();
            Result result = masterAlgorithm.finalizeCompute();

            centroids = result.get(ResultId.centroids);
            goalFunction = result.get(ResultId.goalFunction);
        }

        /* Print the results */
        Service.printNumericTable("First 10 cluster assignments from 1st node:", assignments[0], 10);
        Service.printNumericTable("First 10 dimensions of centroids:", centroids, 20, 10);
        Service.printNumericTable("Goal function value:", goalFunction);

        context.dispose();
    }
}
