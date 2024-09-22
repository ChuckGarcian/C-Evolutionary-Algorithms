// Title: es.c
// Description: Evolutionary Strategy Implementation

#include <string.h>
#include <tensor/tensor.h>
#include "simple_es.h"
#include "util.h"

/* Opaque Struct for Internal ES State */
struct es_algorithm
{
  size_t pop_size;
  size_t num_params;
  gsl_vector *mu;
  gsl_vector *stdev;
  gsl_matrix *current_population;
  gsl_rng *rng;
};

static struct es_algorithm es;

/* Initializes internal state of simple evolutionary algorithm. */
void es_init(size_t pop_size, size_t num_params, gsl_vector *init_x,
             gsl_vector *stdev, long seed)
{
  // Initialize Random Generator
  gsl_rng_env_setup();
  const gsl_rng_type *T = gsl_rng_default;
  es.rng = gsl_rng_alloc(T);

  // Set Struct Variables
  es.pop_size = pop_size;
  es.num_params = num_params;
  es.mu = init_x;
  es.stdev = stdev;

  // Create Initial Population
  gsl_rng_set(es.rng, seed);
  es.current_population = gsl_matrix_alloc(pop_size, num_params);
  matrix_set_normal(es.current_population, es.rng, es.mu, es.stdev);
}

/* Frees resources held by ES */
void es_terminate(void)
{
  gsl_rng_free(es.rng);
  gsl_matrix_free(es.current_population);
}

/* Returns current population matrix.
  Matrix should be freed by calling 'es_terminate()'.
*/
gsl_matrix *es_ask(void)
{
  matrix_set_normal(es.current_population, es.rng, es.mu, es.stdev);
  return es.current_population;
}

/* Updates the internal state based on fitness scores.
  fitness: gsl_vector containing fitness for current generation.
*/
void es_tell(gsl_vector *fitness)
{
  // Most Fit Individual 
  size_t best_parent_idx = gsl_vector_min_index(fitness);

  // Set new Mu value 
  for (int i = 0; i < es.num_params; i++)
  {
    double xii = gsl_matrix_get(es.current_population, best_parent_idx, 0);
    gsl_vector_set(es.mu, i, xii);
  }
}