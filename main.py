#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.transforms as tf

import engine_lib.combustion_engine as ic_eng

def main():

    fig, ax = plt.subplots()
    ax.set_xlim(-1.0, 1.0)
    ax.set_ylim(-1.0, 1.0)
    ax.set_aspect("equal")


    # Shape properties
    width, height = 0.05, 0.3

    # Piston properties
    crank_offset = 0.2
    ra_ratio = 3
    connecting_rod_length = crank_offset * ra_ratio

    # Equation notation
    a = crank_offset
    r = connecting_rod_length
    theta_deg = 0
    theta_rad = np.deg2rad(theta_deg)

    # Connecting rod length bottom position
    x = a * np.cos(np.deg2rad(90) - theta_rad)
    y = a * np.sin(np.deg2rad(90) - theta_rad)

    # Current piston position from wrist axis
    s = ic_eng.get_current_piston_position(a, r, theta_rad)
    sin_alpha = s * np.sin(theta_rad) / r
    alpha = np.arcsin(sin_alpha)
    alpha = 0

    connecting_rod_coords = (x, y)
    connecting_rod_coords_with_offset = (x - width/2, y)
    connecting_rod = patches.Rectangle(connecting_rod_coords_with_offset, width, height, fill=True, rotation_point=connecting_rod_coords, angle=np.rad2deg(alpha))

    crank_pin_coords = (0, 0)
    crank_pin_coords_with_offset = (crank_pin_coords[0] - width/2, crank_pin_coords[1])
    crank_pin = patches.Rectangle(crank_pin_coords_with_offset, width, crank_offset, fill=True, color="red", rotation_point=(0, 0), angle=0)

    rod_path = patches.Circle((0, 0), radius=crank_offset, fill=False, linestyle="dashed")
    ax.add_patch(connecting_rod)
    ax.add_patch(crank_pin)
    ax.add_patch(rod_path)

    # Pivot point
    ax.scatter(0, 0)
    plt.show()

if __name__ == "__main__":
    main()
