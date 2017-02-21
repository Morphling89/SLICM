#pragma once

#include "IGene.h"

//////////////////////////////////////////////////////////////////////////
class IntegerGene : public IGene
  {
  public:
    IntegerGene(const int &i_allele, const int &i_lower_bound, const int &i_upper_bound);
    IntegerGene(const int &i_lower_bound, const int &i_upper_bound);
    int GetAllele() const;
    virtual IntegerGene* Clone() const;
    virtual void Swap(IGene *ip_gene);
    virtual void Copy(const IGene *ip_gene);
    virtual void Mutate();
    virtual void Print(std::ostream &o_os) const;

  private:
    int m_allele;
    int m_lower_bound;
    int m_upper_bound;
  };

//////////////////////////////////////////////////////////////////////////
IntegerGene* CreateIntegerGene(const int &i_allele, const int &i_lower_bound, const int &i_upper_bound);
IntegerGene* CreateIntegerGene(const int &i_lower_bound, const int &i_upper_bound);

//////////////////////////////////////////////////////////////////////////
