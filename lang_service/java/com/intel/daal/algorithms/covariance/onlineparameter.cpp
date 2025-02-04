/* file: onlineparameter.cpp */
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

#include "daal.h"
#include "covariance/JOnlineParameter.h"

#include "covariance_types.i"

#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::covariance;

/*
 * Class:     com_intel_daal_algorithms_covariance_OnlineParameter
 * Method:    cInit
 * Signature: (JIII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_covariance_OnlineParameter_cInit
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method, jint cmode)
{
    return jniOnline<covariance::Method, Online, defaultDense, singlePassDense, sumDense,
        fastCSR, singlePassCSR, sumCSR>::getParameter(prec, method, algAddr);
}

/*
 * Class:     com_intel_daal_algorithms_covariance_OnlineParameter
 * Method:    cSetInitializationProcedure
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_covariance_OnlineParameter_cSetInitializationProcedure
(JNIEnv *env, jobject thisObj, jlong parAddr, jlong initAddr)
{
    using namespace daal::algorithms;
    covariance::OnlineParameter *parameterAddr = (covariance::OnlineParameter *)parAddr;
    parameterAddr->initializationProcedure =
        services::SharedPtr<covariance::PartialResultsInitIface>
            (*(services::SharedPtr<covariance::PartialResultsInitIface> *)initAddr);
}
