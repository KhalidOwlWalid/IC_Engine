#pragma once

#include <math.h>
#include "common/math_utils.hpp"

float stroke_length(float a);
float average_piston_speed(float S, float N);
float piston_current_position(float a, float r, float theta_deg);
float piston_speed_ratio(float R, float theta_deg);
