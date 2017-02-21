#pragma once

#include "Chromosome.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////
class Population
  {
  public:
    Population(const double &i_crossover_probability, const double &i_mutation_probability, 
               const double &i_elitism_percentage = 0.0);
    void SetFitnessProportionCalculator(std::vector<double>(*ip_fitness_proportion_calculator)(const std::vector<Chromosome> &i_generation));
    size_t Size() const;
    void AddChromosome(const Chromosome &i_chromosome);
    void SetGeneration(const std::vector<Chromosome> &i_generation);
    std::vector<Chromosome> EvolveNextGeneration() const;

  private:
    std::vector<Chromosome> m_current_generation;
    double m_crossover_probability;
    double m_mutation_probability;
    double m_elitism_percentage;
    std::vector<double>(*mp_fitness_proportion_calculator)(const std::vector<Chromosome> &i_generation);
  };

//////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& o_os, const std::vector<Chromosome> &i_generation);

//////////////////////////////////////////////////////////////////////////