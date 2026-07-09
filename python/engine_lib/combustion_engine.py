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

def piston_speed_ratio(a, r, theta):
    R = r/a
    u_p_ratio = (np.pi / 2) * np.sin(theta) * (1 + (np.cos(theta)/np.sqrt(np.power(R, 2) - np.power(np.sin(theta), 2))))
    return u_p_ratio
