#include "Utilities.h"
#include <chrono>
#include <random>

using namespace std;

//////////////////////////////////////////////////////////////////////////
namespace Utilities
  {
  static default_random_engine generator;

  //////////////////////////////////////////////////////////////////////////
  void SeedRandomNumberGeneratorWithTime()
    {
    generator.seed(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    }

  //////////////////////////////////////////////////////////////////////////
  double GenerateRandomDouble(const double &i_lower_bound, const double &i_upper_bound)
    {
    uniform_real_distribution<double> distribution(i_lower_bound, i_upper_bound);
    return distribution(generator);
    }

  //////////////////////////////////////////////////////////////////////////
  int GenerateRandomInteger(const int &i_lower_bound, const int &i_upper_bound)
    {
    uniform_int_distribution<int> distribution(i_lower_bound, i_upper_bound);
    return distribution(generator);
    }

  //////////////////////////////////////////////////////////////////////////
  double SampleNormalDistribution(const double &i_mean, const double &i_std_dev)
    {
    normal_distribution<double> distribution(i_mean, i_std_dev);
    return distribution(generator);
    }

  //////////////////////////////////////////////////////////////////////////
  }