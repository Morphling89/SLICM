#include "DoubleGene.h"
#include "Utilities.h"
#include <cassert>

using namespace std;

//////////////////////////////////////////////////////////////////////////
DoubleGene::DoubleGene(const double &i_allele, const double &i_lower_bound, const double &i_upper_bound)
  : m_allele(i_allele)
  , m_lower_bound(i_lower_bound)
  , m_upper_bound(i_upper_bound)
  {
  assert(i_upper_bound > i_lower_bound);
  assert(i_allele >= i_lower_bound);
  assert(i_allele <= i_upper_bound);
  }

//////////////////////////////////////////////////////////////////////////
DoubleGene::DoubleGene(const double &i_lower_bound, const double &i_upper_bound)
  : m_allele(Utilities::GenerateRandomDouble(i_lower_bound, i_upper_bound))
  , m_lower_bound(i_lower_bound)
  , m_upper_bound(i_upper_bound)
  {
  assert(i_upper_bound > i_lower_bound);
  }

//////////////////////////////////////////////////////////////////////////
double DoubleGene::GetAllele() const
  {
  return m_allele;
  }

//////////////////////////////////////////////////////////////////////////
DoubleGene* DoubleGene::Clone() const
  {
  return new DoubleGene(*this);
  }

//////////////////////////////////////////////////////////////////////////
void DoubleGene::Swap(IGene *ip_gene)
  {
  DoubleGene *p_double_gene = dynamic_cast<DoubleGene *>(ip_gene);
  assert(p_double_gene);

  if (p_double_gene)
    {
    assert(m_lower_bound == p_double_gene->m_lower_bound);
    assert(m_upper_bound == p_double_gene->m_upper_bound);

    double temp_allele = p_double_gene->m_allele;
    p_double_gene->m_allele = m_allele;
    m_allele = temp_allele;
    }
  }

//////////////////////////////////////////////////////////////////////////
void DoubleGene::Copy(const IGene *ip_gene)
  {
  const DoubleGene *p_double_gene = dynamic_cast<const DoubleGene *>(ip_gene);
  assert(p_double_gene);

  if (p_double_gene)
    {
    assert(m_lower_bound == p_double_gene->m_lower_bound);
    assert(m_upper_bound == p_double_gene->m_upper_bound);

    m_allele = p_double_gene->m_allele;
    }
  }

//////////////////////////////////////////////////////////////////////////
void DoubleGene::Mutate()
  {
  double mean = m_allele;
  double std_dev = 0.050 * (m_upper_bound - m_lower_bound);

  m_allele = Utilities::SampleNormalDistribution(mean, std_dev);

  if (m_allele > m_upper_bound)
    m_allele = m_upper_bound;

  if (m_allele < m_lower_bound)
    m_allele = m_lower_bound;
  }

//////////////////////////////////////////////////////////////////////////
void DoubleGene::Print(ostream &o_os) const
  {
  o_os << m_allele;
  }

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
DoubleGene* CreateDoubleGene(const double &i_allele, const double &i_lower_bound, const double &i_upper_bound)
  {
  return new DoubleGene(i_allele, i_lower_bound, i_upper_bound);
  }

//////////////////////////////////////////////////////////////////////////
DoubleGene* CreateDoubleGene(const double &i_lower_bound, const double &i_upper_bound)
  {
  return new DoubleGene(i_lower_bound, i_upper_bound);
  }

//////////////////////////////////////////////////////////////////////////