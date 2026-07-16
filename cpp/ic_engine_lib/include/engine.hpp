#pragma once

#include <math.h>
#include "common/math_utils.hpp"

namespace ice {

double stroke_length(double a);
double average_piston_speed(double S, double N);
double piston_current_position(double a, double r, double theta_deg);
double piston_speed_ratio(double R, double theta_deg);

}
