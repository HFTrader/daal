/* file: implicit_als_training_batch.h */
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
//  Implementation of the interface for the implicit ALS training algorithm
//--
*/

#ifndef __IMPLICIT_ALS_TRAINING_BATCH_H__
#define __IMPLICIT_ALS_TRAINING_BATCH_H__

#include "algorithms/algorithm.h"
#include "algorithms/implicit_als/implicit_als_training_types.h"

namespace daal
{
namespace algorithms
{
namespace implicit_als
{
namespace training
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__IMPICIT_ALS__TRAINING__BATCHCONTAINER"></a>
 * \brief Provides methods to run implementations of the implicit ALS training algorithm
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public TrainingContainerIface<batch>
{
public:
    /** \brief Constructor */
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();

    void compute();
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__IMPLICIT_ALS__TRAINING__BATCH"></a>
 * \brief Algorithm class for training the implicit ALS model
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for implicit ALS model training, double or float
 * \tparam method           Implicit ALS training method, \ref Method
 *
 * \par Enumerations
 *      - \ref Method                Implicit ALS training method
 *      - \ref NumericTableInputId   Identifiers of input numeric table objects for the implicit ALS training algorithm
 *      - \ref ResultId              Identifiers of the results of the implicit ALS training algorithm
 *
 * \par References
 *      - \ref implicit_als::interface1::Parameter "implicit_als::Parameter" class
 *      - \ref Input class
 *      - \ref Result class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public daal::algorithms::Training<batch>
{
public:
    Input input;         /*!< %Input data structure */
    Parameter parameter; /*!< %Algorithm parameter */

    /** Default constructor */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs an implicit ALS training algorithm by copying input objects and parameters
     * of another implicit ALS training algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other)
    {
        initialize();
        input.set(data,       other.input.get(data));
        input.set(inputModel, other.input.get(inputModel));
        parameter = other.parameter;
    }

    /**
    * Returns the method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains the results of the implicit ALS training algorithm
     * \return Structure that contains the results of the implicit ALS training algorithm
     */
    services::SharedPtr<Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store the results of the implicit ALS training algorithm
     * \param[in] res  Structure to store the results of the implicit ALS training algorithm
     */
    void setResult(services::SharedPtr<Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated implicit ALS training algorithm with a copy of input objects
     * of this implicit ALS training algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

protected:
    services::SharedPtr<training::Result> _result;

    virtual Batch<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    virtual void allocateResult()
    {
        _result->allocate<algorithmFPType>(&input, &parameter, (int) method);
         _res = _result.get();
    }

    void initialize()
    {
        _ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in = &input;
        _par = &parameter;
        _result = services::SharedPtr<training::Result>(new Result());
    }
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

}
}
}
}

#endif
