import numpy as np

def rastrigin_fn (x):
    sum = np.array ([0])
    dim = x.shape[-1]
    
    for ii in range(dim):
        xi = x[ii]
        sum = sum + (xi**2 - 10*np.cos(2*np.pi*xi))
    
    return 10*dim + sum

if __name__ == "__main__":
    # Extract Data and Calulate Reference Fitness
    population = np.genfromtxt("./population_mat.txt")
    act_fitness = np.genfromtxt("./act_fitness.txt")
    ref_fitness = np.array(list(map(rastrigin_fn, population))).T[0]
    
    # Calculate Fitness and Show Findings
    if not np.all(np.isclose(ref_fitness, act_fitness)):

        print ("--- Data ---")
        print ("Population: \n {}".format(population))
        print("Reference Fitness: \n {}".format(ref_fitness))
        print("Actual Fitness: \n {}".format(act_fitness))
        
        print ("--- Shape ---")
        print ("Population: \n {}".format(population.shape))
        print("Reference Fitness: \n {}".format(ref_fitness.shape))
        print("Actual Fitness: \n {}".format(act_fitness.shape))
        assert np.all(np.isclose(ref_fitness, act_fitness))
        

