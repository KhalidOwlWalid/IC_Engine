#include <rerun.hpp>
#include "engine.hpp"
#include "engine_component.hpp"
#include "plot_helper.hpp"
#include "common/utils.hpp"
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ranges.h>
#include <iostream>
#include <math.h>

int main() {
    // init_piston();
    // init_piston_visualizer();

    // Piston characteristics
    double S = 2.04e-2;
    double a = S/2;
    double R = 8;
    double r = R * a;
    double U_p = 8.84;
    double N = 13000; // rpm
    double N_s = N / 60; // rps (also Hz)
    double U_p_calc = ice::average_piston_speed(S, N_s);

    double start = 0;
    double stop = 1.0;
    double step = (1/N_s)/50;
    std::vector<double> t = ice::linear_array(start, stop, step);

    std::vector<rerun::components::Translation3D> journal_centers;
    std::vector<rerun::components::RotationAxisAngle> journal_rotations;
    journal_centers.reserve(t.size());
    journal_rotations.reserve(t.size());

    std::vector<rerun::components::Translation3D> conrod_centers;
    std::vector<rerun::components::RotationAxisAngle> conrod_rotations;
    conrod_centers.reserve(t.size());
    conrod_rotations.reserve(t.size());

    spdlog::info("========= Engine Characteristics =========");
    spdlog::info(" Stroke length, S: {0}", S);
    spdlog::info(" Crank offset, a: {0}", a);
    spdlog::info(" Average piston speed calculated: {0} @ {1} rpm", U_p_calc, N);
    spdlog::info("==========================================");

    std::vector<double> piston_position;

    std::string app_id {"engine_charateristics"};
    const rerun::RecordingStream& rec = rerun::RecordingStream(app_id);
    rec.spawn().exit_on_failure();

    for (size_t i = 0; i < t.size(); i++) {
        // Multiply by N_s since this is amount of cycles per second
        double s = ice::piston_current_position(a, r, 360.0 * N_s * t[i]);
        piston_position.push_back(s);

        double inc = i * 0.01;

        journal_centers.push_back({0.0f, 0.0f, static_cast<float>(a/2)});
        journal_rotations.push_back(rerun::RotationAxisAngle({1.0f, 0.0f, 0.0f}, rerun::Angle::degrees(0.0f + inc)));

        conrod_centers.push_back({0.0f, 0.0f, static_cast<float>(a + r/2)});
        conrod_rotations.push_back(rerun::RotationAxisAngle({1.0f, 0.0f, 0.0f}, rerun::Angle::degrees(0.0f + inc)));
    };

    std::string path_name {"piston/position"};
    const rerun::TimeColumn t_column = rerun::TimeColumn::from_duration_secs("time", t);
    ice::rerun_viz::plot_time_series(rec, path_name, t_column, std::move(piston_position));

    // Constant geometry logged once; only centers/rotations vary per timestep
    rec.log_static("piston/journal_comp", rerun::Cylinders3D::from_lengths_and_radii({(float)a}, {0.01f}));
    rec.log_static("piston/conrod_comp", rerun::Cylinders3D::from_lengths_and_radii({(float)r}, {0.01f}));

    rerun::Collection<rerun::ComponentColumn> journal_columns = rerun::Cylinders3D()
        .with_centers(journal_centers)
        .with_rotation_axis_angles(journal_rotations)
        .columns();

    rerun::Collection<rerun::ComponentColumn> conrod_columns = rerun::Cylinders3D()
        .with_centers(conrod_centers)
        .with_rotation_axis_angles(conrod_rotations)
        .columns();

    rec.send_columns("piston/journal_comp", t_column, journal_columns);
    rec.send_columns("piston/conrod_comp", t_column, conrod_columns);

    return 0;
}
