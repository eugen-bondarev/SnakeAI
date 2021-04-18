#pragma once

#include "common.h"

#include "neuron.h"

class Layer
{
friend class NeuralNetwork;

private:
    std::vector<Neuron> neurons;

};