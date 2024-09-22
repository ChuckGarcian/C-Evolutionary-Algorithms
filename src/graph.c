#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <tensor/tensor.h>

#include "es.h"
#include "util.h"

gsl_vector *(*bbob_fn) (gsl_matrix *x);

gsl_matrix* vector_to_matrix(const gsl_vector *v);

static void optimize_and_write (void);
static void generate_graph (void);


int main (void)
{
  bbob_fn = &sphere_fn; // Function being Plotted
  
  int x_min = -5;
  int x_max = 5;
  int num_points_per_dim = 100;
    
  /* Setup vector and matrix Objects */  
  gsl_vector *x  = linspace (x_min, x_max, num_points_per_dim);
  gsl_matrix *tmp = gsl_matrix_alloc (num_points_per_dim, 2);
  gsl_matrix *x1 = gsl_matrix_alloc (num_points_per_dim, num_points_per_dim);
  gsl_matrix *x2 = gsl_matrix_alloc (num_points_per_dim, num_points_per_dim);
  gsl_matrix *y_res = gsl_matrix_alloc (num_points_per_dim, num_points_per_dim);
  meshgrid (x, x1, x2);
  
  /* Compute Graphing Data */
  for (int i = 0; i < num_points_per_dim; i++)
  {    
    gsl_vector *res_row;
    
    gsl_vector_view x1_row = gsl_matrix_subrow(x1, i, 0, num_points_per_dim);
    gsl_vector_view x2_row = gsl_matrix_subrow(x2, i, 0, num_points_per_dim); 
        
    gsl_matrix_set_col (tmp, 0, &x2_row.vector);
    gsl_matrix_set_col (tmp, 1, &x1_row.vector);
    
    res_row = bbob_fn (tmp);
    gsl_matrix_set_row (y_res, i, res_row);
    gsl_vector_free (res_row);
    
  }
  
  /* Save Graphing Data */  
  write_matrix (x1, "bin/x1.txt");
  write_matrix (x2, "bin/x2.txt");  
  write_matrix (y_res, "bin/y_res.txt");
  optimize_and_write ();
  
  /* Plot the Graphed Data */
  generate_graph ();
  
  printf ("Done -- Graph Saved\n");
  return 0;
}

/* Run ES Algorithm and Write Optimization Results */
void optimize_and_write (void)
{
  printf ("Initializing Now\n");

  int generations = 20;        // Num Optimization Time-steps
  size_t pop_size = 32;        // Population Size
  size_t num_params = 2;       // Number of Model Parameters
  long seed = 42;              // Seed for Random Functions    
  
  double init_x_arr[2] = {-4, -4};  // Initial Guess of Optimal
  double stdev_arr[2] = {.2, .20}; // Standard Deviation
  
  gsl_vector_view init_x = gsl_vector_view_array (init_x_arr, num_params);
  gsl_vector_view stdev = gsl_vector_view_array (stdev_arr, num_params);
    
  es_init (pop_size, num_params, &init_x.vector, &stdev.vector, seed);

  gsl_matrix *best = gsl_matrix_calloc(generations, num_params);

  for (int gen = 0; gen < generations; gen++)
  {
    // Develop Next Generation
    gsl_matrix *population = es_ask ();
    gsl_vector *fitness_scores = bbob_fn (population);
    es_tell (fitness_scores);
    
    // Store Results
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
  write_matrix (best, "bin/best_traj.txt");  
}

gsl_matrix* vector_to_matrix(const gsl_vector *v) {
    printf ("Size: %ld\n", v->size);
    gsl_matrix *m = gsl_matrix_alloc(v->size, 1);
    for (size_t i = 0; i < v->size; i++) {
        printf ("idx: %ld\n", i);
        gsl_matrix_set(m, i, 0, gsl_vector_get(v, i));
    }
    return m;
}

/* Plot Written Data */
void generate_graph (void)
{
  int ret = system("python3 src/plot.py");
  if (ret == -1)
  {
    fprintf(stderr, "Error starting Python script\n");
  }

}