#include "IntegerGene.h"
#include "Utilities.h"
#include <cassert>
#include <cmath>

using namespace std;

//////////////////////////////////////////////////////////////////////////
IntegerGene::IntegerGene(const int &i_allele, const int &i_lower_bound, const int &i_upper_bound)
  : m_allele(i_allele)
  , m_lower_bound(i_lower_bound)
  , m_upper_bound(i_upper_bound)
  {
  assert(i_upper_bound > i_lower_bound);
  assert(i_allele >= i_lower_bound);
  assert(i_allele <= i_upper_bound);
  }

//////////////////////////////////////////////////////////////////////////
IntegerGene::IntegerGene(const int &i_lower_bound, const int &i_upper_bound)
  : m_allele(Utilities::GenerateRandomInteger(i_lower_bound, i_upper_bound))
  , m_lower_bound(i_lower_bound)
  , m_upper_bound(i_upper_bound)
  {
  assert(i_upper_bound > i_lower_bound);
  }

//////////////////////////////////////////////////////////////////////////
int IntegerGene::GetAllele() const
  {
  return m_allele;
  }

//////////////////////////////////////////////////////////////////////////
IntegerGene* IntegerGene::Clone() const
  {
  return new IntegerGene(*this);
  }

//////////////////////////////////////////////////////////////////////////
void IntegerGene::Swap(IGene *ip_gene)
  {
  IntegerGene *p_int_gene = dynamic_cast<IntegerGene *>(ip_gene);
  assert(p_int_gene);

  if (p_int_gene)
    {
    assert(m_lower_bound == p_int_gene->m_lower_bound);
    assert(m_upper_bound == p_int_gene->m_upper_bound);

    int temp_allele = p_int_gene->m_allele;
    p_int_gene->m_allele = m_allele;
    m_allele = temp_allele;
    }
  }

//////////////////////////////////////////////////////////////////////////
void IntegerGene::Copy(const IGene *ip_gene)
  {
  const IntegerGene *p_int_gene = dynamic_cast<const IntegerGene *>(ip_gene);
  assert(p_int_gene);

  if (p_int_gene)
    {
    assert(m_lower_bound == p_int_gene->m_lower_bound);
    assert(m_upper_bound == p_int_gene->m_upper_bound);

    m_allele = p_int_gene->m_allele;
    }
  }

//////////////////////////////////////////////////////////////////////////
void IntegerGene::Mutate()
  {
  double mean = m_allele;
  double std_dev = 0.050 * (m_upper_bound - m_lower_bound);

  m_allele = int(round(Utilities::SampleNormalDistribution(mean, std_dev)));

  if (m_allele > m_upper_bound)
    m_allele = m_upper_bound;

  if (m_allele < m_lower_bound)
    m_allele = m_lower_bound;
  }

//////////////////////////////////////////////////////////////////////////
void IntegerGene::Print(ostream &o_os) const
  {
  o_os << m_allele;
  }

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
IntegerGene* CreateIntegerGene(const int &i_allele, const int &i_lower_bound, const int &i_upper_bound)
  {
  return new IntegerGene(i_allele, i_lower_bound, i_upper_bound);
  }

//////////////////////////////////////////////////////////////////////////
IntegerGene* CreateIntegerGene(const int &i_lower_bound, const int &i_upper_bound)
  {
  return new IntegerGene(i_lower_bound, i_upper_bound);
  }

//////////////////////////////////////////////////////////////////////////