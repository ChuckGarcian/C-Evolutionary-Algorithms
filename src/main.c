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
  double init_x[2] = {-4, -4}; // Initial Guess of Optimal
  
  es_init (pop_size, num_params, init_x, stdev, seed);

  int generations = 10;

  gsl_matrix *best = gsl_matrix_calloc(generations, num_params);

  for (int gen = 0; gen < generations; gen++)
  {
    /* Develop Next Generation */
    gsl_matrix *population = es_ask ();
    gsl_vector *fitness_scores = sphere_fn (population);
    es_tell (fitness_scores);
    
    /* Store Results */
    size_t best_idx = gsl_vector_min_index (fitness_scores);
    printf ("Gen=%d,\t(", gen+1);    
    
    // Store each parameter of the best individual
    for (int i = 0; i < num_params; i++) 
    {      
      double param_i = gsl_matrix_get (population, best_idx, i);
      printf ("x%d=%g,", i, param_i);
      gsl_matrix_set (best, gen, i, param_i);
    }
      printf ("),\tfit=%g", gsl_vector_get (fitness_scores, best_idx));
    printf ("\n");
      
  }
  
  printf ("Done\n");
  print_vector (best);

  return 0;
}
