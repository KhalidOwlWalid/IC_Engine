#include <rerun.hpp>

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