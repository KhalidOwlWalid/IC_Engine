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
    float S = 2.04e-2;
    float a = S/2;
    float R = 8;
    float r = R * a;
    float U_p = 8.84;
    float N = 13000; // rpm
    float N_s = N / 60; // rps
    float U_p_calc = ice::average_piston_speed(S, N_s);

    std::vector<float> t = ice::linear_array(0.0f, 10.0f, (1/N_s)/50);

    spdlog::info("========= Engine Characteristics =========");
    spdlog::info(" Stroke length, S: {0}", S);
    spdlog::info(" Crank offset, a: {0}", a);
    spdlog::info(" Average piston speed calculated: {0} @ {1} rpm", U_p_calc, N);
    spdlog::info("==========================================");

    std::vector<float> piston_position;

    for (size_t i = 0; i < t.size(); i++) {
        float s = ice::piston_current_position(a, r, 360.0f * N_s * t[i]);
        piston_position.push_back(s);
    };

    std::string app_id {"engine_charateristics"};
    const rerun::RecordingStream& rec = rerun::RecordingStream(app_id);
    rec.spawn().exit_on_failure();

    rec.send_columns(
        "piston/position",
        rerun::TimeColumn::from_duration_secs("time", t),
        rerun::Scalars(std::move(piston_position)).columns()
    );

    return 0;
}