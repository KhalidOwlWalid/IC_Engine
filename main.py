#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.transforms as tf
import matplotlib.animation as animation

import engine_lib.combustion_engine as ic_eng

def main():

    fig, ax = plt.subplots()
    ax.set_xlim(-1.0, 1.0)
    ax.set_ylim(-1.0, 1.0)
    ax.set_aspect("equal")

    # Piston properties
    crank_offset = 0.2
    ra_ratio = 3
    connecting_rod_length = crank_offset * ra_ratio
    cr_width, cr_height = 0.05, connecting_rod_length
    cp_width, cp_height = 0.05, crank_offset

    # Equation notation
    a = crank_offset
    r = connecting_rod_length
    theta_deg = np.linspace(0, 360, 200)

    x, y = 0, a
    crank_pin_coords = (x, y)
    crank_pin_width_offset = (x - cr_width/2, y)
    connecting_rod = patches.Rectangle(crank_pin_width_offset, cr_width, cr_height, fill=True, rotation_point=crank_pin_coords, angle=0)

    crankshaft_center = (0, 0)
    crank_pin_coords_with_offset = (crankshaft_center[0] - cp_width/2, crankshaft_center[1])
    crank_pin = patches.Rectangle(crank_pin_coords_with_offset, cp_width, cp_height, fill=True, color="red", rotation_point=(0, 0), angle=0)

    rod_path = patches.Circle((0, 0), radius=crank_offset, fill=False, linestyle="dashed")

    ax.add_patch(connecting_rod)
    ax.add_patch(crank_pin)
    ax.add_patch(rod_path)

    # Pivot point
    crank_pin_dot = ax.scatter([], [])

    def init():
        crank_pin.set(xy=(0, 0), angle=0)
        connecting_rod.set(xy=(0 - cr_width/2, a))
        connecting_rod.rotation_point = (0, a)
        connecting_rod.angle = 0
        return (crank_pin, connecting_rod, crank_pin_dot)

    def update(frame):

        theta_rad = np.deg2rad(theta_deg[frame])

        # Connecting rod length bottom position
        x = a * np.cos(np.deg2rad(90) - theta_rad)
        y = a * np.sin(np.deg2rad(90) - theta_rad)

        # Current piston position from wrist axis
        alpha = np.arcsin((a/r) * np.sin(theta_rad))

        crank_pin_coords = (x, y)
        crank_pin_with_offset = (x - cr_width/2, y)
        crankshaft_center = (0 - cp_width/2, 0)

        crank_pin.set(xy=crankshaft_center, angle=-np.rad2deg(theta_rad))
        connecting_rod.set_xy(crank_pin_with_offset)
        connecting_rod.rotation_point = crank_pin_coords
        connecting_rod.angle = np.rad2deg(alpha)
        crank_pin_dot.set_offsets([crank_pin_coords[0], crank_pin_coords[1]])

        return (crank_pin, connecting_rod, crank_pin_dot)

    ani = animation.FuncAnimation(
        fig,
        update,
        frames=len(theta_deg),
        init_func=init,
        interval=1,
        blit=True,
        repeat=True,
    )

    plt.show()

if __name__ == "__main__":
    main()
