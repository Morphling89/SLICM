#include "DoubleGene.h"
#include "IntegerGene.h"
#include "Population.h"
#include "Utilities.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////
const double PARAM0_MIN_VALUE = 0.0;
const double PARAM0_MAX_VALUE = 1.0;
const int    PARAM1_MIN_VALUE = 0;
const int    PARAM1_MAX_VALUE = 100;
const double PARAM2_MIN_VALUE = 0.0;
const double PARAM2_MAX_VALUE = 1.0;
const int    PARAM3_MIN_VALUE = 0;
const int    PARAM3_MAX_VALUE = 20;
const int    PARAM4_MIN_VALUE = 0;
const int    PARAM4_MAX_VALUE = 20;
const int    PARAM5_MIN_VALUE = 0;
const int    PARAM5_MAX_VALUE = 20;

//////////////////////////////////////////////////////////////////////////
// Enum
//////////////////////////////////////////////////////////////////////////
enum EProgramMode
  {
  GENERATE_POPULATION = 1,
  EVOLVE_POPULATION = 2
  };

//////////////////////////////////////////////////////////////////////////
namespace
  {
  //////////////////////////////////////////////////////////////////////////
  vector<double> CalculateFitnessProportion(const vector<Chromosome> &i_generation)
    {
    //assumption: i_generation has been sorted in ascending order of fitness
    assert(!i_generation.empty());
    double max_fitness = i_generation.back().GetFitness();

    //assumption: fitness is execution time, inverted fitness is speedup
    vector<double> inverted_fitness;
    for (auto chromosome : i_generation)
      inverted_fitness.push_back(max_fitness / chromosome.GetFitness());

    double total = accumulate(inverted_fitness.begin(), inverted_fitness.end(), 0.0);

    assert(total > 0.0);

    vector<double> fitness_proportion;
    for (auto value : inverted_fitness)
      fitness_proportion.push_back(value / total);

    return fitness_proportion;
    }

  //////////////////////////////////////////////////////////////////////////
  void CommandLineArgumentError()
    {
    cout << "Usage: GeneticAlgorithm POPULATION_SIZE OUTPUT_FILENAME [CROSSOVER_PROBABILITY MUTATION_PROBABILITY ELITISM_PERCENTAGE INPUT_FILENAME]" << endl;
    cout << "POPULATION_SIZE > 0" << endl;
    cout << "0.0 <= CROSSOVER_PROBABILITY <= 1.0" << endl;
    cout << "0.0 <= MUTATION_PROBABILITY <= 1.0" << endl;
    cout << "0.0 <= ELITISM_PERCENTAGE <= 1.0" << endl;
    cout << "CROSSOVER_PROBABILITY + ELITISM_PERCENTAGE <= 1.0" << endl;
    exit(EXIT_FAILURE);
    }

  //////////////////////////////////////////////////////////////////////////
  void FileOpenError(const string &i_filename)
    {
    cout << "Error opening file: " << i_filename << endl;
    exit(EXIT_FAILURE);
    }

  //////////////////////////////////////////////////////////////////////////
  bool CheckInputFile(const string &i_filename)
    {
    bool result(true);

    ifstream fin;
    fin.open(i_filename.c_str());

    if (!fin.is_open())
      result = false;
    else
      fin.close();

    return result;
    }

  //////////////////////////////////////////////////////////////////////////
  bool CheckOutputFile(const string &i_filename)
    {
    bool result(true);

    ofstream fout;
    fout.open(i_filename.c_str());

    if (!fout.is_open())
      result = false;
    else
      fout.close();

    return result;
    }

  //////////////////////////////////////////////////////////////////////////
  void ProcessCommandLineArguments(int &o_program_mode, int &o_population_size, string &o_output_filename,
                                   double &o_crossover_probability, double &o_mutation_probability, double &o_elitism_percentage,
                                   string &o_input_filename, int argc, char *argv[])
    {
    if (argc != 3 && argc != 7)
      CommandLineArgumentError();

    o_population_size = atoi(argv[1]);
    if (o_population_size <= 0)
      CommandLineArgumentError();

    o_output_filename = string(argv[2]);
    if (!CheckOutputFile(o_output_filename))
      FileOpenError(o_output_filename);

    if (argc == 3)
      {
      o_program_mode = GENERATE_POPULATION;
      return;
      }

    if (argc == 7)
      {
      o_program_mode = EVOLVE_POPULATION;

      o_crossover_probability = atof(argv[3]);
      o_mutation_probability = atof(argv[4]);
      o_elitism_percentage = atof(argv[5]);
      if (o_crossover_probability < 0.0 || o_crossover_probability > 1.0 ||
          o_mutation_probability < 0.0 || o_mutation_probability > 1.0 ||
          o_elitism_percentage < 0.0 || o_elitism_percentage > 1.0 ||
          (o_crossover_probability + o_elitism_percentage) > 1.0)
        CommandLineArgumentError();

      o_input_filename = string(argv[6]);
      if (!CheckInputFile(o_input_filename))
        FileOpenError(o_input_filename);

      return;
      }
    }

  //////////////////////////////////////////////////////////////////////////
  void WritePopulationToFile(const vector<Chromosome> &i_generation, const string &i_output_filename)
    {
    ofstream fout;
    fout.open(i_output_filename.c_str());
    if (!fout.is_open())
      {
      cout << "Error opening file: " << i_output_filename << endl;
      exit(EXIT_FAILURE);
      }

    for (auto chromosome : i_generation)
      fout << chromosome << endl;

    fout.close();
    }

  //////////////////////////////////////////////////////////////////////////
  void GeneratePopulation(const int &i_population_size, const string &i_output_filename)
    {
    vector<Chromosome> generation;

    for (int i = 0; i < i_population_size; ++i)
      {
      Chromosome chromosome;

      chromosome.AddGene(CreateDoubleGene(PARAM0_MIN_VALUE, PARAM0_MAX_VALUE));
      chromosome.AddGene(CreateIntegerGene(PARAM1_MIN_VALUE, PARAM1_MAX_VALUE));
      chromosome.AddGene(CreateDoubleGene(PARAM2_MIN_VALUE, PARAM2_MAX_VALUE));
      chromosome.AddGene(CreateIntegerGene(PARAM3_MIN_VALUE, PARAM3_MAX_VALUE));
      chromosome.AddGene(CreateIntegerGene(PARAM4_MIN_VALUE, PARAM4_MAX_VALUE));
      chromosome.AddGene(CreateIntegerGene(PARAM5_MIN_VALUE, PARAM5_MAX_VALUE));

      generation.push_back(chromosome);
      }

    WritePopulationToFile(generation, i_output_filename);
    }

  //////////////////////////////////////////////////////////////////////////
  void UnexpectedEndOfFileError()
    {
    cout << "Unexpected end of file." << endl;
    exit(EXIT_FAILURE);
    }

  //////////////////////////////////////////////////////////////////////////
  string ReadString(ifstream &i_fin)
    {
    string value;
    if (!(i_fin >> value))
      UnexpectedEndOfFileError();

    return value;
    }

  //////////////////////////////////////////////////////////////////////////
  int ReadInteger(ifstream &i_fin)
    {
    int value;
    if (!(i_fin >> value))
      UnexpectedEndOfFileError();

    return value;
    }

  //////////////////////////////////////////////////////////////////////////
  double ReadDouble(ifstream &i_fin)
    {
    double value;
    if (!(i_fin >> value))
      UnexpectedEndOfFileError();

    return value;
    }

  //////////////////////////////////////////////////////////////////////////
  void ReadPopulationFromFile(vector<Chromosome> &o_population, const string &i_input_filename, const int &i_population_size)
    {
    ifstream fin;
    fin.open(i_input_filename.c_str());
    if (!fin.is_open())
      {
      cout << "Error opening file: " << i_input_filename << endl;
      exit(EXIT_FAILURE);
      }

    o_population.clear();
    for (int i = 0; i < i_population_size; ++i)
      {
      Chromosome chromosome;

      ReadString(fin);
      chromosome.AddGene(CreateDoubleGene(ReadDouble(fin), PARAM0_MIN_VALUE, PARAM0_MAX_VALUE));
      
      ReadString(fin);
      chromosome.AddGene(CreateIntegerGene(ReadInteger(fin), PARAM1_MIN_VALUE, PARAM1_MAX_VALUE));

      ReadString(fin);
      chromosome.AddGene(CreateDoubleGene(ReadDouble(fin), PARAM2_MIN_VALUE, PARAM2_MAX_VALUE));

      ReadString(fin);
      chromosome.AddGene(CreateIntegerGene(ReadInteger(fin), PARAM3_MIN_VALUE, PARAM3_MAX_VALUE));

      ReadString(fin);
      chromosome.AddGene(CreateIntegerGene(ReadInteger(fin), PARAM4_MIN_VALUE, PARAM4_MAX_VALUE));

      ReadString(fin);
      chromosome.AddGene(CreateIntegerGene(ReadInteger(fin), PARAM5_MIN_VALUE, PARAM5_MAX_VALUE));

      ReadString(fin);
      chromosome.SetFitness(ReadDouble(fin));

      o_population.push_back(chromosome);
      }

    fin.close();
    }

  //////////////////////////////////////////////////////////////////////////
  void EvolvePopulation(const int &i_population_size, const string &i_output_filename, const double &i_crossover_probability,
                        const double &i_mutation_probability, const double &i_elitism_percentage, const string &i_input_filename)
    {
    vector<Chromosome> generation;
    ReadPopulationFromFile(generation, i_input_filename, i_population_size);

    Population population(i_crossover_probability, i_mutation_probability, i_elitism_percentage);
    population.SetFitnessProportionCalculator(CalculateFitnessProportion);
    population.SetGeneration(generation);
    vector<Chromosome> next_generation = population.EvolveNextGeneration();

    WritePopulationToFile(next_generation, i_output_filename);
    }

  //////////////////////////////////////////////////////////////////////////
  }

//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
  {
  Utilities::SeedRandomNumberGeneratorWithTime();

  int program_mode(0), population_size;
  string input_filename, output_filename;
  double crossover_probability, mutation_probability, elitism_percentage;
  ProcessCommandLineArguments(program_mode, population_size, output_filename, crossover_probability, 
                              mutation_probability, elitism_percentage, input_filename, argc, argv);

  if (program_mode == GENERATE_POPULATION)
    {
    GeneratePopulation(population_size, output_filename);
    }

  if (program_mode == EVOLVE_POPULATION)
    {
    EvolvePopulation(population_size, output_filename, crossover_probability, 
                     mutation_probability, elitism_percentage, input_filename);
    }

  return 0;
  }

//////////////////////////////////////////////////////////////////////////