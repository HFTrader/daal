/* file: pivoted_qr_batch.cpp */
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
!    C++ example of computing pivoted QR decomposition
!******************************************************************************/

/**
 * <a name="DAAL-EXAMPLE-CPP-PIVOTED_QR_BATCH"></a>
 * \example pivoted_qr_batch.cpp
 */

#include "daal.h"
#include "service.h"

using namespace std;
using namespace daal;
using namespace daal::algorithms;

/* Input data set parameters */
const string datasetFileName = "../data/batch/qr.csv";

int main(int argc, char *argv[])
{
    checkArguments(argc, argv, 1, &datasetFileName);

    /* Initialize FileDataSource<CSVFeatureManager> to retrieve the input data from a .csv file */
    FileDataSource<CSVFeatureManager> dataSource(datasetFileName, DataSource::doAllocateNumericTable, DataSource::doDictionaryFromContext);

    /* Retrieve the data from the input file */
    dataSource.loadDataBlock();

    /* Create an algorithm to compute pivoted QR decomposition */
    pivoted_qr::Batch<> algorithm;

    algorithm.input.set(pivoted_qr::data, dataSource.getNumericTable());

    /* Compute pivoted QR decomposition */
    algorithm.compute();

    services::SharedPtr<pivoted_qr::Result> res = algorithm.getResult();

    /* Print the results */
    printNumericTable(res->get(pivoted_qr::matrixQ), "Orthogonal matrix Q:", 10);
    printNumericTable(res->get(pivoted_qr::matrixR), "Triangular matrix R:");
    printNumericTable(res->get(pivoted_qr::permutationMatrix), "Permutation matrix P:");

    return 0;
}
