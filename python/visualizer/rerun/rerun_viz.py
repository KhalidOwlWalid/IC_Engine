#!/usr/bin/env python
import rerun as rr
import numpy as np
from datetime import datetime
import time
from rerun.datatypes import Vec3DArrayLike

from rerun import components

application_id = "ic_engine_app"
now = datetime.now()
curr_datetime = now.strftime("%d_%m_%Y-T%H_%M")
recording_id = f"ic_engine_{curr_datetime}"

class RerunArchetypeSpawner():

    def __init__(self):
        pass

    def spawn_into_canvas():
        pass

class RrBoxes3DWrapper(rr.Boxes3D, RerunArchetypeSpawner):
    """
        Parameters
        ----------
        sizes:
            Full extents in x/y/z. Specify this instead of `half_sizes`
        centers:
            Optional center positions of the boxes.
        rotation_axis_angles:
            Rotations via axis + angle.

            If no rotation is specified, the axes of the boxes align with the axes of the local coordinate system.
        colors:
            Optional colors for the boxes.
        fill_mode:
            Optionally choose whether the boxes are drawn with lines or solid.
        labels:
            Optional text labels for the boxes.
        show_labels:
            Optional choice of whether the text labels should be shown by default.
    """

    def __init__(self, *, log_path, sizes, centers, fill_mode, labels="", show_labels=False):
        super().__init__(
            sizes=sizes,
            centers=centers,
            # rotation_axis_angles=rotation_axis_angles,
            # colors=colors,
            fill_mode=fill_mode,
            labels=labels,
            show_labels=show_labels,
        )
        self.log_path = log_path

    def spawn():
        pass

    def clear():
        pass

class ConnectingRod:

    def __init__(self, log_path, sizes, centers, fill_mode=components.FillMode.Solid):
        self.log_path = log_path
        self.archetype = rr.Boxes3D(
            sizes=sizes,
            centers=centers,
            fill_mode=fill_mode,
        )

    def spawn(self):
        rr.log(
            self.log_path,
            self.archetype,
        )

def main():

    rr.init(
        application_id=application_id,
        recording_id=recording_id,
        spawn=True
    )

    rr.set_time("frame", sequence=0)

    # Log a box and points further down in the hierarchy.
    crank_radius = 0.05
    R = 5
    conrod_length = R * crank_radius
    conrod_width = 0.02

    a = crank_radius
    r = conrod_length
    test = ConnectingRod(
        log_path = "engine_comp/connecting_rod",
        sizes=[conrod_width, conrod_width, conrod_length],
        centers=[0, 0, conrod_length / 2],
    )
    test.spawn()

if __name__ == "__main__":

    main()
