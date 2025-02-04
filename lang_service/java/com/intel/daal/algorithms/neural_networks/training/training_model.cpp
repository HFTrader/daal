/* file: training_model.cpp */
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
#include "neural_networks/training/JTrainingModel.h"

#include "daal.h"

#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::neural_networks;

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cInit__
(JNIEnv *env, jobject thisObj)
{
    return (jlong)(new SharedPtr<training::Model>(new training::Model()));
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cInit
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cInit__J
(JNIEnv *env, jobject thisObj, jlong modelAddr)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)modelAddr);
    return (jlong)(new SharedPtr<training::Model>(new training::Model(*model)));
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cInsertLayer
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingBatch_cInsertLayer
  (JNIEnv *env, jobject thisObj, jlong cModel, jlong layerDescriptorAddr)
{
    layers::LayerDescriptor *layerDescriptor = (layers::LayerDescriptor *)layerDescriptorAddr;
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    model->insertLayer(*layerDescriptor);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cInitialize
 * Signature: (JI[JJJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingBatch_cInitialize
  (JNIEnv *env, jobject thisObj, jlong cModel, jint prec, jlongArray dataSizeArray, jlong layerDescriptorsAddr, jlong parameterAddr)
{
    SharedPtr<Collection<layers::LayerDescriptor> > layerDescriptors = *(SharedPtr<Collection<layers::LayerDescriptor> > *)layerDescriptorsAddr;

    size_t len = (size_t)(env->GetArrayLength(dataSizeArray));
    jlong *dataSize = env->GetLongArrayElements(dataSizeArray, 0);

    Collection<size_t> dataSizeCollection;

    for (size_t i = 0; i < len; i++) {
        dataSizeCollection.push_back((size_t)dataSize[i]);
    }

    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);

    if (prec == 0)
    {
        model->initialize<double>(dataSizeCollection, *layerDescriptors, (training::Parameter<double> *)parameterAddr);
    } else
    {
        model->initialize<float>(dataSizeCollection, *layerDescriptors, (training::Parameter<float> *)parameterAddr);
    }
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cSetForwardLayers
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cSetForwardLayers
(JNIEnv *env, jobject thisObj, jlong cModel, jlong forwardLayersAddr)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<ForwardLayers> forwardLayers = *((SharedPtr<ForwardLayers> *)forwardLayersAddr);
    model->setForwardLayers(forwardLayers);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cGetForwardLayers
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cGetForwardLayers
(JNIEnv *env, jobject thisObj, jlong cModel)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<ForwardLayers> *forwardLayersAddr = new SharedPtr<ForwardLayers>(model->getForwardLayers());
    return (jlong) forwardLayersAddr;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cGetForwardLayer
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cGetForwardLayer
(JNIEnv *env, jobject thisObj, jlong cModel, jlong index)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<layers::forward::LayerIface> *forwardLayerAddr =
        new SharedPtr<layers::forward::LayerIface>(model->getForwardLayer((size_t)index));
    return (jlong) forwardLayerAddr;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cSetBackwardLayers
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cSetBackwardLayers
(JNIEnv *env, jobject thisObj, jlong cModel, jlong backwardLayersAddr)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<BackwardLayers> backwardLayers = *((SharedPtr<BackwardLayers> *)backwardLayersAddr);
    model->setBackwardLayers(backwardLayers);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cGetBackwardLayers
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cGetBackwardLayers
(JNIEnv *env, jobject thisObj, jlong cModel)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<BackwardLayers> *backwardLayersAddr = new SharedPtr<BackwardLayers>(model->getBackwardLayers());
    return (jlong) backwardLayersAddr;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cGetBackwardLayer
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cGetBackwardLayer
(JNIEnv *env, jobject thisObj, jlong cModel, jlong index)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<layers::backward::LayerIface> *backwardLayerAddr =
        new SharedPtr<layers::backward::LayerIface>(model->getBackwardLayer((size_t)index));
    return (jlong) backwardLayerAddr;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cSetNextLayers
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cSetNextLayers
(JNIEnv *env, jobject thisObj, jlong cModel, jlong nextLayersCollectionAddr)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<Collection<layers::NextLayers> > nextLayersCollection = *((SharedPtr<Collection<layers::NextLayers> > *)nextLayersCollectionAddr);
    model->setNextLayers(nextLayersCollection);
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cGetNextLayers
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cGetNextLayers
(JNIEnv *env, jobject thisObj, jlong cModel)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    SharedPtr<Collection<layers::NextLayers> > *nextLayersCollectionAddr = new SharedPtr<Collection<layers::NextLayers> >(model->getNextLayers());
    return (jlong) nextLayersCollectionAddr;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_training_TrainingModel
 * Method:    cGetPredictionModel
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_training_TrainingModel_cGetPredictionModel
(JNIEnv *env, jobject thisObj, jlong cModel)
{
    SharedPtr<training::Model> model = *((SharedPtr<training::Model> *)cModel);
    return (jlong) (new SharedPtr<prediction::Model>(new prediction::Model(*model->getPredictionModel())));
}
