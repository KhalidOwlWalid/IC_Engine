import numpy as np

import sys
sys.path.append("/home/khalidowlwalid/Documents/notes/combustion_engine_fundamentals/ipython_notebooks")
from engine_lib import combustion_engine as ic_eng

import matplotlib.pyplot as plt
from engine_lib import theme
from itertools import cycle

theme.use()

fig, ax = plt.subplots()
R_setup = [3, 6, 10]
marker_opts = cycle(["o", "s", "^", "v", "P"])

for i, R in enumerate(R_setup):
    # Piston properties
    crank_offset = 0.2
    # R = 3 # r/a ration
    connecting_rod_length = crank_offset * R
    cr_width, cr_height = 0.05, connecting_rod_length
    cp_width, cp_height = 0.05, crank_offset

    # Equation notation
    a = crank_offset
    r = connecting_rod_length
    theta_deg = np.linspace(0, 360, 50)

    Up_ratio = ic_eng.piston_speed_ratio(a, r, np.deg2rad(theta_deg))

    ax.plot(theta_deg, Up_ratio, marker=next(marker_opts), label=f"R: {R}")
    ax.set(xlabel="Theta (deg)", ylabel="Up_ratio")


plt.grid()
plt.legend()
plt.show()
