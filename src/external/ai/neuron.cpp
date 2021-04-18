#include "neuron.h"

float Neuron::Sigmoid(float x)
{
    return 1.0f / (1.0f + exp(-x));
}