/* file: java_online.h */
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
//  Implementation of the class that connects Covariance Java Online
//  to C++ algorithm
//--
*/
#ifndef __JAVA_ONLINE_H__
#define __JAVA_ONLINE_H__

#include <jni.h>

#include "algorithms/covariance/covariance_types.h"
#include "algorithms/covariance/covariance_online.h"
#include "java_callback.h"
#include "java_online_container.h"

namespace daal
{
namespace algorithms
{
namespace covariance
{

using namespace daal::data_management;
using namespace daal::services;

/*
 * \brief Class that specifies the default method for partial results initialization
 */
class JavaOnline : public OnlineIface
{
public:
    /** Default constructor */
    JavaOnline(JavaVM *_jvm, jobject _javaObject)
    {
        JavaOnlineContainer* _container = new JavaOnlineContainer(_jvm, _javaObject);
        _container->setJavaResult(_result);
        _container->setJavaPartialResult(_partialResult);

        _container->setEnvironment(&_env);

        this->_ac = _container;
    };

    virtual ~JavaOnline() {}

    virtual int getMethod() const DAAL_C11_OVERRIDE { return 0; } // To make the class non-abstract

    virtual void setResult(const services::SharedPtr<Result> &result)
    {
        _result = result;
        (static_cast<JavaOnlineContainer*>(this->_ac))->setJavaResult(_result);
        _res = _result.get();
    }

    virtual void setPartialResult(const services::SharedPtr<PartialResult> &partialResult, bool _initFlag = false)
    {
        _partialResult = partialResult;
        (static_cast<JavaOnlineContainer*>(this->_ac))->setJavaPartialResult(_partialResult);
        _pres = _partialResult.get();
        setInitFlag(_initFlag);
    }

protected:
    virtual JavaOnline * cloneImpl() const DAAL_C11_OVERRIDE { return NULL; }

    virtual void allocateResult() DAAL_C11_OVERRIDE
    {
        _result->allocate<double>(_partialResult.get(), _par, 0);
        _res    = _result.get();
        _pres   = _partialResult.get();
    }

    virtual void allocatePartialResult() DAAL_C11_OVERRIDE
    {
        _partialResult->allocate<double>(&input, _par, 0);
        _pres   = _partialResult.get();
    }
};

} // namespace daal::algorithms::covariance
} // namespace daal::algorithms
} // namespace daal

#endif
