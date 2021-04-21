#include "genome.h"

Genome::Genome(const NeuralNetworkStructure& structure) : neuralNetwork { { structure } }
{

}

Genome::Genome(const NeuralNetwork& _neuralNetwork) : neuralNetwork { { _neuralNetwork } }
{

}

const NeuralNetwork& Genome::GetNeuralNetwork() const
{
    return neuralNetwork;
}

void Genome::SetNeuralNetwork(const NeuralNetwork& _neuralNetwork)
{
    neuralNetwork = _neuralNetwork;
}

float Genome::GetFitness() const
{
    return 0;
}

bool Genome::FitnessComparator(const Genome* a, const Genome* b)
{
    return a->GetFitness() > b->GetFitness();
}