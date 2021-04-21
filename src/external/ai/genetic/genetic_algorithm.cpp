#include "genetic_algorithm.h"

#include <bitset>
#include <climits>
#include <cmath>

using float_bits_t = std::bitset<sizeof(float) * CHAR_BIT>;

inline static float_bits_t FloatToBits(float n)
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

inline static float BitsToFloat(const float_bits_t& param) {
    const auto val = param.to_ulong();
    float result;

    memcpy(&result, &val, sizeof(float));

    return result;
}

value_t BitwiseCrossover(value_t parent0, value_t parent1)
{
    const float_bits_t bitsOfParent0 = FloatToBits(parent0);
    const float_bits_t bitsOfParent1 = FloatToBits(parent1);
    // float_bits_t bitsOfChild = FloatToBits(0);

    // const bool randomBool = rand() % 2 == 1;
    // const float_bits_t& firstParent = (randomBool) ? bitsOfParent0 : bitsOfParent1;
    // const float_bits_t& secondParent = (randomBool) ? bitsOfParent1 : bitsOfParent0;

    // const int cross = rand() % bitsOfChild.size();

    // for (int bit = 0; bit < cross; bit++)
    // {
    //     bitsOfChild[bit] = firstParent[bit];
    // }

    // for (int bit = cross; bit < bitsOfChild.size(); bit++)
    // {
    //     bitsOfChild[bit] = secondParent[bit];
    // }

    // float child = BitsToFloat(bitsOfChild);

    float_bits_t ch = FloatToBits(parent0);

    for (int i = rand() % ch.size(); i > 0; i--)
    {
        ch[i] = bitsOfParent1[i];
    }

    float child = BitsToFloat(ch);
    
    return child;
}

value_t NumberCrossover(value_t parent0, value_t parent1)
{    
    if (rand() % 2 == 1)
        return parent0;
    else
        return parent1;
}

value_t BitwiseMutation(value_t value, float bitMutationRate = 1.0f / 6.5f)
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

NeuralNetwork GA::Crossover(const NeuralNetwork& parent0, const NeuralNetwork& parent1, float mutationRate, float bitMutationRate)
{
    NeuralNetwork child(parent0.GetStructure());

    for (int l = 0; l < child.layers.size(); l++)
    {
        for (int n = 0; n < child.layers[l].neurons.size(); n++)
        {
            bias_t biasOfParent0 = parent0.layers[l].neurons[n].bias;
            bias_t biasOfParent1 = parent1.layers[l].neurons[n].bias;
            bias_t biasOfChild = BitwiseCrossover(biasOfParent0, biasOfParent1);
            // bias_t biasOfChild = NumberCrossover(biasOfParent0, biasOfParent1);

            // while (std::isnan(biasOfChild) || biasOfChild < util::BIAS_BOTTOM || biasOfChild > util::BIAS_TOP)
            while (std::isnan(biasOfChild))
            {
                biasOfChild = BitwiseCrossover(biasOfParent0, biasOfParent1);
            }

            if ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) < 0.1f)
            {
                float mutated = BitwiseMutation(biasOfChild, bitMutationRate);
                // if (!std::isnan(mutated) && mutated > util::BIAS_BOTTOM && mutated < util::BIAS_TOP)
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
                // weight_t weightOfChild = NumberCrossover(weightOfParent0, weightOfParent1);

                // while (std::isnan(weightOfChild) || weightOfChild < util::WEIGHT_BOTTOM || weightOfChild > util::WEIGHT_TOP)
                while (std::isnan(weightOfChild))
                {
                    weightOfChild = BitwiseCrossover(weightOfParent0, weightOfParent1);
                }

                if ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) < 0.02f)
                {
                    float mutated = BitwiseMutation(weightOfChild, bitMutationRate);
                    // if (!std::isnan(mutated) && mutated > util::WEIGHT_BOTTOM && mutated < util::WEIGHT_TOP)
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