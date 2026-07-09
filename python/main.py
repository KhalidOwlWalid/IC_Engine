#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.transforms as tf
import matplotlib.animation as animation
import matplotlib.gridspec as gridspec

import engine_lib.combustion_engine as ic_eng
from engine_lib import theme

def main():

    theme.use()

    # piston_fig, (piston_ax, u_avg_plot_ax) = plt.subplots(
    #     1, 2,
    #     figsize=(10, 6),
    #     gridspec_kw={"width_ratios": [1, 3]},
    #     constrained_layout=True,
    # )

    piston_fig = plt.figure(figsize=(12, 6)) 
    gs = gridspec.GridSpec(2, 2, width_ratios=[1, 4])

    piston_ax = piston_fig.add_subplot(gs[:, 0])
    u_avg_plot_ax = piston_fig.add_subplot(gs[0, 1])
    u_plot_ax = piston_fig.add_subplot(gs[1, 1])

    piston_ax.set_xlim(-0.3, 0.3)
    piston_ax.set_ylim(-0.3, 1.5)
    piston_ax.set_aspect("equal")

    # Piston properties
    crank_offset = 0.05
    R = 5
    N = 5200 # rpm
    connecting_rod_length = crank_offset * R
    cr_width, cr_height = crank_offset/2, connecting_rod_length
    cp_width, cp_height = crank_offset/2, crank_offset

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

    rod_path = patches.Circle((0, 0), color="white", radius=crank_offset, fill=False, linestyle="dashed")

    piston_ax.add_patch(connecting_rod)
    piston_ax.add_patch(crank_pin)
    piston_ax.add_patch(rod_path)

    Up_ratio = ic_eng.piston_speed_ratio(a, r, np.deg2rad(theta_deg))

    u_avg_plot_ax.plot(theta_deg, Up_ratio)
    u_avg_plot_ax.set(xlabel="theta (deg)", ylabel="U_p ratio")
    u_avg_plot_ax.grid()
    Up_ratio_marker_dot = u_avg_plot_ax.scatter([], [])

    Up_average = ic_eng.U_p_avg(a, 5200/60)
    Up = Up_ratio * Up_average
    u_plot_ax.plot(theta_deg, Up)
    u_plot_ax.set(xlabel="theta (deg)", ylabel="Up (m/s)")
    u_plot_ax.grid()
    Up_marker_dot = u_plot_ax.scatter([], [])

    # Pivot point
    crank_pin_dot = piston_ax.scatter([], [])

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
        Up_ratio_marker_dot.set_offsets([theta_deg[frame], Up_ratio[frame]])
        Up_marker_dot.set_offsets([theta_deg[frame], Up[frame]])

        return (crank_pin, connecting_rod, crank_pin_dot, Up_ratio_marker_dot, Up_marker_dot)

    ani = animation.FuncAnimation(
        piston_fig,
        update,
        frames=len(theta_deg),
        init_func=init,
        interval=17,
        blit=True,
        repeat=True,
    )

    # ani.save("/home/khalidowlwalid/Documents/notes/combustion_engine_fundamentals/Concepts/blobs/R_comparison/R_3.mp4")
    u_avg_plot_ax.grid()
    u_avg_plot_ax.legend()

    u_plot_ax.grid()
    u_plot_ax.legend()
    plt.show()


if __name__ == "__main__":
    main()
