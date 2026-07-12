#include <rerun.hpp>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>

#include <numeric>

std::string app_id {"engine_3d_model"};

class CylinderBaseShape {

    public:

        explicit CylinderBaseShape(std::string name, float length, float radius, rerun::components::Translation3D pivot_offset) :
         _name(name), _length(length), _radius(radius), _offset(pivot_offset) {
            _pivot_axis = rerun::datatypes::Vec3D{1.0f, 0.0, 0.0};
            set_rotation_axis_angle_deg(0.0);
         };

        virtual ~CylinderBaseShape() = default;

        void set_rotation_axis_angle_deg(const float angle_deg) {
            _rot_axis_angle = rerun::RotationAxisAngle(
                _pivot_axis,
                rerun::Angle::degrees(angle_deg)
            );
        };

        void set_offset(const rerun::components::Translation3D& offset) {
            _offset = offset;
        }

        rerun::Cylinders3D get_component() {
            rerun::Cylinders3D cylinder = rerun::Cylinders3D::from_lengths_and_radii(
                {_length},
                {_radius}
            ).with_centers(
                {_offset}
            ).with_rotation_axis_angles(
                {_rot_axis_angle}
            );
            return cylinder;
        }

        void log_cylinder_shape(const rerun::RecordingStream& rec) {
            rerun::Cylinders3D cylinder = rerun::Cylinders3D::from_lengths_and_radii(
                {_length},
                {_radius}
            ).with_centers(
                {_offset}
            ).with_rotation_axis_angles(
                {_rot_axis_angle}
            );

            rec.log(
                _name,
                cylinder
            );
        };

    protected:
        rerun::Vec3D _pivot_axis; // Pivot should be fixed with respect to the pivot point of the component itself
        rerun::RotationAxisAngle _rot_axis_angle;
        rerun::components::Translation3D _offset;

        float _angle_deg {0};
        float _length;
        float _radius;
        float _pivot_offset;
        std::string _name;
};

class PistonHead: public CylinderBaseShape {
    public:
        PistonHead(float length, float radius, rerun::components::Translation3D pivot_offset) :
            CylinderBaseShape("engine_comp/piston_head", length, radius, pivot_offset) {}

        ~PistonHead() = default;
};

class ConnectingRod: public CylinderBaseShape {
   public:
        ConnectingRod(float length, float radius, rerun::components::Translation3D pivot_offset) :
            CylinderBaseShape("engine_comp/connecting_rod", length, radius, pivot_offset) {}

        ~ConnectingRod() = default;
};

class Journal: public CylinderBaseShape {
   public:
        Journal(float length, float radius, rerun::components::Translation3D pivot_offset) :
            CylinderBaseShape("engine_comp/journal", length, radius, pivot_offset) {}

        ~Journal() = default;
};

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

    float R = 3;        // R = r/a
    float a = 0.02;     // Length of the crankshaft pin to the crankshaft center
    float r = R * a;    // Length of the connecting rod
    float l_ph = 0.04;  // Length of the cylinder head
    float r_ph = 0.1;   // Radius of the piston head

    rerun::components::Translation3D pivot_offset;

    pivot_offset = rerun::datatypes::Vec3D{0.0f, 0.0f, a/2};
    Journal journal(a, 0.01, pivot_offset);

    pivot_offset = rerun::datatypes::Vec3D{0.0f, 0.0f, a + r/2};
    ConnectingRod connecting_rod(r, 0.01, pivot_offset);

    pivot_offset = rerun::datatypes::Vec3D{0.0f, 0.0f, r + a + l_ph/2};
    PistonHead piston_head(l_ph, r_ph, pivot_offset);

    rec.set_time_duration_secs("time", 0);
    journal.log_cylinder_shape(rec);
    connecting_rod.log_cylinder_shape(rec);
    piston_head.log_cylinder_shape(rec);

    // rec.log(
    //     "whatever",
    //     journal.get_component()
    //     connecting_rod.get_component(),
    //     piston_head.get_component()
    // );


    // TODO: Draw piston, conrod, and crankshaft and publish it onto rerun 3d model
    // Let it perform a circular motion to show that it can work as a base example of our engine_lib functionality
    // double cyl_size = 0;
    // double rotation_angle_deg = 0;
    // for (size_t i = 0; i < n; i++) {
    //     rec.set_time_duration_secs("time", timestamp[i]);
    //     piston_head.log_cylinder_shape(rec);
    //     rec.log(
    //         "cylinder_1",
    //         rerun::Cylinders3D::from_lengths_and_radii(
    //             {cyl_size + static_cast<double>(i)},
    //             {cyl_size + static_cast<double>(i) * 0.05}
    //         ).with_rotation_axis_angles({
    //             rerun::RotationAxisAngle(
    //                 {1.0f, 0.0, 0.0},
    //                 rerun::Angle::degrees(rotation_angle_deg + static_cast<double>(i))
    //             )
    //         })
 
    //     );
    //     float xyz[3] = {10.0f, 10.0f, 0.0};
    //     rec.log(
    //         "cylinder_2",
    //         rerun::Cylinders3D::from_lengths_and_radii(
    //             {cyl_size + static_cast<double>(i)},
    //             {cyl_size + static_cast<double>(i) * 0.05}
    //         ).with_rotation_axis_angles({
    //             rerun::RotationAxisAngle(
    //                 {1.0f, 0.0, 0.0},
    //                 rerun::Angle::degrees(rotation_angle_deg + static_cast<double>(i))
    //             )
    //         }).with_centers(
    //             rerun::components::Translation3D(xyz)
    //         )
    //     );
    // }
};