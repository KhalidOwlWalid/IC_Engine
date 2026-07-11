#include <rerun.hpp>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>

#include <numeric>

std::string app_id {"engine_3d_model"};

int main() {
    const rerun::RecordingStream rec = rerun::RecordingStream(app_id);
    rec.spawn().exit_on_failure();

    std::vector<double> timestamp;
    constexpr double start_time = 0;
    constexpr double stop_time = 5;
    constexpr double timestep = 0.01;
    constexpr size_t n = static_cast<size_t>(std::ceil((stop_time - start_time)/timestep));
    timestamp.reserve(n);

    for (size_t i = 0; i < n; i++) {
        timestamp.push_back(start_time + i * timestep);
    }

    // TODO: Draw piston, conrod, and crankshaft and publish it onto rerun 3d model
    // Let it perform a circular motion to show that it can work as a base example of our engine_lib functionality
    double cyl_size = 0;
    for (size_t i = 0; i < n; i++) {
        rec.set_time_duration_secs("time", timestamp[i]);
        rec.log(
            "cylinders",
            rerun::Cylinders3D::from_lengths_and_radii(
                {cyl_size + static_cast<double>(i)},
                {cyl_size + static_cast<double>(i) * 0.05}
            )
        );
    }
};