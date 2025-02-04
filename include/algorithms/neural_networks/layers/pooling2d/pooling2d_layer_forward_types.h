/* file: pooling2d_layer_forward_types.h */
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
//  Implementation of the forward 2D pooling layer types.
//--
*/

#ifndef __POOLING2D_LAYER_FORWARD_TYPES_H__
#define __POOLING2D_LAYER_FORWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_forward_types.h"
#include "algorithms/neural_networks/layers/pooling2d/pooling2d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace pooling2d
{
/**
 * \brief Contains classes for the forward one-dimensional (2D) pooling layer
 */
namespace forward
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * \brief %Input objects for the forward 2D pooling layer
 */
class Input : public layers::forward::Input
{
public:
    /**
     * Default constructor
     */
    Input() : layers::forward::Input() {}

    virtual ~Input() {}

    /**
     * Allocates memory to store input objects of forward 2D pooling layer
     * \param[in] parameter %Parameter of forward 2D pooling layer
     * \param[in] method    Computation method for the layer
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Parameter *parameter, const int method) {}

    /**
     * Returns dimensions of weights tensor
     * \return Dimensions of weights tensor
     */
    virtual const services::Collection<size_t> getWeightsSizes(const layers::Parameter *parameter) const
    {
        return services::Collection<size_t>();
    }

    /**
     * Returns dimensions of biases tensor
     * \return Dimensions of biases tensor
     */
    virtual const services::Collection<size_t> getBiasesSizes(const layers::Parameter *parameter) const
    {
        return services::Collection<size_t>();
    }

    /**
     * Checks an input object for the 2D pooling layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method    Computation method of the layer
     */
    void check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        layers::forward::Input::check(parameter, method);
        const Parameter *param = static_cast<const Parameter *>(parameter);
        services::SharedPtr<data_management::Tensor> dataTensor = get(layers::forward::data);
        const services::Collection<size_t> &dataDims = dataTensor->getDimensions();
        size_t nDim = dataDims.size();

        for (size_t i = 0; i < 2; i++)
        {
            size_t spatialDimension = param->indices.size[i];
            if (spatialDimension > nDim - 1)
            {
                services::SharedPtr<services::Error> error(new services::Error());
                error->setId(services::ErrorIncorrectParameter);
                error->addStringDetail(services::ArgumentName, "indices");
                this->_errors->add(error);
                return;
            }

            size_t kernelSize = param->kernelSize.size[i];
            if (kernelSize == 0 || kernelSize > dataDims[spatialDimension] + 2 * param->padding.size[i])
            {
                services::SharedPtr<services::Error> error(new services::Error());
                error->setId(services::ErrorIncorrectParameter);
                error->addStringDetail(services::ArgumentName, "kernelSize");
                this->_errors->add(error);
                return;
            }
        }
        if (param->indices.size[0] == param->indices.size[1])
        {
            services::SharedPtr<services::Error> error(new services::Error());
            error->setId(services::ErrorIncorrectParameter);
            error->addStringDetail(services::ArgumentName, "indices");
            this->_errors->add(error);
            return;
        }
    }
};


/**
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the forward 2D pooling layer
 */
class Result : public layers::forward::Result
{
public:
    /** Default constructor */
    Result() {}
    virtual ~Result() {}

    /**
     * Returns dimensions of value tensor
     * \return Dimensions of value tensor
     */
    virtual const services::Collection<size_t> getValueSize(const services::Collection<size_t> &inputSize,
                                                            const daal::algorithms::Parameter *par, const int method) const DAAL_C11_OVERRIDE
    {
        services::Collection<size_t> valueDims(inputSize);
        computeValueDimensions(valueDims, static_cast<const Parameter *>(par));
        return valueDims;
    }

    /**
     * Allocates memory to store the result of the forward 2D pooling layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] method Computation method for the layer
     * \param[in] parameter %Parameter of the forward 2D pooling layer
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        const Input *in = static_cast<const Input *>(input);
        const Parameter *algParameter = static_cast<const Parameter *>(parameter);

        services::Collection<size_t> valueDims(in->get(layers::forward::data)->getDimensions());
        computeValueDimensions(valueDims, algParameter);

        Argument::set(layers::forward::value, services::SharedPtr<data_management::SerializationIface>(
                          new data_management::HomogenTensor<algorithmFPType>(valueDims, data_management::Tensor::doAllocate)));
        Argument::set(layers::forward::resultForBackward, services::SharedPtr<data_management::SerializationIface>(
                          new LayerData()));
    }

    /**
     * Checks the result of the forward 2D pooling layer
     * \param[in] input %Input object for the layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method Computation method
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        const Input *algInput = static_cast<const Input *>(input);
        const Parameter *param = static_cast<const Parameter *>(parameter);

        services::SharedPtr<data_management::Tensor> dataTensor = algInput->get(layers::forward::data);
        const services::Collection<size_t> &dataDims = dataTensor->getDimensions();
        services::Collection<size_t> valueDims(dataDims);

        computeValueDimensions(valueDims, param);

        services::SharedPtr<data_management::Tensor> valueTensor = get(layers::forward::value);
        services::SharedPtr<services::Error> error = checkTensor(valueTensor, "value", &valueDims);
        if (error) { this->_errors->add(error); return; }

        services::SharedPtr<LayerData> layerData = get(layers::forward::resultForBackward);
        if (!layerData) { this->_errors->add(services::ErrorNullLayerData); return; }

        if (layerData->size() != 1)
            if (!layerData) { this->_errors->add(services::ErrorIncorrectSizeOfLayerData); return; }
    }

protected:
    size_t computeValueDimension(size_t dataDim, size_t kernelSize, size_t padding, size_t stride) const
    {
        size_t valueDim = (dataDim + 2 * padding - kernelSize + stride) / stride;
        return valueDim;
    }

    void computeValueDimensions(services::Collection<size_t> &dims, const Parameter *param) const
    {
        for (size_t d = 0; d < 2; d++)
        {
            dims[param->indices.size[d]] =
                computeValueDimension(dims[param->indices.size[d]], param->kernelSize.size[d], param->padding.size[d], param->stride.size[d]);
        }
    }
};

} // namespace interface1
using interface1::Input;
using interface1::Result;

} // namespace forward
} // namespace pooling2d
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
