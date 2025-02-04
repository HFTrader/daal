/* file: parameter.cpp */
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
#include "neural_networks/layers/split/JParameter.h"

#include "daal.h"

#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::neural_networks::layers;

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_split_Parameter
 * Method:    cInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_split_Parameter_cInit
  (JNIEnv *env, jobject thisObj)
{
    return (jlong)(new split::Parameter);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_split_Parameter
 * Method:    cGetNOutputs
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_split_Parameter_cGetNOutputs
  (JNIEnv *env, jobject thisObj, jlong cParameter)
{
    return (jlong)((((split::Parameter *)cParameter))->nOutputs);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_split_Parameter
 * Method:    cSetNOutputs
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_split_Parameter_cSetNOutputs
  (JNIEnv *env, jobject thisObj, jlong cParameter, jlong nOutputs)
{
    (((split::Parameter *)cParameter))->nOutputs = (size_t)nOutputs;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_split_Parameter
 * Method:    cGetNInputs
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_split_Parameter_cGetNInputs
  (JNIEnv *env, jobject thisObj, jlong cParameter)
{
    return (jlong)((((split::Parameter *)cParameter))->nInputs);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_split_Parameter
 * Method:    cGetNInputs
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_split_Parameter_cSetNInputs
  (JNIEnv *env, jobject thisObj, jlong cParameter, jlong nInputs)
{
    (((split::Parameter *)cParameter))->nInputs = (size_t)nInputs;
}
