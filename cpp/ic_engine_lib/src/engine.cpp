#include "engine.hpp"

float stroke_length(float a) {
    return 2 * a;
};

float average_piston_speed(float S, float N) {
    return 2 * S * N;
}

float piston_current_position(float a, float r, float theta_deg) {
    return a * cos(ice::deg2rad(theta_deg)) + sqrt(pow(r, 2) - pow(a, 2) * pow(sin(ice::deg2rad(theta_deg)), 2));
}

float piston_speed_ratio(float R, float theta_deg) {
    return (M_PI / 2) * sin(ice::deg2rad(theta_deg)) * (1 + cos(ice::deg2rad(theta_deg)) / sqrt(pow(R, 2) - pow(sin(ice::deg2rad(theta_deg)), 2)));
}
