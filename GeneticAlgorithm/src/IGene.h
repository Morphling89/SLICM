#pragma once

#include <ostream>

//////////////////////////////////////////////////////////////////////////
class IGene
  {
  public:
    virtual IGene* Clone() const = 0;
    virtual void Swap(IGene *ip_gene) = 0;
    virtual void Copy(const IGene *ip_gene) = 0;
    virtual void Mutate() = 0;
    virtual void Print(std::ostream &o_os) const = 0;
    virtual ~IGene() {}
  };

//////////////////////////////////////////////////////////////////////////
inline std::ostream& operator<<(std::ostream& o_os, const IGene *ip_gene)
  {
  ip_gene->Print(o_os);
  return o_os;
  }

//////////////////////////////////////////////////////////////////////////
