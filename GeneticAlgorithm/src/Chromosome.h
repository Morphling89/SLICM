#pragma once

#include "IGene.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////
class Chromosome
  {
  public:
    Chromosome();
    Chromosome(const double &i_fitness);
    ~Chromosome();
    Chromosome(const Chromosome &i_other);
    Chromosome& operator=(const Chromosome &i_rhs);
    void AddGene(IGene *ip_gene);
    size_t Size() const;
    void Print(std::ostream &o_os) const;
    Chromosome Crossover(const Chromosome &i_other) const;
    void Mutate(const double &i_mutation_probability);
    void SetFitness(const double &i_fitness);
    double GetFitness() const;
   
    template <typename FitnessCalculator>
    void CalculateFitness(FitnessCalculator i_fitness_calculator)
      {
      m_fitness = i_fitness_calculator(m_genes);
      }

    //void SwapCrossOver(Chromosome &io_other);

  private:
    std::vector<IGene *> m_genes;
    double m_fitness;
  };

//////////////////////////////////////////////////////////////////////////
Chromosome Crossover(const Chromosome &i_parent_1, const Chromosome &i_parent_2);
std::ostream& operator<<(std::ostream& o_os, const Chromosome &i_chromosome);
bool operator<(const Chromosome &i_lhs, const Chromosome &i_rhs);

//////////////////////////////////////////////////////////////////////////
