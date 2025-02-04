/* file: forward_result.cpp */
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
#include "neural_networks/layers/average_pooling1d/JForwardResult.h"
#include "neural_networks/layers/average_pooling1d/JLayerDataId.h"

#include "daal.h"

#include "common_helpers.h"

#define auxInputDimensionsId com_intel_daal_algorithms_neural_networks_layers_average_pooling1d_LayerDataId_auxInputDimensionsId

using namespace daal;
using namespace daal::algorithms::neural_networks::layers::average_pooling1d;

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_maximum_1pooling1d_ForwardResult
 * Method:    cNewResult
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_ForwardResult_cNewResult
(JNIEnv *env, jobject thisObj)
{
    return jniArgument<forward::Result>::newObj();
}


/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_ForwardResult
 * Method:    cGetValue
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_ForwardResult_cGetValue
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id)
{
    if (id == auxInputDimensionsId)
    {
        return jniArgument<forward::Result>::get<LayerDataId, NumericTable>(resAddr, id);
    }

    return (jlong)0;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_average_1pooling1d_ForwardResult
 * Method:    cSetValue
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_average_1pooling1d_ForwardResult_cSetValue
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id, jlong ntAddr)
{
    if (id == auxInputDimensionsId)
    {
        jniArgument<forward::Result>::set<LayerDataId, NumericTable>(resAddr, auxInputDimensions, id);
    }
}
