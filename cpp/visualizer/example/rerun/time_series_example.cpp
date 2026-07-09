#include <rerun.hpp>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>

#include <numeric>

std::string app_id {"Example_Visualizer"};

int main() {
    const rerun::RecordingStream rec = rerun::RecordingStream(app_id);
    rec.spawn().exit_on_failure();

    std::vector<double> sin_data(64);
    std::vector<double> cos_data(64);

    for (size_t i =0; i < 64; ++i) {
        sin_data[i] = sin(static_cast<double>(i) / 10.0);
        cos_data[i] = cos(static_cast<double>(i) / 10.0);
    }

    std::vector<int64_t> times(64);
    std::iota(times.begin(), times.end(), 0);

    rec.send_columns(
        "group1/sin",
        rerun::TimeColumn::from_sequence("step", times),
        // Please be wary of the following example use-case below whereby you are using std::move to perform "shallow copy"
        // hence when the next send_columns call comes in, times is already expired and no longer in memory which would cause a silent
        // crash
        // rerun::TimeColumn::from_sequence("step", std::move(times)),
        rerun::Scalars(std::move(sin_data)).columns()
    );

    rec.send_columns(
        "group1/cos",
        rerun::TimeColumn::from_sequence("step", times),
        rerun::Scalars(std::move(cos_data)).columns()
    );

}
