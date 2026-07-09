from matplotlib.patches import Rectangle

class ComponentsBase(Rectangle):
    
    def __init__(self, width: float, length: float, bottom_coords: tuple):
        self.xy = bottom_coords
        self.width = width
        self.height = length

class ConnectingRodShaft(ComponentsBase):
    pass

class Crank(ComponentsBase):
    pass

class Piston(ComponentsBase):
    pass

class Cylinder(ComponentsBase):
    pass
