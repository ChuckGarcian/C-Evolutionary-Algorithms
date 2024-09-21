// Title: es.c
// Description: Evolutionary Strategy Implementation

#include "es.h"

/* Initializes internal state of simple evolutionary algorithm. */
void es_init(size_t pop_size, size_t num_params, gsl_vector *init_x,
             double stdev, long seed)
{
  printf ("Called es_init \n");  
}

/* Returns current population. */
gsl_matrix *ask(void);

/* Updates the internal state based on fitness scores.
  fitness: gsl_vector containing fitness for current generation.
*/
void *tell(gsl_vector *fitness);