#include <rerun.hpp>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>

#include <numeric>

std::string app_id {"Example_Visualizer"};

class VisualizerBase {

    public:
        VisualizerBase() = default;
        ~VisualizerBase() = default;

        virtual bool init_visualizer();
        virtual void plot_time_series();
};

class RerunVisualizer: public VisualizerBase {

    RerunVisualizer();
    ~RerunVisualizer();

    bool init_visualizer() override;
    void plot_time_series() override;

};

int main() {
    const rerun::RecordingStream rec = rerun::RecordingStream(app_id);
    rec.spawn().exit_on_failure();

    std::vector<double> scalar_data(64);

    for (size_t i =0; i < 64; ++i) {
        scalar_data[i] = sin(static_cast<double>(i) / 10.0);
    }

    std::vector<int64_t> times(64);
    std::iota(times.begin(), times.end(), 0);

    rec.send_columns(
        "scalars",
        rerun::TimeColumn::from_sequence("step", std::move(times)),
        rerun::Scalars(std::move(scalar_data)).columns()
    );

}
