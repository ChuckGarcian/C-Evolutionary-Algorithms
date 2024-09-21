#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

void es_init (size_t pop_size, size_t num_params, gsl_vector *init_x,
             float *stdev, long seed);
gsl_matrix *ask (void);
void *tell(gsl_vector *fitness);