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

private:
    std::vector<Layer> layers;

    NeuralNetworkStructure structure;

    Layer& GetFirstLayer();
    Layer& GetLastLayer();
};