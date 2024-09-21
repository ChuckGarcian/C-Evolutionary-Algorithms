#include <stdio.h>
#include <assert.h>
#include <tensor/tensor.h>

#include "es.h"
#include "util.h"

void test_rastrigin (void);

int main(void)
{
  printf ("Initializing Now\n");

  size_t pop_size = 10;      // Population Size
  size_t num_params = 2;     // Number of Model Parameters
  double stdev = .10;        // Standard Deviation
  long seed = 42;            // Seed for Random Functions    
  double init_x[2] = {0, 0}; // Initial Guess of Optimal
  
  es_init (pop_size, num_params, init_x, stdev, seed);

  gsl_matrix *population = es_ask ();
  
  gsl_vector *fitness_scores = rastrigin_fn (population);
  printf("\nPrinting in 'main', after calling rastrigin: \n");
  print_vector (fitness_scores);
  
  printf ("\n-- Printing Population Matrix -- \n");
  printf ("\n-- Printing Fitness Scores -- \n");
  print_vector (fitness_scores);

  return 0;
}
