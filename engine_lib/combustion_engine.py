import numpy as np
import matplotlib.pyplot as plt

def stroke_length(a):
    return 2 * a

def U_p_avg(a, N):
    S = stroke_length(a)
    return 2 * S * N

def get_current_piston_position(a, r, theta):
    # Distance s between crank axis and wrist pin axis
    s = a * np.cos(theta) + np.sqrt(np.power(r, 2) - np.power(a, 2) * np.power(np.sin(theta), 2))
    return s

def piston_speed_ratio(a, r, N, theta):
    R = r/a
    u_p_ratio = (np.pi / 2) * np.sin(theta) * (1 + (np.cos(theta)/np.sqrt(np.power(R, 2) - np.power(np.sin(theta), 2))))
    return theta, u_p_ratio

theta = np.linspace(0, 2 * np.pi, 200)
a = 0.02
r = 0.05
N = 3000
theta_rad, u_p_ratio = piston_speed_ratio(a, r, N, theta)

import matplotlib.patches as patches
import matplotlib.animation as animation
import matplotlib.transforms as tranforms

def main():
    fig, ax = plt.subplots()
    ax.set_xlim(left=0, right=1.0)
    ax.set_ylim(bottom=0, top=1.0)
    width, height = 0.1, 0.05
    block = patches.Rectangle((0.5, 0.5), width=width, height=height, fill=False, rotation_point="xy")
    block2 = patches.Rectangle((0.7, 0.5), width=width, height=height, fill=False, rotation_point="xy")
    ax.add_patch(block)
    ax.add_patch(block2)

    t = np.linspace(0, 2*np.pi, 200)

    def init():
        block.set(x=0.2)
        block2.set_y(0)
        return(block,block2,)

    def animate(frame):
        y = np.sin(t[frame])
        block.set_y(y - height/2)
        block2.set_y(y - height/2 + 0.2)
        return (block,block2,)

    ani = animation.FuncAnimation(
        fig,
        animate,
        frames=len(t),
        init_func=init,
        interval=30,
        blit=True,
        repeat=True,
    )

    plt.show()

if __name__ == "__main__":
    main()