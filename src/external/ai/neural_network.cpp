#include "neural_network.h"

NeuralNetwork::NeuralNetwork(const NeuralNetworkStructure& _structure) : structure { _structure }
{
    layers.resize(structure.size());

    for (int i = 0; i < structure.size(); i++)
    {
        layers[i].neurons.resize(structure[i]);
    }

    for (int l = 1; l < layers.size(); l++)
    {
        Layer& previousLayer = layers[l - 1];
        Layer& currentLayer = layers[l];
        
        for (int n = 0; n < currentLayer.neurons.size(); n++)
        {
            Neuron& neuron = currentLayer.neurons[n];
            neuron.bias = util::GenRandomBias();

            neuron.weights.resize(previousLayer.neurons.size());
            
            for (int w = 0; w < neuron.weights.size(); w++)
            {
                neuron.weights[w] = util::GenRandomWeight();
            }
        }
    }
}

std::vector<value_t> NeuralNetwork::Feed(const std::vector<value_t>& inputs)
{
    assert(inputs.size() == GetFirstLayer().neurons.size() && "The amount of inputs and the amount of the neurons in the first layer must match.");

    for (int i = 0; i < inputs.size(); i++)
    {
        Layer& firstLayer = GetFirstLayer();
        firstLayer.neurons[i].value = inputs[i];
    }

    for (int l = 1; l < layers.size(); l++)
    {
        Layer& previousLayer = layers[l - 1];
        Layer& currentLayer = layers[l];

        for (int n = 0; n < currentLayer.neurons.size(); n++)
        {
            Neuron& neuron = currentLayer.neurons[n];

            neuron.value = neuron.bias;

            for (int prevLayerN = 0; prevLayerN < previousLayer.neurons.size(); prevLayerN++)
            {
                neuron.value += previousLayer.neurons[prevLayerN].value * neuron.weights[prevLayerN];
            }

            neuron.value = Neuron::Sigmoid(neuron.value);
        }
    }

    Layer& lastLayer = GetLastLayer();

    std::vector<value_t> result(lastLayer.neurons.size());

    for (int n = 0; n < lastLayer.neurons.size(); n++)
    {
        result[n] = lastLayer.neurons[n].value;
    }

    return result;
}

const NeuralNetworkStructure& NeuralNetwork::GetStructure() const
{
    return structure;
}

Layer& NeuralNetwork::GetFirstLayer()
{
    return layers[0];
}

Layer& NeuralNetwork::GetLastLayer()
{
    return layers[layers.size() - 1];
}