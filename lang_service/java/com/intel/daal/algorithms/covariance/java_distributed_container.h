/* file: java_distributed_container.h */
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
//  Implementation of the class that connects Covariance Java Distributed
//  to C++ algorithm
//--
*/
#ifndef __JAVA_ONLINE_CONTAINER_H__
#define __JAVA_ONLINE_CONTAINER_H__

#include <jni.h>

#include "algorithms/covariance/covariance_types.h"
#include "algorithms/covariance/covariance_distributed.h"
#include "java_callback.h"

namespace daal
{
namespace algorithms
{
namespace covariance
{

using namespace daal::data_management;
using namespace daal::services;

class JavaDistributedContainer : public DistributedContainerIface<step2Master>, public JavaCallback
{
public:
    JavaDistributedContainer(JavaVM *_jvm, jobject _javaObject) : JavaCallback(_jvm, _javaObject)
    {};
    virtual ~JavaDistributedContainer() {}

    /**
     * Runs the implementation of the correlation or variance-covariance matrix algorithm in the distributed processing mode
     */
    virtual void compute()
    {
        JavaCallback::ThreadLocalStorage tls = _tls.local();
        jint status = jvm->AttachCurrentThread((void **)(&tls.jniEnv), NULL);
        JNIEnv *env = tls.jniEnv;

        jclass javaObjectClass = env->GetObjectClass(javaObject);
        if(javaObjectClass == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jclass javaObjectClass could not be initialized"); return; }


        jmethodID getContextID = env->GetMethodID(javaObjectClass, "getContext", "()Lcom/intel/daal/services/DaalContext;");
        if(getContextID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID getContextID could not be initialized"); return; }

        jobject javaContextObject = env->CallObjectMethod(javaObject, getContextID);
        if(javaContextObject == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jobject javaContextObject could not be initialized"); return; }

        setInputToJava(env, javaObjectClass, javaObject);

        setPartialResultToJava(env, javaObjectClass, javaObject, javaContextObject);

        jmethodID computeMethodID = env->GetMethodID(javaObjectClass, "compute", "()Lcom/intel/daal/algorithms/covariance/PartialResult;");
        if(computeMethodID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID computeMethodID could not be initialized"); return; }

        env->CallObjectMethod(javaObject, computeMethodID);

        if(!tls.is_main_thread)
        {
            status = jvm->DetachCurrentThread();
        }

        _tls.local() = tls;
    }

    /**
    * Runs the implementation of the correlation or variance-covariance matrix algorithm in the distributed processing mode
    */
    virtual void finalizeCompute()
    {
        JavaCallback::ThreadLocalStorage tls = _tls.local();
        jint status = jvm->AttachCurrentThread((void **)(&tls.jniEnv), NULL);
        JNIEnv *env = tls.jniEnv;
        jclass javaObjectClass = env->GetObjectClass(javaObject);
        if(javaObjectClass == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jclass javaObjectClass could not be initialized"); return; }

        jmethodID getContextID = env->GetMethodID(javaObjectClass, "getContext", "()Lcom/intel/daal/services/DaalContext;");
        if(getContextID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID getContextID could not be initialized"); return; }

        jobject javaContextObject = env->CallObjectMethod(javaObject, getContextID);
        if(javaContextObject == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jobject javaContextObject could not be initialized"); return; }

        setPartialResultToJava(env, javaObjectClass, javaObject, javaContextObject);

        setResultToJava(env, javaObjectClass, javaObject, javaContextObject);

        jmethodID finalizeComputeMethodID = env->GetMethodID(javaObjectClass, "finalizeCompute", "()Lcom/intel/daal/algorithms/covariance/Result;");
        if(finalizeComputeMethodID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID finalizeComputeMethodID could not be initialized"); return; }

        env->CallObjectMethod(javaObject, finalizeComputeMethodID);

        if(!tls.is_main_thread)
        {
            status = jvm->DetachCurrentThread();
        }

        _tls.local() = tls;
    }

    SharedPtr<SerializationIface> *partialResultStorage;
    SharedPtr<SerializationIface> *resultStorage;

    void setJavaResult(services::SharedPtr<Result> result)
    {
        _result = result;
    };

    void setJavaPartialResult(services::SharedPtr<PartialResult> partialResult)
    {
        _partialResult = partialResult;
    };

protected:
    void setInputToJava(JNIEnv *env, jclass javaObjectClass, jobject javaObject)
    {
        const char *javaInputClassName = "Lcom/intel/daal/algorithms/covariance/DistributedStep2MasterInput;";
        jclass javaInputClass = env->FindClass(javaInputClassName);
        if(javaInputClass == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jclass javaInputClass could not be initialized"); return; }

        jfieldID inputFieldID = env->GetFieldID(javaObjectClass, "input", "Lcom/intel/daal/algorithms/covariance/DistributedStep2MasterInput;");
        if(inputFieldID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jfieldID inputFieldID could not be initialized"); return; }

        jobject javaInput = env->GetObjectField(javaObject, inputFieldID);
        if(javaInput == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jobject javaInput could not be initialized"); return; }

        jmethodID setterID = env->GetMethodID(javaInputClass, "setCInput", "(J)V");
        if(setterID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID setterID could not be initialized"); return; }

        env->CallVoidMethod(javaInput, setterID, (jlong)(_in));
    }

    void setPartialResultToJava(JNIEnv *env, jclass javaObjectClass, jobject javaObject, jobject javaContextObject)
    {
        const char *javaPartialResultClassName = "Lcom/intel/daal/algorithms/covariance/PartialResult;";
        jclass javaPartialResultClass = env->FindClass(javaPartialResultClassName);
        if(javaPartialResultClass == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jclass javaPartialResultClass could not be initialized"); return; }

        jmethodID constructPartialResultID = env->GetMethodID(javaPartialResultClass, "<init>", "(Lcom/intel/daal/services/DaalContext;J)V");
        if(constructPartialResultID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID constructPartialResultID could not be initialized"); return; }

        partialResultStorage = new SharedPtr<SerializationIface>(_partialResult);
        jobject javaPartialResultObject = env->NewObject(javaPartialResultClass, constructPartialResultID, javaContextObject,
                                                         jlong(partialResultStorage));
        if(javaPartialResultObject == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jobject javaPartialResultObject could not be initialized"); return; }

        jmethodID setPartialResultMethodID = env->GetMethodID(javaObjectClass, "setPartialResult",
                                                              "(Lcom/intel/daal/algorithms/covariance/PartialResult;)V");
        if(setPartialResultMethodID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID setPartialResultMethodID could not be initialized"); return; }

        env->CallVoidMethod(javaObject, setPartialResultMethodID, javaPartialResultObject);
    }

    void setResultToJava(JNIEnv *env, jclass javaObjectClass, jobject javaObject, jobject javaContextObject)
    {
        const char *javaResultClassName = "Lcom/intel/daal/algorithms/covariance/Result;";
        jclass javaResultClass = env->FindClass(javaResultClassName);
        if(javaResultClass == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jclass javaResultClass could not be initialized"); return; }

        jmethodID constructResultID = env->GetMethodID(javaResultClass, "<init>", "(Lcom/intel/daal/services/DaalContext;J)V");
        if(constructResultID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID constructResultID could not be initialized"); return; }

        resultStorage = new SharedPtr<SerializationIface>(_result);
        jobject javaResultObject = env->NewObject(javaResultClass, constructResultID, javaContextObject, jlong(resultStorage));
        if(javaResultObject == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jobject javaResultObject could not be initialized"); return; }

        jmethodID setResultMethodID = env->GetMethodID(javaObjectClass, "setResult", "(Lcom/intel/daal/algorithms/covariance/Result;)V");
        if(setResultMethodID == 0)
        { env->ThrowNew(env->FindClass("java/lang/Exception"), "jmethodID setResultMethodID could not be initialized"); return; }

        env->CallVoidMethod(javaObject, setResultMethodID, javaResultObject);
    }

    services::SharedPtr<Result> _result;
    services::SharedPtr<PartialResult> _partialResult;
};

} // namespace daal::algorithms::covariance
} // namespace daal::algorithms
} // namespace daal

#endif
