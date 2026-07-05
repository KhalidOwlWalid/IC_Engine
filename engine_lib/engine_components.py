import matplotlib.patches as patches

def piston_head(xy=(0, 0), width=0.05, height=0.05):
    block = patches.Rectangle(xy=xy, width=width, height=height, fill=False)
    return block

def connecting_rod(length=0.15):
    # block = patches.Rectangle(xy=xy, width=width, height=height, fill=False)
    # return block
    pass

def cylinder():
    # Draw rectangle with no border
    pass
