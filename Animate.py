###   S i m u l a t i o n   A n i m a t i o n

import os
import numpy as np
from matplotlib import pyplot as mpl
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation

import Io

################################################################################

## User Variables.

box_size        = 2e12

interval        = 30
speed           = 5

distributions   = [
    "Output/Disk1/",
    "Output/Spheroid1/",
    "Output/Disk2/",
    "Output/Spheroid2/",
    "Output/Spheroid3/",
    ]

markers         = [
    "bo","yo","bo","yo","ro"
    ]

markersize      = 2
alpha           = .6

################################################################################

## Figure initialization.

fig         = mpl.figure()
ax          = fig.add_subplot( 111, projection='3d' )

ax.set_xlim3d( -box_size, box_size )
ax.set_ylim3d( -box_size, box_size )
ax.set_zlim3d( -box_size, box_size )

ax.set_axis_bgcolor('black')
ax.axis('off')

frames  = int( len(os.listdir(distributions[0]))/speed ) - 1

## Animation initialization.

points  = []

for i in range(len(distributions)):

    plot, = ax.plot(
        [],[],[], markers[i],
        markersize=markersize, alpha=alpha
        )

    points.append( plot )

def init():

    for i in range(len(distributions)):

        points[i].set_data([],[])
        points[i].set_3d_properties([])

    plots = points[0],
    for i in range(1,len(distributions)):
        plots += points[i],

    return plots

def animate(t):

    data    = [
        Io.read( dist + str(speed*t) + '.dat' ) for dist in distributions
        ]

    for i in range(len(data)):

        points[i].set_data( data[i]['x'], data[i]['y'] )
        points[i].set_3d_properties( data[i]['z'] )

    plots = points[0],
    for i in range(1,len(distributions)):
        plots += points[i],

    return plots

anime   = animation.FuncAnimation(
                fig, animate, init_func=init,
                frames=frames, interval=interval, #blit=True
                )

mpl.show()
