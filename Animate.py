###   S i m u l a t i o n   A n i m a t i o n

from astrolib.imports import *

#import os
#import numpy as np
#from matplotlib import pyplot as mpl
#from mpl_toolkits.mplot3d import Axes3D
#from matplotlib import animation

#import Io

################################################################################

## User Variables.

box_size        = 3e25

interval        = 85
step            = 1

color           = "black"
size            = 3
alpha           = 0.6

out_dir         = "Output/solar_system/"

################################################################################

##  determine box size again.

box_size        = 1.5 * np.max( io.read( out_dir + "0.dat" )["x"] )

## Figure initialization.

fig         = mpl.figure()
ax          = fig.add_subplot( 111, projection='3d' )

ax.set_xlim3d( -box_size, box_size )
ax.set_ylim3d( -box_size, box_size )
ax.set_zlim3d( -box_size, box_size )

ax.set_axis_bgcolor('white')
ax.axis('off')

plot  = ax.scatter3D( [], [], [], c=color, s=size, depthshade=False )

frames  = int( len(os.listdir(out_dir)) )

## Animation initialization.

def init():

    plot.set_data([],[])
    plot.set_3d_properties([])

    return plot

def animate(t):

    dat                 = io.read( out_dir + str(step * t) + ".dat" )

    plot._offsets3d     = ( dat["x"], dat["y"], dat["z"] )

    return  plot

anime   = animation.FuncAnimation(
            fig, animate, frames=frames, interval=interval #, blit=True
        )

# Set up formatting for the movie files
#Writer = animation.writers['ffmpeg']
#writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)
#anime.save( gif, writer="ffmpeg" )

mpl.show()
