#include <rerun.hpp>
#include "plot_helper.hpp"

#include <math.h>

int main() {
    const rerun::RecordingStream rec = rerun::RecordingStream("plot_2d_example");
    rec.spawn().exit_on_failure();

    const size_t array_size = 100;
    std::array<rerun::Vec2D, array_size> vec2d;  
    std::array<rerun::Vec2D, array_size> another_vec2d;  

    for (size_t i = 0; i < array_size; i++) {
        float t = i * 0.01;
        float x = cos(2 * M_PI * t);
        float y = sin(2 * M_PI * t);

        std::array<float, 2> xy = {x, y};
        std::array<float, 2> yy = {y, y};

        vec2d[i] = xy;
        another_vec2d[i] = yy;
    };

    const auto strip =
    rerun::LineStrip2D(vec2d);
    const auto another_strip = 
        rerun::LineStrip2D(another_vec2d);

    std::string path {"strip"};
    rerun_viz::plot_2d(rec, path, vec2d); 

}
