import matplotlib as mpl

def use():
    mpl.rcParams.update({
        "figure.facecolor": "#1e1e1e",
        "figure.edgecolor": "#1e1e1e",
        "axes.facecolor":   "#252525",
        "axes.edgecolor":   "#3a3a3a",
        "axes.labelcolor":  "#d4d4d4",
        "axes.prop_cycle":  mpl.cycler(color=[
            "#268bd2", "#2aa198", "#859900", "#b58900",
            "#cb4b16", "#dc322f", "#d33682", "#6c71c4",
        ]),
        "axes.grid": True,
        "xtick.color":      "#6e6e6e",
        "ytick.color":      "#6e6e6e",
        "grid.color":       "#d4d4d4",
        "grid.linestyle":   "--",
        "grid.alpha":       0.4,
        "text.color":       "#d4d4d4",
        "legend.facecolor": "#252525",
        "legend.edgecolor": "#3a3a3a",
    })
