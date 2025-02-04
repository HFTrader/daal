/* file: objective_function_batch.h */
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
//  Implementation of the Objective function types.
//--
*/

#ifndef __OBJECTIVE_FUNCTION_BATCH_H__
#define __OBJECTIVE_FUNCTION_BATCH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "objective_function_types.h"

namespace daal
{
namespace algorithms
{
namespace optimization_solver
{
namespace objective_function
{

namespace interface1
{

/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__OBJECTIVE_FUNCTION__BATCH"></a>
 * \brief Interface for computing the Objective function in the batch processing mode.
 *
 * \par Enumerations
 *      - InputId  Identifiers of input objects for the Objective function
 *      - ResultId Result identifiers for the Objective function
 *
 * \par References
 *      - Input class
 *      - Result class
 */
class DAAL_EXPORT Batch : public daal::algorithms::Analysis<batch>
{
public:
    /**
     *  Main constructor
     */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs an Objective function by copying input objects and parameters
     * of another Objective function
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch &other)
    {
        initialize();
    }

    /** Destructor */
    virtual ~Batch() {}

    /**
    * Returns the structure that contains results of the Objective function
    * \return Structure that contains results of the Objective function
    */
    virtual services::SharedPtr<objective_function::Result> getResult()
    {
        return _result;
    }

    /**
     * Sets the memory for storing results of the Objective function
     * \param[in] result  Structure for storing results of the Objective function
     */
    virtual void setResult(services::SharedPtr<objective_function::Result> result)
    {
        _result = result;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated Objective function algorithm with a copy of input objects
     * of this Objective function algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch> clone() const
    {
        return services::SharedPtr<Batch>(cloneImpl());
    }

protected:
    virtual Batch *cloneImpl() const DAAL_C11_OVERRIDE = 0;

    void initialize()
    {
        _result = services::SharedPtr<objective_function::Result>(new objective_function::Result());
    }

protected:
    services::SharedPtr<objective_function::Result> _result;
};
} // namespace interface1
using interface1::Batch;

} // namespace objective_function
} // namespace optimization_solver
} // namespace algorithm
} // namespace daal
#endif
