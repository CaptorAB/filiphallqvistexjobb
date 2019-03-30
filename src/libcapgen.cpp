#ifndef __EMSCRIPTEN__
#define CATCH_CONFIG_RUNNER
#include <lib/catch.h>
#endif

#include <vector>
#include <lib/random.h>

#include <include/genetic.h>
#include <include/scenario.h>

#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcapgen)
{
  value_object<OptimizeOptions>("OptimizeOptions")
      .field("population", &OptimizeOptions::population)
      .field("elitism", &OptimizeOptions::elitism)
      .field("generations", &OptimizeOptions::generations)
      .field("bits", &OptimizeOptions::bits)
      .field("steps", &OptimizeOptions::steps)
      .field("instruments", &OptimizeOptions::instruments);

  value_object<Result>("Result")
      .field("fitness", &Result::fitness)
      .field("chromosome", &Result::chromosome)
      .field("individual", &Result::individual);

  emscripten::register_vector<int>("VectorInt");
  emscripten::register_vector<double>("VectorDouble");

  function("optimize", &optimize);
}

#else

/*

TEST_CASE("sample_black_process calculates correct values", "[sample_black_process]")
{
  double n1 = 0.12;
  double n2 = 0.33;
  double forward_price = 0.91;
  double gamma = 0.42;
  double rho = 0.9;
  double sigma = 0.78;
  double mean = 1.0;
  double variance = 0.99;

  double result = sample_black_process(n1, n2, forward_price, gamma, rho, sigma, mean, variance);
  REQUIRE(result - 0.267704205 <= 0.0001); // TODO: Verify this using pen and paper
}

TEST_CASE("DomesticMarketRiskProcess calculates correct values", "[risk]")
{
  double n1 = 0.25;
  double n2 = 0.9;
  RiskProcess *risk_process = new DomesticMarketRiskProcess();

  double current = risk_process->get_current();

  REQUIRE(current == 0.0);

  risk_process->update(n1, n2);

  current = risk_process->get_current();

  REQUIRE(current - 0.3456077342 <= 0.0001); // TODO: Verify this using pen and paper
}

TEST_CASE("DomesticEquity moves correctly", "[risk]")
{
  double n1 = 0.25;
  double n2 = 0.9;
  risks_t risks = create_default_risks();
  Instrument *instrument = new DomesticEquityInstrument();

  double current = instrument->get_current();

  REQUIRE(current == 1.0);

  instrument->update(risks);

  current = instrument->get_current();

  REQUIRE(current - 0.3456077342 <= 0.0001); // TODO: Verify this using pen and paper
}

TEST_CASE("initialize_chromosomes generates a population with correct capacity and values", "[genetic]")
{
  int population = 2;
  int genes = 10;
  int size = population * genes;

  std::vector<int> chromosomes = initialize_chromosomes(population, genes);

  REQUIRE(chromosomes.capacity() == size);
  for (size_t i = 0; i < size; i++)
  {
    REQUIRE((chromosomes[i] == 1 || chromosomes[i] == 0));
  }
}

TEST_CASE("decode_chromosomes correctly decodes a chromosome", "[genetic]")
{
  int population = 2;
  int bits = 3;
  int variables = 2;
  int instruments = 2;
  int genes = variables * bits;
  int size = population * variables;

  std::vector<int> chromosomes{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0};
  std::vector<double> individuals = decode_chromosomes(chromosomes, population, variables, instruments, genes, bits);

  REQUIRE(individuals.capacity() == size);
  REQUIRE(individuals[0] == 4.0 / 7.0);
  REQUIRE(individuals[1] == 3.0 / 7.0);
  REQUIRE(individuals[2] == 1.0 / (double)variables);
  REQUIRE(individuals[3] == 1.0 / (double)variables);
}

TEST_CASE("select_roulette selects proper indices", "[genetic]")
{
  std::vector<double> fitnesses({0.01, 0.02, 1.25, 0.02, 0.3, 1.1, 0.9});
  std::tuple<size_t, size_t> selected = select_roulette(fitnesses);

  REQUIRE(std::get<0>(selected) == 2);
  REQUIRE(std::get<1>(selected) == 5);
}

TEST_CASE("evaluate_individuals correctly evaluates individuals", "[genetic]")
{
  int population = 2;
  int variables = 3;

  std::vector<double> individuals({0.0, 0.5, 0.5, 1.0, 0.0, 0.0});
  std::vector<double> fitnesses = evaluate_individuals(individuals, population, variables);

  REQUIRE(fitnesses[0] == -100.0);
  REQUIRE(fitnesses[1] == 1000.0);
}

TEST_CASE("crossover_chromosomes correctly crossovers chromosomes", "[genetic]")
{
  std::vector<int> chromosomes({0, 0, 0, 0, 1, 1, 1, 0});
  std::vector<double> evaluated({0.0, 2.0});
  std::vector<int> crossovered = crossover_chromosomes(chromosomes, evaluated, 2, 4, 1.0);

  REQUIRE(crossovered[0] == 1);
  REQUIRE(crossovered[1] == 1);
  REQUIRE(crossovered[2] == 1);
  REQUIRE(crossovered[3] == 0);
  REQUIRE(crossovered[4] == 1);
  REQUIRE(crossovered[5] == 1);
  REQUIRE(crossovered[6] == 1);
  REQUIRE(crossovered[7] == 0);
}

*/

TEST_CASE("optimization works", "[genetic]")
{
  OptimizeOptions options;
  options.population = 100;
  options.elitism = 2;
  options.generations = 100;
  options.bits = 7;
  options.steps = 3;
  options.instruments = 2;
  options.mutation = 0.02;
  options.crossover = 0.4;

  optimize(options);
}

using Random = effolkronium::random_static;
int main(int argc, char *argv[])
{
  Random::seed(42);
  int result = Catch::Session().run(argc, argv);
  return result;
}

#endif