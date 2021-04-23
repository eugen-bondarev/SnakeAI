#pragma once

#include "../common.h"
#include "genetic_algorithm.h"

template <typename T>
class Population
{
public:
    Population(int sizeOfPopulation)
    {
        genomes.resize(sizeOfPopulation);

        for (int i = 0; i < sizeOfPopulation; i++)
        {
            genomes[i] = new T();
        }
    }

    void KillPopulation()
    {
        for (auto& genome : genomes)
        {
            delete genome;
        }

        genomes.clear();
    }

    ~Population()
    {
        KillPopulation();
    }

    void Evolution(float selection = 8.0f)
    {
        std::vector<T*> fittest = Population<T>::Selection(genomes, selection);
        std::vector<int> roulette = Population<T>::CreateRoulette(fittest);
        std::vector<T*> offspring = Population<T>::Crossover(fittest, static_cast<int>(genomes.size()), roulette);

        KillPopulation();

        genomes = offspring;

        generation += 1;
    }

    static std::vector<T*> Selection(const std::vector<T*>& population, float percent)
    {
        std::vector<T*> fittest;
        std::vector<T*> sortedByFitness = population;
        std::sort(sortedByFitness.begin(), sortedByFitness.end(), Genome::FitnessComparator);
        
        int amountOfFittest = static_cast<int>(static_cast<float>(population.size()) * (percent / 100.0f));
        fittest.resize(amountOfFittest);

        for (int i = 0; i < fittest.size(); i++)
        {
            fittest[i] = sortedByFitness[i];
        }

        return fittest;
    }

    static std::vector<int> CreateRoulette(const std::vector<T*>& fittest)
    {
        std::vector<int> roulette;

        int maxIndex = static_cast<int>(fittest.size()) - 1;

        for (int i = 0; i < fittest.size(); i++)
        {
            for (int j = 0; j < (fittest.size() - i) / (i + 1) + 1; j++)
            {
                roulette.emplace_back(i);
            }
        }

        return roulette;
    }

    static T* SelectParent(const std::vector<T*>& fittest, const std::vector<int>& roulette, T* avoid = nullptr)
    {
        T* parent { avoid };

        while (parent == avoid)
        {
            int randomIndexInRoulette = rand() % roulette.size();
            int indexOfParent = roulette[randomIndexInRoulette];
            parent = fittest[indexOfParent];
        }

        return parent;
    }

    static std::vector<T*> Crossover(const std::vector<T*>& fittest, int sizeOfNewPopulation, const std::vector<int>& roulette)
    {
        std::vector<T*> offspring;

        for (int i = 0; i < sizeOfNewPopulation; i++)
        {
            T* newGenome = new T();

            T* parent0 = SelectParent(fittest, roulette);
            T* parent1 = SelectParent(fittest, roulette, parent0);

            const NeuralNetwork newNeuralNetwork0 = GA::Crossover(parent0->GetNeuralNetwork(), parent1->GetNeuralNetwork());
            newGenome->SetNeuralNetwork(newNeuralNetwork0);
            offspring.emplace_back(newGenome);
        }

        return offspring;
    }

    void Restart()
    {
        for (auto& genome : genomes)
        {
            genome->Reset();
        }
    }

    const std::vector<T*>& GetGenomes() const
    {
        return genomes;
    }

    int GetGeneration() const
    {
        return generation;
    }

private:
    std::vector<T*> genomes;

    int generation { 0 };
};