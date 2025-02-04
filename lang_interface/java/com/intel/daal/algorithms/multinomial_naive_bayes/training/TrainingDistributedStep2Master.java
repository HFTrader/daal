/* file: TrainingDistributedStep2Master.java */
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

package com.intel.daal.algorithms.multinomial_naive_bayes.training;

import com.intel.daal.algorithms.ComputeMode;
import com.intel.daal.algorithms.Precision;
import com.intel.daal.algorithms.classifier.training.TrainingDistributedInput;
import com.intel.daal.algorithms.multinomial_naive_bayes.Parameter;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTINOMIAL_NAIVE_BAYES__TRAINING__TRAININGDISTRIBUTEDSTEP2MASTER"></a>
 * @brief Algorithm class for training naive Bayes model on the second step in the distributed processing mode
 *
 * @par References
 *      - <a href="DAAL-REF-MULTINOMNAIVEBAYES-ALGORITHM">Multinomial naive Bayes algorithm description and usage models</a>
 *      - TrainingMethod class
 *      - com.intel.daal.algorithms.classifier.training.InputId class
 *      - com.intel.daal.algorithms.classifier.training.TrainingResultId class
 *      - com.intel.daal.algorithms.classifier.training.TrainingInput class
 *      - TrainingResult class
 */
public class TrainingDistributedStep2Master extends com.intel.daal.algorithms.classifier.training.TrainingDistributed {
    public Parameter  parameter;     /*!< Parameters of the algorithm */
    public TrainingMethod method;   /*!< %Training method for the algorithm */

    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs multinomial naive Bayes training algorithm by copying input objects and parameters
     * of another multinomial naive Bayes training algorithm
     * @param context   Context to manage the multinomial naive Bayes training
     * @param other     An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    public TrainingDistributedStep2Master(DaalContext context, TrainingDistributedStep2Master other) {
        super(context);
        this.method = other.method;
        prec = other.prec;

        this.cObject = cClone(other.cObject, prec.getValue(), method.getValue());

        input = new TrainingDistributedInput(getContext(), cObject, ComputeMode.distributed);
        parameter = new Parameter(getContext(), cInitParameter(this.cObject, prec.getValue(), method.getValue()));
    }

    /**
     * Constructs multinomial naive Bayes training algorithm
     * @param context   Context to manage the multinomial naive Bayes training
     * @param cls       Data type to use in intermediate computations of the multinomial naive Bayes training on the second step in the distributed
     *                  processing mode,
     *                  Double.class or Float.class
     * @param method    Multinomial naive Bayes training method on the second step in the distributed processing mode, @ref TrainingMethod
     * @param nClasses  Number of classes
     */
    public TrainingDistributedStep2Master(DaalContext context, Class<? extends Number> cls, TrainingMethod method,
            long nClasses) {
        super(context);

        this.method = method;
        if (cls != Double.class && cls != Float.class) {
            throw new IllegalArgumentException("type unsupported");
        }

        if (this.method != TrainingMethod.defaultDense &&
            this.method != TrainingMethod.fastCSR) {
            throw new IllegalArgumentException("method unsupported");
        }

        if (cls == Double.class) {
            prec = Precision.doublePrecision;
        } else {
            prec = Precision.singlePrecision;
        }

        this.cObject = cInit(prec.getValue(), method.getValue(), nClasses);

        input = new TrainingDistributedInput(getContext(), cObject, ComputeMode.distributed);
        parameter = new Parameter(getContext(), cInitParameter(this.cObject, prec.getValue(), method.getValue()));
    }

    /**
     * Computes naive Bayes training results on the second step in the distributed processing mode
     * \return Naive Bayes training results on the second step in the distributed processing mode
     */
    @Override
    public TrainingPartialResult compute() {
        super.compute();
        TrainingPartialResult presult = new TrainingPartialResult(getContext(), cGetPartialResult(cObject, prec.getValue(), method.getValue()));
        return presult;
    }

    /**
     * Computes naive Bayes training results on the second step in the distributed processing mode
     * \return Naive Bayes training results on the second step in the distributed processing mode
     */
    @Override
    public TrainingResult finalizeCompute() {
        super.finalizeCompute();
        TrainingResult result = new TrainingResult(getContext(), cGetResult(cObject, prec.getValue(), method.getValue()));
        return result;
    }

    /**
     * Returns the newly allocated multinomial naive Bayes training algorithm
     * with a copy of input objects and parameters of this multinomial naive Bayes training algorithm
     * @param context   Context to manage the multinomial naive Bayes training
     *
     * @return The newly allocated algorithm
     */
    @Override
    public TrainingDistributedStep2Master clone(DaalContext context) {
        return new TrainingDistributedStep2Master(context, this);
    }

    private native long cInit(int prec, int method, long nClasses);

    private native long cInitParameter(long algAddr, int prec, int method);

    private native long cGetResult(long algAddr, int prec, int method);

    private native long cGetPartialResult(long algAddr, int prec, int method);

    private native long cClone(long algAddr, int prec, int method);
}
