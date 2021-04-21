#include "genome.h"

Genome::Genome(const NeuralNetworkStructure& structure) : neuralNetwork { { structure } }
{

}

Genome::Genome(const NeuralNetwork& _neuralNetwork) : neuralNetwork { { _neuralNetwork } }
{

}

float Genome::GetFitness() const
{
    return 0;
}