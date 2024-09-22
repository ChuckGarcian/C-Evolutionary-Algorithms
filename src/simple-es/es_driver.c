#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include "simple_es.h"
#include "graph.h"
#include "util.h"

void run_es_algorithm(int generations, size_t num_params, gsl_matrix *best);

gsl_vector *(*bbob_fn)(gsl_matrix *x);

int main(void)
{
    printf("Starting 'Simple-es' Now\n");

    // Initialize Training Parameters 
    bbob_fn = sphere_fn;   // Black Box Function
    int generations = 20;  // Num Optimization Time-steps
    size_t pop_size = 32;  // Population Size
    size_t num_params = 2; // Number of Model Parameters
    long seed = 42;        // Seed for Random Functions

    double init_x_arr[2] = {-4, -4}; // Initial Guess of Optimal
    double stdev_arr[2] = {.2, .20}; // Standard Deviation

    gsl_vector_view init_x = gsl_vector_view_array(init_x_arr, num_params);
    gsl_vector_view stdev = gsl_vector_view_array(stdev_arr, num_params);

    es_init(pop_size, num_params, &init_x.vector, &stdev.vector, seed);
    
    print_vector (&init_x.vector);
    gsl_matrix *best = gsl_matrix_calloc(generations, num_params);

    // Train using ES Algorithm
    run_es_algorithm(generations, num_params, best);
    
    // Write and Graph Results
    write_matrix(best, "bin/best_traj.txt");
    gen_bbob_data(bbob_fn);
    graph_data();

    gsl_matrix_free(best);

    return 0;
}

void run_es_algorithm(int generations, size_t num_params, gsl_matrix *best)
{
    for (int gen = 0; gen < generations; gen++)
    {
        // Develop Next Generation
        gsl_matrix *population = es_ask();
        gsl_vector *fitness_scores = bbob_fn(population);
        es_tell(fitness_scores);

        // Store Results
        size_t best_idx = gsl_vector_min_index(fitness_scores);
        printf("Gen=%d,\t(", gen + 1);

        // Store each parameter of the best individual
        for (int i = 0; i < num_params; i++)
        {
            double param_i = gsl_matrix_get(population, best_idx, i);
            printf("x%d=%g,", i, param_i);
            gsl_matrix_set(best, gen, i, param_i);
        }
        printf("),\tfit=%g", gsl_vector_get(fitness_scores, best_idx));
        printf("\n");

        gsl_vector_free(fitness_scores);
    }
}