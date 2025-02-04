/* file: linear_regression_qr_online.cpp */
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
!  Content:
!    C++ example of multiple linear regression in the online processing mode.
!
!    The program trains the multiple linear regression model on a training
!    datasetFileName with a QR decomposition-based method and computes
!    regression for the test data.
!******************************************************************************/

/**
 * <a name="DAAL-EXAMPLE-CPP-LINEAR_REGRESSION_QR_ONLINE"></a>
 * \example linear_regression_qr_online.cpp
 */

#include "daal.h"
#include "service.h"

using namespace std;
using namespace daal;
using namespace daal::algorithms::linear_regression;

/* Input data set parameters */
string trainDatasetFileName            = "../data/online/linear_regression_train.csv";
string testDatasetFileName             = "../data/online/linear_regression_test.csv";

const size_t nTrainVectorsInBlock = 250;

const size_t nFeatures           = 10;
const size_t nDependentVariables = 2;

void trainModel();
void testModel();

services::SharedPtr<training::Result> trainingResult;
services::SharedPtr<prediction::Result> predictionResult;

int main(int argc, char *argv[])
{
    checkArguments(argc, argv, 2, &trainDatasetFileName, &testDatasetFileName);

    trainModel();
    testModel();

    return 0;
}

void trainModel()
{
    /* Initialize FileDataSource<CSVFeatureManager> to retrieve the input data from a .csv file */
    FileDataSource<CSVFeatureManager> trainDataSource(trainDatasetFileName,
                                                      DataSource::notAllocateNumericTable,
                                                      DataSource::doDictionaryFromContext);

    /* Create Numeric Tables for training data and dependent variables */
    services::SharedPtr<NumericTable> trainData(new HomogenNumericTable<double>(nFeatures, 0, NumericTable::notAllocate));
    services::SharedPtr<NumericTable> trainDependentVariables(new HomogenNumericTable<double>(nDependentVariables, 0, NumericTable::notAllocate));
    services::SharedPtr<NumericTable> mergedData(new MergedNumericTable(trainData, trainDependentVariables));

    /* Create an algorithm object to train the multiple linear regression model */
    training::Online<double, training::qrDense> algorithm;

    while(trainDataSource.loadDataBlock(nTrainVectorsInBlock, mergedData.get()) == nTrainVectorsInBlock)
    {
        /* Pass a training data set and dependent values to the algorithm */
        algorithm.input.set(training::data, trainData);
        algorithm.input.set(training::dependentVariables, trainDependentVariables);

        /* Update the multiple linear regression model */
        algorithm.compute();
    }

    /* Finalize the multiple linear regression model */
    algorithm.finalizeCompute();

    /* Retrieve the algorithm results */
    trainingResult = algorithm.getResult();
    printNumericTable(trainingResult->get(training::model)->getBeta(), "Linear Regression coefficients:");
}

void testModel()
{
    /* Initialize FileDataSource<CSVFeatureManager> to retrieve the input data from a .csv file */
    FileDataSource<CSVFeatureManager> testDataSource(testDatasetFileName,
                                                     DataSource::doAllocateNumericTable,
                                                     DataSource::doDictionaryFromContext);

    /* Create Numeric Tables for testing data and ground truth values */
    services::SharedPtr<NumericTable> testData(new HomogenNumericTable<double>(nFeatures, 0, NumericTable::notAllocate));
    services::SharedPtr<NumericTable> testGroundTruth(new HomogenNumericTable<double>(nDependentVariables, 0, NumericTable::notAllocate));
    services::SharedPtr<NumericTable> mergedData(new MergedNumericTable(testData, testGroundTruth));

    /* Retrieve the data from the input file */
    testDataSource.loadDataBlock(mergedData.get());

    /* Create an algorithm object to predict values of multiple linear regression */
    prediction::Batch<> algorithm;

    /* Pass a testing data set and the trained model to the algorithm */
    algorithm.input.set(prediction::model, trainingResult->get(training::model));
    algorithm.input.set(prediction::data, testData);

    /* Predict values of multiple linear regression */
    algorithm.compute();

    /* Retrieve the algorithm results */
    predictionResult = algorithm.getResult();
    printNumericTable(predictionResult->get(prediction::prediction),
        "Linear Regression prediction results: (first 10 rows):", 10);
    printNumericTable(testGroundTruth, "Ground truth (first 10 rows):", 10);
}
