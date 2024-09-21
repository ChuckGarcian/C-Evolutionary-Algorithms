# Description: Block Optimization Benchmark Reference Implementations
# Source: Neurevolution, Mikulainen

import numpy as np

def lambda_alpha(x, alpha):
    dim = x.shape[-1]
    diag = np.power(alpha, 0.5 * np.arange(dim) / (dim - 1))
    return np.diag(diag)


def f_pen(x):
    return np.sum(np.square(np.maximum(0, np.abs(x) - 5)), axis=-1)


def t_osz(x):
    x_hat = np.where(x != 0, np.log(np.abs(x)), 0)
    c1 = np.where(x > 0, 10., 5.5)
    c2 = np.where(x > 0, 7.9, 3.1)
    return np.sign(x) * np.exp(x_hat + 0.049 * (np.sin(c1 * x_hat) +
                                                np.sin(c2 * x_hat)))


def t_asy(x, beta):
    dim = x.shape[-1]
    tmp = x.copy()
    tmp[tmp < 0] = 1
    power = np.where(
        x > 0, 1 + beta * np.arange(dim) / (dim - 1) * np.sqrt(tmp), 1)
    return np.power(x, power)


# === BBO Functions ===

def sphere_fn(x):
    z = x
    return np.sum(np.square(z), axis=-1)


def separable_ellipsoidal_fn(x):
    dim = x.shape[-1]
    z = t_osz(x)
    term1 = np.power(10, 6 * np.arange(dim) / (dim - 1))[None, ...]
    term2 = np.square(z)
    return np.sum(term1 * term2, axis=-1)


def rastrgin_fn(x):
    dim = x.shape[-1]    
    z = np.dot(t_asy(t_osz(x), 0.2), lambda_alpha(x, 10))
    term1 = 10 * (dim - np.sum(np.cos(2 * np.pi * z), axis=-1))
    term2 = np.sum(np.square(z), axis=-1)
    return term1 + term2

def dot (x, y):
    print (x)
    print (y)
    ref = np.dot (x, y)
    # act = np.tensordot (x, y, axes=([1], [0]))
    
    print (ref)
    # print (act)
    # assert (ref.all() == act.all())

def rastrigin_fn (x):
    sum = np.array ([0])
    dim = x.shape[-1]
    
    for ii in range(dim):
        xi = x[ii]
        sum = sum + (xi**2 - 10*np.cos(2*np.pi*xi))
    
    return 10*dim + sum

if __name__=="__main__":
  size1 = 3;
  size2 = 2;
  population = np.arange (size1*size2).reshape(size1, size2) + 1
  print ("Population: \n {}".format(population))
  
  fitness_scores = np.array(list(map(rastrigin_fn, np.array(population)))).T[0]
  print ("Fitness Scores: \n {}".format(fitness_scores))
