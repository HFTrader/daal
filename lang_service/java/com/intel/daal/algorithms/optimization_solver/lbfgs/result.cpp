/* file: optimization_solver::sgd::Result.cpp */
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

#include "optimization_solver/lbfgs/JResult.h"

#include "common_defines.i"
#include "common_helpers.h"

USING_COMMON_NAMESPACES()

/*
 * Class:     com_intel_daal_algorithms_optimization_solver_lbfgs_Result
 * Method:    cNewResult
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_optimization_1solver_lbfgs_Result_cNewResult
(JNIEnv *, jobject)
{
    return jniArgument<optimization_solver::lbfgs::Result>::newObj();
}

/*
 * Class:     com_intel_daal_algorithms_optimization_solver_lbfgs_Result
 * Method:    cGetResultTable
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_optimization_1solver_lbfgs_Result_cGetResultTable
(JNIEnv *, jobject, jlong resAddr, jint id)
{
    return jniArgument<optimization_solver::lbfgs::Result>::get<optimization_solver::lbfgs::ResultId, NumericTable>(resAddr, id);
}

/*
 * Class:     com_intel_daal_algorithms_optimization_solver_lbfgs_Result
 * Method:    cSetResultTable
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_optimization_1solver_lbfgs_Result_cSetResultTable
(JNIEnv *, jobject, jlong resAddr, jint id, jlong ntAddr)
{
    jniArgument<optimization_solver::lbfgs::Result>::set<optimization_solver::lbfgs::ResultId, NumericTable>(resAddr, id, ntAddr);
}
