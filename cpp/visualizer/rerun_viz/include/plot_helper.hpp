#pragma once

#include <rerun.hpp>

namespace ice::rerun_viz {

template <size_t N>
inline void plot_2d(const rerun::RecordingStream& rec, std::string path, const std::array<rerun::Vec2D, N>& data) {
    const auto data_2d = rerun::LineStrip2D(data);
    rec.log(path, rerun::LineStrips2D(data_2d));
};

template <typename T>
inline void plot_time_series(const rerun::RecordingStream& rec, const std::string& path, const rerun::TimeColumn& t_column, const std::vector<T>& data) {
    rec.send_columns(
        path,
        t_column,
        rerun::Scalars(data).columns()
    );
};

inline rerun::Cylinders3D create_cylinder(float length, float radius, std::array<float, 3> centers, std::array<float, 3> rot_axis, float rot_angle_deg) {
    return std::move(rerun::Cylinders3D::from_lengths_and_radii(
        {length},
        {radius}
    ).with_centers(
        {centers}
    ).with_rotation_axis_angles(
        {rerun::RotationAxisAngle(
            rot_axis,
            rerun::Angle::degrees(rot_angle_deg)
        )}
    ));
};

}