/* file: weak_learner_model.h */
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
//  Implementation of the class defining the weak learner model.
//--
*/

#ifndef __WEAK_LEARNER_MODEL_H__
#define __WEAK_LEARNER_MODEL_H__

#include "algorithms/classifier/classifier_model.h"

namespace daal
{
namespace algorithms
{
namespace weak_learner
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__WEAK_LEARNER__PARAMETER"></a>
 * \brief %Base class for the input objects of the weak learner training and prediction algorithm
 *
 * \snippet weak_learner/weak_learner_model.h Parameter source code
 */
/* [Parameter source code] */
class Parameter : public classifier::Parameter
{
public:
    Parameter() {}
    virtual ~Parameter() {}
};
/* [Parameter source code] */

/**
 * <a name="DAAL-CLASS-ALGORITHMS__WEAK_LEARNER__MODEL"></a>
 * \brief %Base class for the weak learner model
 */
class Model : public classifier::Model
{
public:
    Model() {}
    virtual ~Model() {}
};
} // namespace interface1
using interface1::Parameter;
using interface1::Model;

} // namespace daal::algorithms::weak_learner
}
} // namespace daal
#endif // __WEAK_LEARNER_MODEL_H__
