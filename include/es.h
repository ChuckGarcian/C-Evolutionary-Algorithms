#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

/* Life Cycle */
void es_init (size_t pop_size, size_t num_params, gsl_vector *init_x,
             gsl_vector *stdev, long seed);
void es_terminate (void);

/* GA/ES Interface Convention */
gsl_matrix *es_ask (void);
void es_tell(gsl_vector *fitness);
