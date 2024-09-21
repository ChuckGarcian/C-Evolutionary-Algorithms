#include <stdio.h>
#include <assert.h>
#include <tensor/tensor.h>

#include "es.h"
#include "util.h"

void test_rastrigin (void);

int main(void)
{
  printf ("Initializing Now\n");
  
  
  size_t pop_size = 100;    // Population Size
  size_t num_params = 10;   // Number of Model Parameters
  double stdev = .10;       // Standard Deviation
  long seed = 42;           // Seed for Random Functions    
  double data_init_x[] = {0, 0}; // Initial Guess of Optimal
  gsl_vector_view init_x = gsl_vector_view_array (data_init_x, 2); 
  
  
  es_init (pop_size, num_params, &init_x.vector, stdev, seed);
  return 0;
}
