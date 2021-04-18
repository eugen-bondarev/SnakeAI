#pragma once

#include "common.h"

#include "layer.h"

class NeuralNetwork
{
public:
    NeuralNetwork(const NeuralNetworkStructure& structure);

    std::vector<value_t> Feed(const std::vector<value_t>& inputs);

private:
    std::vector<Layer> layers;

    NeuralNetworkStructure structure;

    Layer& GetFirstLayer();
    Layer& GetLastLayer();
};