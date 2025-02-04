/* file: average_pooling3d_layer_forward_types.h */
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
//  Implementation of three-dimensional average pooling layer.
//--
*/

#ifndef __AVERAGE_POOLING3D_LAYER_FORWARD_TYPES_H__
#define __AVERAGE_POOLING3D_LAYER_FORWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/pooling3d/average_pooling3d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling3d/pooling3d_layer_forward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace average_pooling3d
{
/**
 * \brief Contains classes for forward average 3D pooling layer
 */
namespace forward
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * \brief %Input objects for the forward average 3D pooling layer.
 * See \ref pooling3d::forward::interface1::Input "pooling3d::forward::Input"
 */
class Input : public pooling3d::forward::Input
{};

/**
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the forward average 3D pooling layer
 */
class Result : public pooling3d::forward::Result
{
public:
    /**
     * Default constructor
     */
    Result() {}
    virtual ~Result() {}

    using layers::forward::Result::get;
    using layers::forward::Result::set;

    /**
     * Allocates memory to store the result of the forward average 3D pooling layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] parameter %Parameter of the forward average 3D pooling layer
     * \param[in] method Computation method for the layer
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        pooling3d::forward::Result::allocate<algorithmFPType>(input, parameter, method);
        allocateLayerData<algorithmFPType>(input, parameter, method);
    }

    /**
      * Allocates memory for storing final results of the average 3D pooling layer
      * \param[in] input     Pointer to the structure with result objects
      * \param[in] parameter Pointer to the structure of layer parameters
      * \param[in] method    Computation method
      */
    template <typename algorithmFPType>
    void allocateLayerData(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        const Input *in = static_cast<const Input *>(input);

        const services::Collection<size_t> &dataDims = in->get(layers::forward::data)->getDimensions();
        set(auxInputDimensions, services::SharedPtr<data_management::NumericTable>(
                new data_management::HomogenNumericTable<int>(dataDims.size(), 1, data_management::NumericTableIface::doAllocate, 0)));
    }

    /**
     * Returns the result of the forward average 3D pooling layer
     * \param[in] id    Identifier of the result
     * \return          Result that corresponds to the given identifier
     */
    services::SharedPtr<data_management::NumericTable> get(LayerDataId id) const
    {
        services::SharedPtr<layers::LayerData> layerData = get(layers::forward::resultForBackward);
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>((*layerData)[id]);
    }

    /**
     * Sets the result of the forward average 3D pooling layer
     * \param[in] id      Identifier of the result
     * \param[in] ptr     Result
     */
    void set(LayerDataId id, const services::SharedPtr<data_management::NumericTable> &ptr)
    {
        services::SharedPtr<layers::LayerData> layerData = get(layers::forward::resultForBackward);
        (*layerData)[id] = ptr;
    }

    /**
     * Checks the result of the forward average 3D pooling layer
     * \param[in] input     %Input of the layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method    Computation method of the layer
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        pooling3d::forward::Result::check(input, parameter, method);
    }

    /**
     * Returns the serialization tag of the forward average 3D pooling layer result
     * \return     Serialization tag of the forward average 3D pooling layer result
     */
    int getSerializationTag() { return SERIALIZATION_NEURAL_NETWORKS_LAYERS_AVERAGE_POOLING3D_FORWARD_RESULT_ID; }

    /**
     * Serializes the object
     * \param[in]  arch  Storage for the serialized object or data structure
     */
    void serializeImpl(data_management::InputDataArchive  *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
     * Deserializes the object
     * \param[in]  arch  Storage for the deserialized object or data structure
     */
    void deserializeImpl(data_management::OutputDataArchive *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::OutputDataArchive, true>(arch);}

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};

} // namespace interface1
using interface1::Input;
using interface1::Result;

} // namespace forward
} // namespace pooling3d
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
