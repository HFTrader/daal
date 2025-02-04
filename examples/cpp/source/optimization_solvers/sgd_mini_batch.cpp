/* file: sgd_mini_batch.cpp */
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
!    C++ example of the Stochastic gradient descent algorithm
!******************************************************************************/

/**
 * <a name="DAAL-EXAMPLE-CPP-SGD_MINI_BATCH"></a>
 * \example sgd_mini_batch.cpp
 */

#include "daal.h"
#include "service.h"

using namespace std;
using namespace daal;
using namespace daal::algorithms;
using namespace daal::data_management;

string datasetFileName = "../data/batch/mse.csv";

const size_t nIterations = 1000;
const size_t nFeatures = 3;

const size_t batchSize = 5;
const double learningRate = 0.5;
const double accuracyThreshold = 0.0000001;

double startPoint[nFeatures + 1] = {8, 2, 1, 4};

int main(int argc, char *argv[])
{
    /* Initialize FileDataSource<CSVFeatureManager> to retrieve the input data from a .csv file */
    FileDataSource<CSVFeatureManager> dataSource(datasetFileName,
            DataSource::notAllocateNumericTable,
            DataSource::doDictionaryFromContext);

    /* Create Numeric Tables for data and values for dependent variable */
    services::SharedPtr<NumericTable> data(new HomogenNumericTable<double>(nFeatures, 0, NumericTable::notAllocate));
    services::SharedPtr<NumericTable> dependentVariables(new HomogenNumericTable<double>(1, 0, NumericTable::notAllocate));
    services::SharedPtr<NumericTable> mergedData(new MergedNumericTable(data, dependentVariables));

    /* Retrieve the data from the input file */
    dataSource.loadDataBlock(mergedData.get());

    size_t nVectors = data->getNumberOfRows();

    services::SharedPtr<optimization_solver::mse::Batch<double> > mseObjectiveFunction(new optimization_solver::mse::Batch<double>(nVectors));
    mseObjectiveFunction->input.set(optimization_solver::mse::data, data);
    mseObjectiveFunction->input.set(optimization_solver::mse::dependentVariables, dependentVariables);

    /* Create objects to compute the Stochastic gradient descent result using the mini-batch method */
    optimization_solver::sgd::Batch<double, optimization_solver::sgd::miniBatch> sgdMiniBatchAlgorithm(mseObjectiveFunction);

    /* Set input objects for the the Stochastic gradient descent algorithm */
    sgdMiniBatchAlgorithm.input.set(optimization_solver::sgd::inputArgument,
                                    services::SharedPtr<NumericTable>(new HomogenNumericTable<double>(startPoint, nFeatures + 1, 1)));
    sgdMiniBatchAlgorithm.parameter.learningRateSequence =
        services::SharedPtr<NumericTable>(new HomogenNumericTable<double>(1, 1, NumericTable::doAllocate, learningRate));
    sgdMiniBatchAlgorithm.parameter.nIterations = nIterations;
    sgdMiniBatchAlgorithm.parameter.batchSize = batchSize;
    sgdMiniBatchAlgorithm.parameter.accuracyThreshold = accuracyThreshold;

    /* Compute the Stochastic gradient descent result */
    sgdMiniBatchAlgorithm.compute();

    /* Print computed the Stochastic gradient descent result */
    printNumericTable(sgdMiniBatchAlgorithm.getResult()->get(optimization_solver::sgd::minimum), "Minimum");
    printNumericTable(sgdMiniBatchAlgorithm.getResult()->get(optimization_solver::sgd::nIterations), "Number of iterations performed:");

    return 0;
}
