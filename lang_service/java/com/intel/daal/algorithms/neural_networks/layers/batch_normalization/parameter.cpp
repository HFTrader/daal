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
#include "neural_networks/layers/batch_normalization/JParameter.h"

#include "daal.h"

#include "common_helpers.h"

USING_COMMON_NAMESPACES()
using namespace daal::algorithms::neural_networks::layers;

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cInit
  (JNIEnv *env, jobject thisObj)
{
    return (jlong)(new batch_normalization::Parameter);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cGetAlpha
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cGetAlpha
  (JNIEnv *env, jobject thisObj, jlong cParameter)
{
    return (((batch_normalization::Parameter *)cParameter))->alpha;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cSetAlpha
 * Signature: (JD)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cSetAlpha
  (JNIEnv *env, jobject thisObj, jlong cParameter, jdouble alpha)
{
    (((batch_normalization::Parameter *)cParameter))->alpha = alpha;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cGetEpsilon
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cGetEpsilon
  (JNIEnv *env, jobject thisObj, jlong cParameter)
{
    return (((batch_normalization::Parameter *)cParameter))->epsilon;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cSetEpsilon
 * Signature: (JD)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cSetEpsilon
  (JNIEnv *env, jobject thisObj, jlong cParameter, jdouble epsilon)
{
    (((batch_normalization::Parameter *)cParameter))->epsilon = epsilon;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cGetDimension
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cGetDimension
  (JNIEnv *env, jobject thisObj, jlong cParameter)
{
    return (jlong)((((batch_normalization::Parameter *)cParameter))->dimension);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cSetDimension
 * Signature: (JD)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cSetDimension
  (JNIEnv *env, jobject thisObj, jlong cParameter, jlong dimension)
{
    (((batch_normalization::Parameter *)cParameter))->dimension = (size_t)dimension;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cGetPredictionStage
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cGetPredictionStage
  (JNIEnv *env, jobject thisObj, jlong cParameter)
{
    return (((batch_normalization::Parameter *)cParameter))->predictionStage;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_batch_normalization_Parameter
 * Method:    cSetPredictionStage
 * Signature: (JZ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_batch_1normalization_Parameter_cSetPredictionStage
  (JNIEnv *env, jobject thisObj, jlong cParameter, jboolean predictionStage)
{
    (((batch_normalization::Parameter *)cParameter))->predictionStage = predictionStage;
}
