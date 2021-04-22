#include "genetic_algorithm.h"

#include <bitset>
#include <climits>
#include <cmath>

using float_bits_t = std::bitset<sizeof(float) * CHAR_BIT>;

static float_bits_t FloatToBits(float n)
{
    union
    {
        float input;
        int   output;
    } data;

    data.input = n;

    float_bits_t bits(data.output);

    return bits;
}

static float BitsToFloat(const float_bits_t& param) {
    const auto val = param.to_ulong();
    float result;

    memcpy(&result, &val, sizeof(float));

    return result;
}

static value_t BitwiseCrossover(value_t parent0, value_t parent1)
{
    const float_bits_t bitsOfParent0 = FloatToBits(parent0);
    float_bits_t child = FloatToBits(parent1);

    for (int i = rand() % child.size(); i >= 0; i--)
    {
        child[i] = bitsOfParent0[i];
    }
    
    return BitsToFloat(child);
}

static value_t BitwiseMutation(value_t value, float bitMutationRate)
{
    float_bits_t bits = FloatToBits(value);

    for (int i = 0; i < bits.size(); i++)
    {
        if (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < bitMutationRate)
        {
            bits[i] = !bits[i];
        }
    }

    return BitsToFloat(bits);
}

NeuralNetwork GA::Crossover(const NeuralNetwork& parent0, const NeuralNetwork& parent1, MutationTendency mutationTendency)
{
    NeuralNetwork child(parent0.GetStructure());

    for (int l = 0; l < child.layers.size(); l++)
    {
        for (int n = 0; n < child.layers[l].neurons.size(); n++)
        {
            bias_t biasOfParent0 = parent0.layers[l].neurons[n].bias;
            bias_t biasOfParent1 = parent1.layers[l].neurons[n].bias;
            bias_t biasOfChild = BitwiseCrossover(biasOfParent0, biasOfParent1);
            
            while (std::isnan(biasOfChild))
            {
                biasOfChild = BitwiseCrossover(biasOfParent0, biasOfParent1);
            }

            if ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) < mutationTendency.biasMutationRate.chanceOfMutation)
            {
                float mutated = BitwiseMutation(biasOfChild, mutationTendency.biasMutationRate.chanceOfBitMutation);
                if (!std::isnan(mutated))
                {
                    biasOfChild = mutated;
                }
            }

            child.layers[l].neurons[n].bias = biasOfChild;

            for (int w = 0; w < child.layers[l].neurons[n].weights.size(); w++)
            {
                weight_t weightOfParent0 = parent0.layers[l].neurons[n].weights[w];
                weight_t weightOfParent1 = parent1.layers[l].neurons[n].weights[w];
                weight_t weightOfChild = BitwiseCrossover(weightOfParent0, weightOfParent1);
                
                while (std::isnan(weightOfChild))
                {
                    weightOfChild = BitwiseCrossover(weightOfParent0, weightOfParent1);
                }

                if ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) < mutationTendency.weightMutationRate.chanceOfMutation)
                {
                    float mutated = BitwiseMutation(weightOfChild, mutationTendency.weightMutationRate.chanceOfBitMutation);
                    if (!std::isnan(mutated))
                    {
                        weightOfChild = mutated;
                    }
                }

                child.layers[l].neurons[n].weights[w] = weightOfChild;
            }
        }
    }

    return child;
}