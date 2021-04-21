#pragma once

#include "../common.h"

template <typename T>
class Population
{
public:
    Population(int amount)
    {
        genomes.resize(amount);

        for (int i = 0; i < amount; i++)
        {
            genomes[i] = new T();
        }
    }

    ~Population()
    {
        for (auto& genome : genomes)
        {
            delete genome;
        }

        genomes.clear();
    }

    void Evolution()
    {
        std::vector<T*> offspring;

        std::vector<T*> fittest = Selection();

        // genomes = offspring;
    }

    std::vector<T*> Selection(float percent = 8.0f)
    {
        std::vector<T*> fittest;
        std::vector<T*> sortedByFitness = genomes;

        return fittest;
    }

    void Restart()
    {
        for (auto& genome : genomes)
        {
            genome->Reset();
        }
    }

    std::vector<T*>& GetGenomes()
    {
        return genomes;
    }

private:
    std::vector<T*> genomes;
};