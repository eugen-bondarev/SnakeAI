#pragma once

#include "common.h"

#include "layer.h"

class NeuralNetwork
{
friend class GA;

public:
    NeuralNetwork(const NeuralNetworkStructure& structure);

    std::vector<value_t> Feed(const std::vector<value_t>& inputs);

    const NeuralNetworkStructure& GetStructure() const;

    weight_t GetWeight(int layer, int neuron, int weight) const;
    bias_t GetBias(int layer, int neuron) const;

private:
    std::vector<Layer> layers;

    NeuralNetworkStructure structure;

    Layer& GetFirstLayer();
    Layer& GetLastLayer();
};