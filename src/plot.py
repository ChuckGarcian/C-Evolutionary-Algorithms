import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import warnings
warnings.filterwarnings('ignore')

def plot_fn(name, traj=None,
            x_min=-5, x_max=5, num_levels=15, num_points_per_dim=100):    
    traj = np.genfromtxt ("src/best_traj.txt")
    x1 = np.genfromtxt ("src/x1.txt")
    x2 = np.genfromtxt ("src/x2.txt")
    y = np.genfromtxt ("src/y_res.txt")

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
    plt.savefig ("src/plot.png")

plot_fn ("rastrigin")    