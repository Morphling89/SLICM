#include "Chromosome.h"
#include "Utilities.h"
#include <cassert>

using namespace std;

//////////////////////////////////////////////////////////////////////////
Chromosome::Chromosome()
  : m_fitness(0.0)
  {
  }

//////////////////////////////////////////////////////////////////////////
Chromosome::Chromosome(const double &i_fitness)
  : m_fitness(i_fitness)
  {
  }

//////////////////////////////////////////////////////////////////////////
Chromosome::~Chromosome()
  {
  for (auto p_gene : m_genes)
    delete p_gene;
  }

//////////////////////////////////////////////////////////////////////////
Chromosome::Chromosome(const Chromosome &i_other)
  {
  m_fitness = i_other.m_fitness;

  for (auto p_gene : i_other.m_genes)
    m_genes.push_back(p_gene->Clone());
  }

//////////////////////////////////////////////////////////////////////////
Chromosome& Chromosome::operator=(const Chromosome &i_rhs)
  {
  if (this == &i_rhs)
    return *this;

  for (auto p_gene : m_genes)
    delete p_gene;

  m_genes.clear();

  m_fitness = i_rhs.m_fitness;

  for (auto p_gene : i_rhs.m_genes)
    m_genes.push_back(p_gene->Clone());

  return *this;
  }

//////////////////////////////////////////////////////////////////////////
void Chromosome::AddGene(IGene *ip_gene)
  {
  m_genes.push_back(ip_gene);
  }

//////////////////////////////////////////////////////////////////////////
size_t Chromosome::Size() const
  {
  return m_genes.size();
  }

//////////////////////////////////////////////////////////////////////////
void Chromosome::Print(ostream &o_os) const
  {
  for (size_t i = 0; i < m_genes.size(); ++i)
    o_os << "Param" << i << ": " << m_genes.at(i) << endl;

  if (m_fitness != 0.0)
    o_os << "Fitness: " << m_fitness << endl;
  }

//////////////////////////////////////////////////////////////////////////
Chromosome Chromosome::Crossover(const Chromosome &i_other) const
  {
  assert(m_genes.size() == i_other.m_genes.size());

  Chromosome child(*this);
  child.SetFitness(0.0);

  for (size_t i = 0; i < child.m_genes.size(); ++i)
    {
    if (Utilities::GenerateRandomInteger(0, 1))
      {      
      child.m_genes.at(i)->Copy(i_other.m_genes.at(i));
      }
    }

  return child;
  }

//////////////////////////////////////////////////////////////////////////
void Chromosome::Mutate(const double &i_mutation_probability)
  {
  assert(i_mutation_probability >= 0.0 && i_mutation_probability <= 1.0);

  for (auto p_gene : m_genes)
    {
    if (Utilities::GenerateRandomDouble(0.0, 1.0) <= i_mutation_probability)
      p_gene->Mutate();
    }
  }

//////////////////////////////////////////////////////////////////////////
void Chromosome::SetFitness(const double &i_fitness)
  {
  m_fitness = i_fitness;
  }

//////////////////////////////////////////////////////////////////////////
double Chromosome::GetFitness() const
  {
  return m_fitness;
  }

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
Chromosome Crossover(const Chromosome &i_parent_1, const Chromosome &i_parent_2)
  {
  return i_parent_1.Crossover(i_parent_2);
  }

//////////////////////////////////////////////////////////////////////////
ostream& operator<<(ostream& o_os, const Chromosome &i_chromosome)
  {
  i_chromosome.Print(o_os);
  return o_os;
  }

//////////////////////////////////////////////////////////////////////////
bool operator<(const Chromosome &i_lhs, const Chromosome &i_rhs)
  {
  return i_lhs.GetFitness() < i_rhs.GetFitness();
  }

//////////////////////////////////////////////////////////////////////////