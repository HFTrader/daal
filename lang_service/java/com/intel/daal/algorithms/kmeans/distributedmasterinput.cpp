/* file: distributedmasterinput.cpp */
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
#include "kmeans/JDistributedStep2MasterInput.h"
#include "common_helpers.h"

USING_COMMON_NAMESPACES()
using namespace daal::algorithms::kmeans;


/*
 * Class:     com_intel_daal_algorithms_kmeans_DistributedStep2MasterInput
 * Method:    cAddInput
 * Signature: (JIJ)I
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_kmeans_DistributedStep2MasterInput_cAddInput
(JNIEnv *env, jobject thisObj, jlong inputAddr, jint id, jlong partialResultAddr)
{
    jniInput<kmeans::DistributedStep2MasterInput>::add<kmeans::MasterInputId, kmeans::PartialResult>(inputAddr, id, partialResultAddr);
}
