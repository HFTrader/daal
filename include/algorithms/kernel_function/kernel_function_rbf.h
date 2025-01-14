/* file: kernel_function_rbf.h */
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
//  Implementation of the radial basis function (RBF) kernel interface.
//--
*/

#ifndef __KERNEL_FUNCTION_RBF_H__
#define __KERNEL_FUNCTION_RBF_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "algorithms/kernel_function/kernel_function_types_rbf.h"
#include "algorithms/kernel_function/kernel_function.h"

namespace daal
{
namespace algorithms
{
namespace kernel_function
{
namespace rbf
{

namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__KERNEL_FUNCTION__RBF__BATCHCONTAINER"></a>
 * \brief Provides methods to run implementations of the radial basis function (RBF) kernel algorithm.
 *        This class is associated with the Batch class
 *        and supports the method for computing RBF kernel functions in the batch processing mode
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of kernel functions, double or float
 * \tparam method           Computation method of the algorithm, \ref Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    BatchContainer(daal::services::Environment::env *daalEnv);
    ~BatchContainer();
    /**
     * Runs implementations of the RBF kernel function algorithm in the %batch processing mode
     */
    virtual void compute();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__KERNEL_FUNCTION__RBF__BATCH"></a>
 * \brief Computes the RBF kernel function in the batch processing mode.
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations of kernel functions, double or float
 * \tparam method           Computation method of the algorithm, \ref Method
 *
 * \par Enumerations
 *      - \ref Method   Methods for computing  kernel functions
 *      - \ref InputId  Identifiers of input objects for the kernel function algorithm
 *      - \ref ResultId Identifiers of results of the kernel function algorithm
 *
 * \par References
 *      - <a href="DAAL-REF-KERNEL_FUNCTION_RBF-ALGORITHM">Kernel function algorithm description and usage models</a>
 *      - \ref interface1::Input "Input" class
 *      - \ref interface1::Result "Result" class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public KernelIface
{
public:
    /** Default constructor */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs RBF kernel function algorithm by copying input objects and parameters
     * of another RBF kernel function algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other) : KernelIface(other)
    {
        initialize();
        parameter = other.parameter;
    }

    /**
    * Returns the method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains computed results of the kernel function algorithm
     * \returns the Structure that contains computed results of the kernel function algorithm
     */
    virtual services::SharedPtr<kernel_function::Result> getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store the results of the kernel function algorithm
     * \param[in] res  Structure to store the results
     */
    void setResult(services::SharedPtr<kernel_function::Result> res)
    {
        _result = res;
        _res = _result.get();
    }

    /**
     * Returns a pointer to the newly allocated RBF kernel function algorithm with a copy of input objects
     * and parameters of this RBF kernel function algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

protected:
    void initialize()
    {
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in = &input;
        _par = &parameter;
        parameterBase = &parameter;
    }
    virtual Batch<algorithmFPType, method> * cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    virtual void allocateResult()
    {
        _result->allocate<algorithmFPType>(&input, &parameter, (int) method);
        _res = _result.get();
    }

public:
    Parameter parameter;  /*!< Parameter of the kernel function*/
};
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // rbf
} // namespace kernel_function
} // namespace algorithm
} // namespace daal
#endif
