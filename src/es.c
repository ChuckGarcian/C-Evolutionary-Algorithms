// Title: es.c
// Description: Evolutionary Strategy Implementation

#include <string.h>
#include <tensor/tensor.h>
#include <gsl/gsl_rng.h>
#include "es.h"
#include "util.h"

/* Opaque Struct for Internal ES State */
struct es_algorithm 
{
  size_t pop_size;
  size_t num_params;
  double mu;
  double stdev;
  gsl_matrix *current_population; 
  gsl_rng *rng;
};

static struct es_algorithm es;

/* Initializes internal state of simple evolutionary algorithm. */
void es_init(size_t pop_size, size_t num_params, double init_x[2],
             double stdev, long seed)
{
  printf ("\nCalled 'es_init' \n");  
  
  // Initialize Random Generator 
  gsl_rng_env_setup();  
  const gsl_rng_type *T = gsl_rng_default;  
  es.rng = gsl_rng_alloc (T); 

  // Set Helper Variables
  es.pop_size = pop_size;
  es.num_params = num_params;
  es.mu = init_x[0];
  es.stdev = stdev;
  
  // Create Initial Population    
  gsl_rng_set (es.rng, seed);
  es.current_population = gsl_matrix_alloc (pop_size, num_params);
  tensor_set_normal (tensor_view_matrix (es.current_population), es.rng, es.mu, es.stdev);
  
  printf ("\nPrinting in 'es.c::init' \n");
  print_matrix (es.current_population);
}

/* Frees resources held by ES */
void es_terminate (void)
{
  printf ("Called 'es_terminate' \n");
  gsl_rng_free (es.rng);
}

/* Returns current population matrix. 
  Matrix should be freed by calling 'es_terminate()'.
*/
gsl_matrix *es_ask(void)
{
  return es.current_population;
}

/* Updates the internal state based on fitness scores.
  fitness: gsl_vector containing fitness for current generation.
*/
void es_tell(gsl_vector *fitness)
{
  size_t best_parent_idx = gsl_vector_max_index (fitness);
  printf ("Max index: %ld,\tMax Value: ", best_parent_idx);
}