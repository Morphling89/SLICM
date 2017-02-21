#include "Population.h"
#include "Utilities.h"
#include <algorithm>
#include <cassert>
#include <numeric>

using namespace std;

//////////////////////////////////////////////////////////////////////////
namespace 
  {
  bool CheckChromosomeValidity(const Chromosome &i_chromosome)
    {
    return i_chromosome.GetFitness() > 0.0 && i_chromosome.Size() > 0;
    }

  //////////////////////////////////////////////////////////////////////////
  Chromosome RouletteWheelSelect(const vector<Chromosome> &i_generation, 
                                 const vector<double> &i_fitness_proportion)
    {
    assert(i_generation.size() == i_fitness_proportion.size());
    assert(abs(accumulate(i_fitness_proportion.begin(), i_fitness_proportion.end(), 0.0) - 1.0) < 1e-8);

    double random_value = Utilities::GenerateRandomDouble(0.0, 1.0);
    for (size_t i = 0; i < i_fitness_proportion.size(); ++i)
      {
      random_value -= i_fitness_proportion.at(i);

      if (random_value <= 0.0)
        return i_generation.at(i);
      }

    //deal with potential rounding errors
    return i_generation.back();
    }

  //////////////////////////////////////////////////////////////////////////
  }

//////////////////////////////////////////////////////////////////////////
Population::Population(const double &i_crossover_probability, const double &i_mutation_probability, 
                       const double &i_elitism_percentage)
  : m_crossover_probability(i_crossover_probability)
  , m_mutation_probability(i_mutation_probability)
  , m_elitism_percentage(i_elitism_percentage)
  , mp_fitness_proportion_calculator(nullptr)
  {
  assert(m_crossover_probability >= 0.0 && m_crossover_probability <= 1.0);
  assert(m_mutation_probability >= 0.0 && m_mutation_probability <= 1.0);
  assert(m_elitism_percentage >= 0.0 && m_elitism_percentage <= 1.0);
  assert((m_crossover_probability + m_elitism_percentage) <= 1.0);
  }

//////////////////////////////////////////////////////////////////////////
void Population::SetFitnessProportionCalculator(std::vector<double>(*ip_fitness_proportion_calculator)(const std::vector<Chromosome> &i_generation))
  {
  mp_fitness_proportion_calculator = ip_fitness_proportion_calculator;
  }

////////////////////////////////////////////////////////////////////////// 
size_t Population::Size() const
  {
  return m_current_generation.size();
  }

//////////////////////////////////////////////////////////////////////////
void Population::AddChromosome(const Chromosome &i_chromosome)
  {
  assert(CheckChromosomeValidity(i_chromosome));

  m_current_generation.push_back(i_chromosome);
  sort(m_current_generation.begin(), m_current_generation.end());
  }

//////////////////////////////////////////////////////////////////////////
void Population::SetGeneration(const vector<Chromosome> &i_generation)
  {
  for (auto chromosome : i_generation)
    assert(CheckChromosomeValidity(chromosome));

  m_current_generation = i_generation;
  sort(m_current_generation.begin(), m_current_generation.end());
  }

//////////////////////////////////////////////////////////////////////////
vector<Chromosome> Population::EvolveNextGeneration() const
  {
  assert(mp_fitness_proportion_calculator);
  vector<double> fitness_proportion = mp_fitness_proportion_calculator(m_current_generation);

  vector<Chromosome> next_generation;
  int elite_count = int(round(m_elitism_percentage * double(m_current_generation.size())));
  
  for (int i = 0; i < int(m_current_generation.size()); ++i)
    {
    Chromosome child;

    //elitism
    if (i < elite_count)
      {
      child = m_current_generation.at(i);
      child.SetFitness(0.0);
      }
    //crossover and mutation
    else
      {
      //generate child through crossover based on crossover probability
      if (Utilities::GenerateRandomDouble(0.0, 1.0) <= m_crossover_probability)
        {
        Chromosome parent1 = RouletteWheelSelect(m_current_generation, fitness_proportion);
        Chromosome parent2 = RouletteWheelSelect(m_current_generation, fitness_proportion);
        child = Crossover(parent1, parent2);
        }
      else
        {
        child = RouletteWheelSelect(m_current_generation, fitness_proportion);
        child.SetFitness(0.0);
        }

      //mutate based on mutation probability
      child.Mutate(m_mutation_probability);
      }

    assert(child.GetFitness() == 0.0);
    next_generation.push_back(child);
    }

  assert(m_current_generation.size() == next_generation.size());
  return next_generation;
  }

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& o_os, const std::vector<Chromosome> &i_generation)
  {
  for (size_t i = 0; i < i_generation.size(); ++i)
    {
    o_os << "Chromosome " << i << endl;
    o_os << i_generation.at(i) << endl;
    }

  return o_os;
  }

//////////////////////////////////////////////////////////////////////////