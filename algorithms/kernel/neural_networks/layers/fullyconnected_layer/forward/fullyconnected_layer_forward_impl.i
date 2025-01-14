/* file: fullyconnected_layer_forward_impl.i */
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
//  Implementation of fullyconnected algorithm
//--
*/

#ifndef __FULLYCONNECTED_LAYER_FORWARD_IMPL_I__
#define __FULLYCONNECTED_LAYER_FORWARD_IMPL_I__

using namespace daal::internal;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace fullyconnected
{
namespace forward
{
namespace internal
{

template<typename algorithmFPType, Method method, CpuType cpu>
void FullyconnectedKernel<algorithmFPType, method, cpu>::compute(const fullyconnected::forward::Input *input,
    const fullyconnected::Parameter *parameter, fullyconnected::forward::Result *result)
{
    SharedPtr<Tensor> inputTable   = input->get(layers::forward::data);
    SharedPtr<Tensor> wTable       = input->get(layers::forward::weights);
    SharedPtr<Tensor> bTable       = input->get(layers::forward::biases);
    SharedPtr<Tensor> resultTable  = result->get(layers::forward::value);

    size_t k = parameter->dim;
    size_t m = parameter->nOutputs;

    const services::Collection<size_t>& inDims = inputTable->getDimensions();
    const services::Collection<size_t>& wDims  = wTable->getDimensions();

    size_t nDims = inDims.size();

    size_t* dimsCounter = (size_t*)services::daal_malloc(sizeof(size_t) * nDims);
    if(!dimsCounter) {this->_errors->add(services::ErrorMemoryAllocationFailed); return;}

    SubtensorDescriptor<algorithmFPType> inputBlock;
    inputTable->getSubtensor(0, 0, 0, inDims[0], readOnly, inputBlock);
    algorithmFPType *inputArray = inputBlock.getPtr();

    SubtensorDescriptor<algorithmFPType> wBlock;
    wTable->getSubtensor(0, 0, 0, wDims[0], readOnly, wBlock);
    algorithmFPType *wArray = wBlock.getPtr();

    SubtensorDescriptor<algorithmFPType> bBlock;
    bTable->getSubtensor(0, 0, 0, m, readOnly, bBlock);
    algorithmFPType *bArray = bBlock.getPtr();

    SubtensorDescriptor<algorithmFPType> resultBlock;
    resultTable->getSubtensor(0, 0, 0, inDims[k], writeOnly, resultBlock);
    algorithmFPType *resultArray = resultBlock.getPtr();

    size_t size = 1;
    for(size_t i=0; i<nDims; i++)
    {
        dimsCounter[i] = 0;

        size *= inDims[i];
    }


    for(size_t i=0; i<m; i++)
    {
        for(size_t j=0; j<inDims[k]; j++)
        {
            resultArray[j*m + i] = bArray[i];
        }

        for(size_t j=0; j<size; j++)
        {
            size_t wJ = 0;

            size_t mul=1;
            for(size_t d=1; d<nDims+1; d++)
            {
                if(nDims-d != k)
                {
                    wJ += dimsCounter[nDims-d]*mul;
                    mul *= inDims[nDims-d];
                }
                else
                {
                    wJ += i*mul;
                    mul *= m;
                }
            }

            resultArray[dimsCounter[k]*m + i] += inputArray[j] * wArray[wJ];

            for(size_t d=1; d<nDims+1; d++)
            {
                dimsCounter[nDims-d]++;
                if(dimsCounter[nDims-d] < inDims[nDims-d]) break;
                dimsCounter[nDims-d]=0;
            }
        }
    }

    inputTable->releaseSubtensor(inputBlock);
    wTable->releaseSubtensor(wBlock);
    bTable->releaseSubtensor(bBlock);
    resultTable->releaseSubtensor(resultBlock);

    services::daal_free( dimsCounter );
}

} // internal
} // forward
} // namespace fullyconnected
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal

#endif
