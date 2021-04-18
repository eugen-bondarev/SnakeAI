#pragma once

#include "common.h"

class Neuron
{
friend class Layer;
friend class NeuralNetwork;

public:
    static float Sigmoid(float x);

private:
    value_t value;
    bias_t bias;
    std::vector<weight_t> weights;
};