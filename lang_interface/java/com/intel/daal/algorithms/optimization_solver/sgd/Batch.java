/* file: Batch.java */
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

package com.intel.daal.algorithms.optimization_solver.sgd;

import com.intel.daal.algorithms.AnalysisBatch;
import com.intel.daal.algorithms.ComputeMode;
import com.intel.daal.algorithms.Precision;
import com.intel.daal.services.DaalContext;
import com.intel.daal.algorithms.optimization_solver.sgd.*;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__SGD__BATCH"></a>
 * @brief %Base interface for the SGD algorithm in the batch processing mode
 *
 * @par References
 *      - <a href="DAAL-REF-SGD-ALGORITHM">SGD algorithm description and usage models</a>
 *      - com.intel.daal.algorithms.optimization_solver.sgd.Method class
 *      - Parameter class
 *      - com.intel.daal.algorithms.optimization_solver.InputId class
 *      - com.intel.daal.algorithms.optimization_solver.ResultId class
 *      - com.intel.daal.algorithms.optimization_solver.Input class
 *      - com.intel.daal.algorithms.optimization_solver.Result class
 *
 */
public class Batch extends com.intel.daal.algorithms.optimization_solver.Batch {

    public Input          input;     /*!< %Input data */
    public Method method;           /*!< Computation method for the algorithm */
    public BaseParameter parameter; /*!< Parameters of the algorithm */
    private Precision                 prec; /*!< Precision of intermediate computations */

    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs the SGD algorithm by copying input objects and parameters of another SGD algorithm
     * @param context    Context to manage the SGD algorithm
     * @param other      An algorithm to be used as the source to initialize the input objects
     *                   and parameters of the algorithm
     */
    public Batch(DaalContext context, Batch other) {
        super(context);
        this.method = other.method;
        prec = other.prec;

        this.cObject = cClone(other.cObject, prec.getValue(), method.getValue());
        input = new Input(context, cGetInput(cObject, prec.getValue(), method.getValue()));
        if(method == Method.defaultDense) {
            parameter = new ParameterDefaultDense(getContext(), cGetParameter(this.cObject, prec.getValue(), method.getValue()));
        }
        else if(method == Method.miniBatch) {
            parameter = new ParameterMiniBatch(getContext(), cGetParameter(this.cObject, prec.getValue(), method.getValue()));
        }
    }

    /**
     * <a name="DAAL-METHOD-ALGORITHMS__OPTIMIZATION_SOLVER__SGD__BATCH__BATCH"></a>
     * Constructs the SGD algorithm
     *
     * @param context      Context to manage the MSE algorithm
     * @param cls          Data type to use in intermediate computations for the MSE algorithm, Double.class or Float.class
     * @param method       SGD computation method, @ref Method
     */
    public Batch(DaalContext context, Class<? extends Number> cls, Method method) {
        super(context);

        this.method = method;

        if (method != Method.defaultDense && method != Method.miniBatch) {
            throw new IllegalArgumentException("method unsupported");
        }
        if (cls != Double.class && cls != Float.class) {
            throw new IllegalArgumentException("type unsupported");
        }

        if (cls == Double.class) {
            prec = Precision.doublePrecision;
        }
        else {
            prec = Precision.singlePrecision;
        }

        this.cObject = cInit(prec.getValue(), method.getValue());
        input = new Input(context, cGetInput(cObject, prec.getValue(), method.getValue()));
        if(method == Method.defaultDense) {
            parameter = new ParameterDefaultDense(getContext(), cGetParameter(this.cObject, prec.getValue(), method.getValue()));
        }
        else if(method == Method.miniBatch) {
            parameter = new ParameterMiniBatch(getContext(), cGetParameter(this.cObject, prec.getValue(), method.getValue()));
        }
    }

    public Batch(DaalContext context, Class<? extends Number> cls, Method method, long cAlgorithm) {
        super(context);

        this.method = method;

        if (method != Method.defaultDense && method != Method.miniBatch) {
            throw new IllegalArgumentException("method unsupported");
        }
        if (cls != Double.class && cls != Float.class) {
            throw new IllegalArgumentException("type unsupported");
        }

        if (cls == Double.class) {
            prec = Precision.doublePrecision;
        }
        else {
            prec = Precision.singlePrecision;
        }

        this.cObject = cAlgorithm;
        input = new Input(context, cGetInput(cObject, prec.getValue(), method.getValue()));
        if(method == Method.defaultDense) {
            parameter = new ParameterDefaultDense(getContext(), cGetParameter(this.cObject, prec.getValue(), method.getValue()));
        }
        else if(method == Method.miniBatch) {
            parameter = new ParameterMiniBatch(getContext(), cGetParameter(this.cObject, prec.getValue(), method.getValue()));
        }
    }

    /**
     * Computes the SGD in the batch processing mode
     * @return  Results of the computation
     */
    @Override
    public Result compute() {
        super.compute();
        Result result = new Result(getContext(), cGetResult(cObject, prec.getValue(), method.getValue()));
        return result;
    }

    /**
     * Registers user-allocated memory to store the results of computing the SGD
     * in the batch processing mode
     * @param result    Structure to store results of computing the SGD
     */
    public void setResult(Result result) {
        cSetResult(cObject, prec.getValue(), method.getValue(), result.getCObject());
    }

    /**
     * Return the input of the algorithm
     * @return Input of the algorithm
     */
    public Input getInput() {
        return (Input) input;
    }

    /**
     * Returns the newly allocated SGD algorithm
     * with a copy of input objects and parameters of this SGD algorithm
     * @param context    Context to manage the SGD algorithm
     *
     * @return The newly allocated algorithm
     */
    @Override
    public Batch clone(DaalContext context) {
        return new Batch(context, this);
    }

    private native long cInit(int prec, int method);
    private native long cClone(long algAddr, int prec, int method);
    private native long cGetInput(long cAlgorithm, int prec, int method);
    private native long cGetParameter(long cAlgorithm, int prec, int method);
    private native void cSetResult(long cAlgorithm, int prec, int method, long cObject);
    private native long cGetResult(long cAlgorithm, int prec, int method);
}
