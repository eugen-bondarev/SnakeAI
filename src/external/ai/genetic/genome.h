#pragma once

#include "../neural_network.h"

class Genome
{
public:
    Genome(const NeuralNetworkStructure& structure);
    Genome(const NeuralNetwork& neuralNetwork);

    const NeuralNetwork& GetNeuralNetwork() const;
    void SetNeuralNetwork(const NeuralNetwork& neuralNetwork);

    virtual float GetFitness() const;
    static bool FitnessComparator(const Genome* a, const Genome* b);

protected:
    NeuralNetwork neuralNetwork;
};