/* file: neural_networks_prediction_model.h */
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
//  Implementation of neural network.
//--
*/

#ifndef __NEURAL_NETWORK_PREDICTION_MODEL_H__
#define __NEURAL_NETWORK_PREDICTION_MODEL_H__

#include "algorithms/algorithm.h"

#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/layer_types.h"

namespace daal
{
namespace algorithms
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__PREDICTION__MODEL"></a>
 * \brief Contains classes for training and prediction using neural network
 */
/**
 * \brief Contains classes for training and prediction using neural network
 */
namespace neural_networks
{
namespace prediction
{
namespace interface1
{

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__PREDICTION__PARAMETER"></a>
 *  \brief Class representing the parameters of neural network prediction
 */
class Parameter : public daal::algorithms::Parameter
{};

/**
* <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__PREDICTION__MODEL"></a>
* \brief Class Model object for the prediction stage of neural network algorithm
*/
class Model : public daal::algorithms::Model
{
public:
    /** \brief Default constructor */
    Model() : _forwardLayers(new neural_networks::ForwardLayers),
        _nextLayers(new services::Collection<layers::NextLayers>) {};

    /** \brief Constructor */
    Model(const services::SharedPtr<neural_networks::ForwardLayers> &forwardLayers,
          const services::SharedPtr<services::Collection<layers::NextLayers> > &nextLayers) :
        _forwardLayers(forwardLayers), _nextLayers(nextLayers) {};

    /** \brief Copy constructor */
    Model(const Model &model) : _forwardLayers(model.getLayers()), _nextLayers(model.getNextLayers()) {};

    /** \brief Destructor */
    virtual ~Model() {};

    /**
     * Sets list of forward stages of the layers
     * \param[in] forwardLayers  List of forward stages of the layers
     */
    void setLayers(const services::SharedPtr<neural_networks::ForwardLayers> &forwardLayers)
    {
        _forwardLayers = forwardLayers;
    }

    /**
     * Returns the list of forward stages of the layers
     * \return List of forward stages of the layers
     */
    const services::SharedPtr<neural_networks::ForwardLayers> getLayers() const
    {
        return _forwardLayers;
    }

    /**
     * Returns the forward stage of a layer with certain index in the network
     * \param[in] index  Index of the layer in the network
     * \return Forward stage of a layer with certain index in the network
     */
    const services::SharedPtr<layers::forward::LayerIface> getLayer(const size_t index) const
    {
        return _forwardLayers->get(index);
    }

    /**
     * Sets list of connections between layers
     * \param[in] nextLayers          List of next layers for each layer with corresponding index
     */
    void setNextLayers(const services::SharedPtr<services::Collection<layers::NextLayers> > &nextLayers)
    {
        _nextLayers = nextLayers;
    }

    /**
     * Returns list of connections between layers
     * \return          List of next layers for each layer with corresponding index
     */
    const services::SharedPtr<services::Collection<layers::NextLayers> > getNextLayers() const
    {
        return _nextLayers;
    }

    /**
     * Sets table containing all neural network weights and biases
     * \param[in] weightsAndBiases          Table containing all neural network weights and biases
     */
    void setWeightsAndBiases(const services::SharedPtr<data_management::NumericTable> &weightsAndBiases)
    {
        _weightsAndBiases = weightsAndBiases;
    }

    /**
     * Returns table containing all neural network weights and biases
     * \return          Table containing all neural network weights and biases
     */
    const services::SharedPtr<data_management::NumericTable> getWeightsAndBiases() const
    {
        return _weightsAndBiases;
    }

    /**
     * Sets collection containing all layer parameters
     * \param[in] parameters          Collection containing all layer parameters
     */
    void setParameters(const services::SharedPtr<services::Collection<services::SharedPtr<layers::Parameter> > > &parameters)
    {
        _parameters = parameters;
    }

    /**
     * Returns collection containing all layer parameters
     * \return          Collection containing all layer parameters
     */
    const services::SharedPtr<services::Collection<services::SharedPtr<layers::Parameter> > > getParameters() const
    {
        return _parameters;
    }

    /**
     * Returns the serialization tag of the neural network model
     * \return         Serialization tag of the neural network model
     */
    int getSerializationTag() { return SERIALIZATION_NEURAL_NETWORKS_PREDICTION_MODEL_ID; }
    /**
    *  Serializes an object
    *  \param[in]  arch  Storage for a serialized object or data structure
    */
    void serializeImpl(data_management::InputDataArchive   *arch)
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
    *  Deserializes an object
    *  \param[in]  arch  Storage for a deserialized object or data structure
    */
    void deserializeImpl(data_management::OutputDataArchive *arch)
    {serialImpl<data_management::OutputDataArchive, true>(arch);}

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        // Model::serialImpl<Archive, onDeserialize>(arch);

        // arch->setSharedPtrObj(_forwardLayers);
        // arch->setSharedPtrObj(_nextLayers);
    }

private:
    services::SharedPtr<neural_networks::ForwardLayers> _forwardLayers; /*!< List of forward layers of the network */
    services::SharedPtr<services::Collection<layers::NextLayers> > _nextLayers; /*!< List of edges connecting the layers in the network */
    services::SharedPtr<services::Collection<services::SharedPtr<layers::Parameter> > > _parameters; /*!< List of parameters of the layers */

    services::SharedPtr<data_management::NumericTable> _weightsAndBiases; /*!< Weights and biases of all the layers in the network */
};
} // namespace interface1
using interface1::Model;
using interface1::Parameter;
} // namespace prediction
} // namespace neural_networks
} // namespace algorithms
} //namespace daal

#endif
