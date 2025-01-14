/* file: sum_of_functions_batch.h */
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
//++
//  Implementation of the Sum of functions types.
//--
*/

#ifndef __SUM_OF_FUNCTIONS_BATCH_H__
#define __SUM_OF_FUNCTIONS_BATCH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "objective_function_batch.h"
#include "sum_of_functions_types.h"

namespace daal
{
namespace algorithms
{
namespace optimization_solver
{
namespace sum_of_functions
{

namespace interface1
{

/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__SUM_OF_FUNCTIONS__BATCH"></a>
 * \brief Interface for computing the Sum of functions in the batch processing mode.
 *
 * \par Enumerations
 *      - Method Computation methods for the Sum of functions
 *      - InputId  Identifiers of input objects for the Sum of functions
 *      - ResultId Result identifiers for the Sum of functions
 *
 * \par References
 *      - <a href="DAAL-REF-SUM_OF_FUNCTIONS-ALGORITHM">the Sum of functions description and usage models</a>
 *      - Input class
 *      - Result class
 */
class DAAL_EXPORT Batch : public objective_function::Batch
{
public:
    /**
     *  Main constructor
     */
    Batch(size_t numberOfTerms, sum_of_functions::Input *sumOfFunctionsInput, sum_of_functions::Parameter *sumOfFunctionsParameter) :
        sumOfFunctionsInput(sumOfFunctionsInput),
        sumOfFunctionsParameter(sumOfFunctionsParameter)
    {
        initialize();
        if(sumOfFunctionsParameter != NULL) {sumOfFunctionsParameter->numberOfTerms = numberOfTerms;}
    }

    /**
     * Constructs the Sum of functions by copying input objects and parameters
     * of another the Sum of functions
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch &other)
    {
        sumOfFunctionsInput = other.sumOfFunctionsInput;
        sumOfFunctionsParameter = other.sumOfFunctionsParameter;
        initialize();
    }

    virtual ~Batch() {}

    /**
     * Returns a pointer to the newly allocated Sum of functions with a copy of input objects
     * of this Sum of functions
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch> clone() const
    {
        return services::SharedPtr<Batch>(cloneImpl());
    }

    sum_of_functions::Parameter *sumOfFunctionsParameter; /*!< Pointer to the parameter to use one object in inherited class */
    sum_of_functions::Input *sumOfFunctionsInput;         /*!< Pointer to the input to use one object in inherited class */

protected:
    virtual Batch *cloneImpl() const DAAL_C11_OVERRIDE = 0;

    void initialize()
    {}
};
} // namespace interface1
using interface1::Batch;

} // namespace sum_of_functions
} // namespace optimization_solver
} // namespace algorithm
} // namespace daal
#endif
