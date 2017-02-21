#pragma once

//////////////////////////////////////////////////////////////////////////
namespace Utilities
  {
  void SeedRandomNumberGeneratorWithTime();
  double GenerateRandomDouble(const double &i_lower_bound, const double &i_upper_bound);
  int GenerateRandomInteger(const int &i_lower_bound, const int &i_upper_bound);
  double SampleNormalDistribution(const double &i_mean, const double &i_std_dev);
  }
