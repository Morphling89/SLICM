#pragma once

#include "IGene.h"

//////////////////////////////////////////////////////////////////////////
class DoubleGene : public IGene
  {
  public:
    DoubleGene(const double &i_allele, const double &i_lower_bound, const double &i_upper_bound);
    DoubleGene(const double &i_lower_bound, const double &i_upper_bound);
    double GetAllele() const;
    virtual DoubleGene* Clone() const;
    virtual void Swap(IGene *ip_gene);
    virtual void Copy(const IGene *ip_gene);
    virtual void Mutate();
    virtual void Print(std::ostream &o_os) const;

  private:
    double m_allele;
    double m_lower_bound;
    double m_upper_bound;
  };

//////////////////////////////////////////////////////////////////////////
DoubleGene* CreateDoubleGene(const double &i_allele, const double &i_lower_bound, const double &i_upper_bound);
DoubleGene* CreateDoubleGene(const double &i_lower_bound, const double &i_upper_bound);

//////////////////////////////////////////////////////////////////////////
