/* file: ResultCollectionId.java */
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

package com.intel.daal.algorithms.optimization_solver.objective_function;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__OBJECTIVE_FUNCTION__RESULTCOLLECTIONID"></a>
 * @brief Available result identifiers for the objective funtion algorithm
 */
public final class ResultCollectionId {
    private int _value;

    /**
    * Constructs the input identifier for objective function algorithm
    * @param value Value of identifier
    */
    public ResultCollectionId(int value) {
        _value = value;
    }

    /**
     * Returns the value corresponding to the identifier of result collection identifier object
     * @return Value corresponding to the identifier
     */
    public int getValue() {
        return _value;
    }

    private static final int gradientIdxId = 0;
    private static final int valueIdxId    = 1;
    private static final int hessianIdxId  = 2;

    public static final ResultCollectionId gradientIdx  = new ResultCollectionId(gradientIdxId); /*!< Objective function gradient
                                                                                                      index in result collection*/
    public static final ResultCollectionId valueIdx  = new ResultCollectionId(valueIdxId);       /*!< Objective function value
                                                                                                      index in result collection*/
    public static final ResultCollectionId hessianIdx  = new ResultCollectionId(hessianIdxId);   /*!< Objective function hessian
                                                                                                      index in result collection*/
}
