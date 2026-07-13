#pragma once

#include <rerun.hpp>

namespace rerun_viz {

template <size_t N>
inline void plot_2d(const rerun::RecordingStream& rec, std::string path, const std::array<rerun::Vec2D, N>& data) {
    const auto data_2d = rerun::LineStrip2D(data);
    rec.log(path, rerun::LineStrips2D(data_2d));
};

}