/* file: pooling1d_layer_backward_types.h */
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

/*
//++
//  Implementation of backward 1D pooling layer.
//--
*/

#ifndef __POOLING1D_LAYER_BACKWARD_TYPES_H__
#define __POOLING1D_LAYER_BACKWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_backward_types.h"
#include "algorithms/neural_networks/layers/pooling1d/pooling1d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace pooling1d
{
/**
 * \brief Contains classes for backward one-dimensional (1D) pooling layer
 */
namespace backward
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * \brief %Input objects for the backward 1D pooling layer
 */
class Input : public layers::backward::Input
{
public:
    /** Default constructor */
    Input() {}

    virtual ~Input() {}

    /**
     * Checks an input object for the backward 1D pooling layer
     * \param[in] parameter Algorithm parameter
     * \param[in] method Computation method
     */
    void check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        const Parameter *param = static_cast<const Parameter *>(parameter);

        services::SharedPtr<data_management::Tensor> inputGradientTensor = get(layers::backward::inputGradient);
        services::SharedPtr<services::Error> error = checkTensor(inputGradientTensor, "inputGradient");
        if (error) { this->_errors->add(error); return; }

        size_t nDim = inputGradientTensor->getNumberOfDimensions();
        if(param->indices.size[0] > nDim - 1)
        {
            error = services::SharedPtr<services::Error>(new services::Error());
            error->setId(services::ErrorIncorrectParameter);
            error->addStringDetail(services::ArgumentName, "indices");
            this->_errors->add(error);
            return;
        }

        services::Collection<size_t> inputDims = getInputGradientSize(param);

        error = checkTensor(inputGradientTensor, "inputGradient", &inputDims);
        if (error) { this->_errors->add(error); return; }
    }

    /**
     * Return the collection with gradient size
     * \return The collection with gradient size
     */
    virtual services::Collection<size_t> getGradientSize() const = 0;

protected:
    virtual services::Collection<size_t> getInputGradientSize(const pooling1d::Parameter *parameter) const = 0;
};

/**
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the backward 1D pooling layer
 */
class Result : public layers::backward::Result
{
public:
    /** Default constructor */
    Result() {}
    virtual ~Result() {}

    /**
     * Allocates memory to store the result of the backward 1D pooling layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] method Computation method for the layer
     * \param[in] parameter %Parameter of the backward 1D pooling layer
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        const Input *in = static_cast<const Input *>(input);
        services::SharedPtr<services::Error> error = checkTensor(in->get(layers::backward::inputGradient), "inputGradient");
        if (error) { this->_errors->add(error); return; }

        set(layers::backward::gradient, services::SharedPtr<data_management::Tensor>(
                new data_management::HomogenTensor<algorithmFPType>(in->getGradientSize(),
                        data_management::Tensor::doAllocate)));
    }

    /**
     * Checks the result of the backward 1D pooling layer
     * \param[in] input %Input object for the layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method Computation method
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        const Parameter *param = static_cast<const Parameter *>(parameter);
        const Input *algInput = static_cast<const Input*>(input);
        const services::Collection<size_t> &gradientDims = algInput->getGradientSize();
        services::SharedPtr<services::Error> error = checkTensor(get(layers::backward::gradient), "gradient", &gradientDims);
        if (error) { this->_errors->add(error); return; }

        size_t spatialDimension = param->indices.size[0];
        size_t kernelSize = param->kernelSize.size[0];

        if (kernelSize == 0 || kernelSize > gradientDims[spatialDimension] + 2 * param->padding.size[0])
        {
            error = services::SharedPtr<services::Error>(new services::Error());
            error->setId(services::ErrorIncorrectParameter);
            error->addStringDetail(services::ArgumentName, "kernelSize");
            this->_errors->add(error);
            return;
        }
    }
};

} // namespace interface1
using interface1::Input;
using interface1::Result;
} // namespace backward

} // namespace pooling1d
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
