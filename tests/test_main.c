#include <stdio.h>
#include <assert.h>
#include <tensor/tensor.h>

#include "../src/es.h"
#include "../src/util.h"

void test_rastrigin (void);
void test_es_init_and_rastrigin (void);

int test_main (void)
{
  test_rastrigin ();
  return 0;
}

void test_rastrigin (void)
{
  int size1, size2;
  gsl_matrix *mat;
  gsl_vector *result;

  size1 = 3;
  size2 = 2;

  /* Allocate and Initialize a Matrix */
  mat = gsl_matrix_alloc (size1, size2);
  arange_matrix (mat, 1);
  print_matrix (mat);
  gsl_matrix_scale(mat, .2);
  printf ("Printing Matrix Prior: \n");
  print_matrix (mat);
  
  result = rastrigin_fn (mat);
  printf ("\nPrinting 'rastrigin_fn' output On Input of Matrix: \n");
  print_vector (result);  
}

void test_es_init_and_rastrigin (void)
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
  
  printf ("-- Printing Population Matrix -- \n");
  print_matrix (population);
  printf ("-- Printing Fitness Scores -- \n");
  print_vector (fitness_scores);
}