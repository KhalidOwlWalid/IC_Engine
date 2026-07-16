#include "engine.hpp"

namespace ice {

double stroke_length(double a) {
    return 2 * a;
};

double average_piston_speed(double S, double N) {
    return 2 * S * N;
}

double piston_current_position(double a, double r, double theta_deg) {
    return a * cos(ice::math::deg2rad(theta_deg)) + sqrt(pow(r, 2) - pow(a, 2) * pow(sin(ice::math::deg2rad(theta_deg)), 2));
}

double piston_speed_ratio(double R, double theta_deg) {
    return (M_PI / 2) * sin(ice::math::deg2rad(theta_deg)) * (1 + cos(math::deg2rad(theta_deg)) / sqrt(pow(R, 2) - pow(sin(ice::math::deg2rad(theta_deg)), 2)));
}

}
