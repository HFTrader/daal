/* file: batch_result.cpp */
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

#include <jni.h>
#include "cholesky/JMethod.h"
#include "cholesky/JResult.h"
#include "cholesky/JResultId.h"
#include "daal.h"
#include "common_helpers.h"

USING_COMMON_NAMESPACES()
using namespace daal::algorithms::cholesky;

#define DefaultMethodValue com_intel_daal_algorithms_cholesky_Method_DefaultMethodValue
#define DefaultResultId com_intel_daal_algorithms_cholesky_ResultId_DefaultResultId

/*
 * Class:     com_intel_daal_algorithms_cholesky_Result
 * Method:    cNewResult
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_cholesky_Result_cNewResult
(JNIEnv *env, jobject thisObj)
{
    return jniArgument<cholesky::Result>::newObj();
}

/*
 * Class:     com_intel_daal_algorithms_cholesky_Result
 * Method:    cGetResult
 * Signature:(JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_cholesky_Result_cGetResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniBatch<cholesky::Method, Batch, defaultDense>::getResult(prec, method, algAddr);
}

/*
 * Class:     com_intel_daal_algorithms_cholesky_Result
 * Method:    cGetCholeskyFactor
 * Signature:(J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_cholesky_Result_cGetCholeskyFactor
(JNIEnv *env, jobject thisObj, jlong resAddr)
{
    return jniArgument<cholesky::Result>::get<cholesky::ResultId, NumericTable>(resAddr, choleskyFactor);
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_cholesky_Result_cSetCholeskyFactor
(JNIEnv *env, jobject thisObj, jlong resAddr, jlong ntAddr)
{
    jniArgument<cholesky::Result>::set<cholesky::ResultId, NumericTable>(resAddr, choleskyFactor, ntAddr);
}
