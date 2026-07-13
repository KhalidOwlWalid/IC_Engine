#pragma once

#include <rerun.hpp>

class EngineComponent {

    public:
        EngineComponent() {};
        virtual ~EngineComponent() {};

        virtual void update_component() = 0;
        virtual void log_component(const rerun::RecordingStream& rec) = 0;

};

class CylinderBaseShape : public EngineComponent {

    public:

        explicit CylinderBaseShape(std::string name, float length, float radius, rerun::components::Translation3D pivot_offset) :
         _name(name), _length(length), _radius(radius), _offset(pivot_offset) {
            _pivot_axis = rerun::datatypes::Vec3D{1.0f, 0.0, 0.0};
            set_rotation_axis_angle_deg(0.0);

            _cylinder_component = 
                rerun::Cylinders3D::from_lengths_and_radii(
                    {_length},
                    {_radius}
                ).with_centers(
                    {_offset}
                ).with_rotation_axis_angles(
                    {_rot_axis_angle}
                );

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

        void update_component() override {
            _cylinder_component = rerun::Cylinders3D::from_lengths_and_radii(
                {_length},
                {_radius}
            ).with_centers(
                {_offset}
            ).with_rotation_axis_angles(
                {_rot_axis_angle}
            );
        }

        void log_component(const rerun::RecordingStream& rec) override {
            _cylinder_component = rerun::Cylinders3D::from_lengths_and_radii(
                {_length},
                {_radius}
            ).with_centers(
                {_offset}
            ).with_rotation_axis_angles(
                {_rot_axis_angle}
            );

            rec.log(
                _name,
                _cylinder_component
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

        rerun::Cylinders3D _cylinder_component;
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