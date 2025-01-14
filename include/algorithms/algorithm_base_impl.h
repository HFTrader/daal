/* file: algorithm_base_impl.h */
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
//  Implementation of base classes defining algorithm interface.
//--
*/

#ifndef __ALGORITHM_BASE_IMPL_H__
#define __ALGORITHM_BASE_IMPL_H__

namespace daal
{
namespace algorithms
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__ALGORITHMIMPL"></a>
 * \brief Provides implementations of the compute and finalizeCompute methods of the Algorithm class.
 *        The methods of the class support different computation modes: batch, distributed and online(see \ref ComputeMode)
 * \tparam mode Computation mode of the algorithm, \ref ComputeMode
 */
template<ComputeMode mode>
class AlgorithmImpl : public Algorithm<mode>
{
public:
    /** Deafult constructor */
    AlgorithmImpl() : Algorithm<mode>() {}

    virtual ~AlgorithmImpl() {}

    /**
     * Computes final results of the algorithm in the %batch mode,
     * or partial results of the algorithm in %online and %distributed modes.
     */
    void compute()
    {
        this->setParameter();

        this->_in->setErrorCollection(this->_errors);
        if(this->_par)
        {
            this->_par->setErrorCollection(this->_errors);
        }

        this->allocateInputMemory();
        if(this->_errors->size() != 0)
        {
            return;
        }

#if defined(DAAL_CHECK_PARAMETER)
        this->checkComputeParams();
        if(this->_errors->size() != 0)
        {
            return;
        }
#endif

        if(!this->allocatePartialResultMemory())
        {
            this->_errors->add(services::ErrorMemoryAllocationFailed);
            return;
        }

        if(!this->getInitFlag())
        {
            this->initPartialResult();
            this->setInitFlag(true);
        }

        this->_ac->setArguments(this->_in,  this->_pres, this->_par);
        this->_ac->setErrorCollection(this->_errors);
        this->_pres->setErrorCollection(this->_errors);

#if defined(DAAL_CHECK_PARAMETER)
        this->checkResult();
        if(this->_errors->size() != 0)
        {
            return;
        }
#endif

        this->_ac->compute();

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

    /**
     * Computes final results of the algorithm using partial results in %online and %distributed modes.
     */
    void finalizeCompute()
    {

#if defined(DAAL_CHECK_PARAMETER)
        this->checkPartialResult();
        if(this->_errors->size() != 0)
        {
            return;
        }
#endif

        this->allocateResultMemory();
        if(this->_errors->size() != 0)
        {
            this->_errors->add(services::ErrorMemoryAllocationFailed);
            return;
        }

        this->_ac->setPartialResult(this->_pres);
        this->_ac->setResult(this->_res);
        this->_ac->setErrorCollection(this->_errors);

        if(this->_res)
        {
            this->_res->setErrorCollection(this->_errors);
        }

#if defined(DAAL_CHECK_PARAMETER)
        this->checkFinalizeComputeParams();
        if(this->_errors->size() != 0)
        {
            return;
        }
#endif

        this->_ac->finalizeCompute();

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

    /**
     * Validates parameters of the compute method
     */
    virtual void checkComputeParams() DAAL_C11_OVERRIDE
    {
        if (this->_par)
        {
            this->_par->check();
        }

        this->_in->check(this->_par, this->getMethod());

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

    /**
     * Validates result parameters of the compute method
     */
    virtual void checkResult() DAAL_C11_OVERRIDE
    {
        if (this->_pres)
        {
            this->_pres->check(this->_in, this->_par, this->getMethod());
        }
        else
        {
            this->_errors->add(services::ErrorNullPartialResult);
        }

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

    /**
     * Validates result parameters of the finalizeCompute method
     */
    virtual void checkPartialResult() DAAL_C11_OVERRIDE
    {
        if(this->_pres)
        {
            this->_pres->check(this->_par, this->getMethod());
        }
        else
        {
            this->_errors->add(services::ErrorNullPartialResult);
        }

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

    /**
     * Validates parameters of the finalizeCompute method
     */
    virtual void checkFinalizeComputeParams() DAAL_C11_OVERRIDE
    {
        if(this->_res)
        {
            this->_res->check(this->_pres, this->_par, this->getMethod());
        }

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__ALGORITHMIMPL"></a>
 * \brief Provides implementations of the compute and checkComputeParams methods of the Algorithm<batch> class
 */
template<>
class AlgorithmImpl<batch> : public Algorithm<batch>
{
public:
    /** Deafult constructor */
    AlgorithmImpl() : Algorithm<batch>() {}

    virtual ~AlgorithmImpl() {}

    /**
    * Returns method of the algorithm
    * \return Method of the algorithm
    */
    virtual int getMethod() const = 0;

    /**
     * Computes final results of the algorithm in the %batch mode.
     */
    void compute()
    {
        this->setParameter();

        this->_in->setErrorCollection(this->_errors);

        if(this->_par)
        {
            this->_par->setErrorCollection(this->_errors);
        }

#if defined(DAAL_CHECK_PARAMETER)
        this->checkComputeParams();
        if(this->_errors->size() != 0)
        {
            return;
        }
#endif

        this->allocateInputMemory();
        if(this->_errors->size() != 0)
        {
            return;
        }

        this->allocateResultMemory();
        if(this->_errors->size() != 0)
        {
            this->_errors->add(services::ErrorMemoryAllocationFailed);
            return;
        }

        this->_ac->setArguments(this->_in, this->_res, this->_par);
        this->_ac->setErrorCollection(this->_errors);

        this->_res->setErrorCollection(this->_errors);

#if defined(DAAL_CHECK_PARAMETER)
        this->checkResult();
        if(this->_errors->size() != 0)
        {
            return;
        }
#endif

        this->_ac->compute();

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }

        _res = this->_ac->getResult();
    }

    /**
     * Validates parameters of the compute method
     */
    virtual void checkComputeParams() DAAL_C11_OVERRIDE
    {
        if (_par)
        {
            _par->check();

            if(this->_errors->size() != 0)
            {
                this->throwIfPossible();
                return;
            }
        }

        _in->check(_par, getMethod());

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

    /**
     * Validates result parameters of the compute method
     */
    virtual void checkResult() DAAL_C11_OVERRIDE
    {
        if(_res)
        {
            _res->check(_in, _par, getMethod());
        }
        else
        {
            _errors->add(services::ErrorNullResult);
        }

        if(this->_errors->size() != 0)
        {
            this->throwIfPossible();
            return;
        }
    }

protected:
};
} // namespace interface1
using interface1::AlgorithmImpl;

}
}
#endif
