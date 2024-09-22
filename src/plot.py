import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import warnings
warnings.filterwarnings('ignore')

def plot_fn(name, traj=None,
            x_min=-5, x_max=5, num_levels=15, num_points_per_dim=100):    
    data_dir = "bin"
    traj = np.genfromtxt ("{}/best_traj.txt".format(data_dir))
    x1 = np.genfromtxt ("{}/x1.txt".format(data_dir))
    x2 = np.genfromtxt ("{}/x2.txt".format(data_dir))
    y = np.genfromtxt ("{}/y_res.txt".format(data_dir))

    fig = plt.figure(figsize=plt.figaspect(.5))

    # Plot the function.
    ax = fig.add_subplot(1, 2, 1, projection="3d")
    ax.plot_surface(x1, x2, y, cmap='coolwarm', linewidth=0, antialiased=False)
    ax.set_xlabel("$x_1$")
    ax.set_ylabel("$x_2$")
    ax.set_zlabel("$y$")
    ax.set_xlim([x_min, x_max])
    ax.set_ylim([x_min, x_max])
    ax.set_title(name.replace("_", " "))

    # Plot the contour.
    ax = fig.add_subplot(1, 2, 2)
    quantiles = (np.arange(num_levels + 2) / (num_levels + 1))[1:-1]
    ax.contour(x1, x2, y, np.quantile(y, quantiles))
    title = "Contour"
    if traj is not None:
        traj_len = traj.shape[0]
        alphas = np.linspace(0.1, 1, traj_len)
        for i in range(traj_len):
            ax.scatter(traj[i, 0], traj[i, 1],
                       color='black', marker="o", s=100, alpha=alphas[i])
        title += " & Optimization Trajectory"

    ax.set_xlim([x_min, x_max])
    ax.set_ylim([x_min, x_max])
    ax.set_title(title)

    plt.tight_layout()
    plt.savefig ("{}/plot.png".format(data_dir))

plot_fn ("rastrigin")    