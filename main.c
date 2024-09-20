#include <stdio.h>
#include <assert.h>
#include <tensor/tensor.h>

// https://numbbo.github.io/gforge/downloads/download16.00/bbobdocfunctions.pdf#page=15

void rastrigin_fn (tensor *tn)
{
  
  printf ("tn\n\n");
}

int main (void)
{
  
  tensor *t = tensor_alloc (3, 2, 3, 4);
  printf ("stride[2]: %d \n", t->stride[0]);
  // tensor_set_al (t, )
  // print_tensor (t);
  // tensor_set_one (t);
  
  printf ("Element's sum: %g\n", tensor_sum (t));
  tensor_free (t);
  return  0;
}

/**
 * This function returns the "true/physical" memory index of the i'th
 * consecutive element along a logical memory layout along 'axis' of tensor 't'.
 * In other words, if tensor 't' were stored along 'axis' such that the
 * underlying data is a flat array, then i represents the i'th element in the
 * flattened array -- the physical index is then returned.
 */
int index_along_axis (const tensor *t, const size_t i, const size_t axis)
{
  assert (t->dim < axis);
  
  int idx, tmp;
  
  tmp = i * t->stride[axis];
  idx = tensor_index (t, tmp);
/*
012 a00
34a 000
678 000

In this case: a = 1, axis=2


                                            How far into the request dimension
idx = t.stride[axis-1](a % t.stride[axis]) + (a // t.stride[axis])
          Number of complete leading Dimensions

*/
  return idx;
}

void print_tensor (const tensor * t)
{        
  for (int i = 0; i < t->size[0]; ++i)
    {
      printf ("Dim: %d \n", t->dim);
      for (int j = 0; j < t->size[1]; ++j)
      printf (" \n");
    }
}
