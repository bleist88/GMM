"""
This file is used to adjust the velocities of objects so that they may orbit.
This does nothing more but rescales the current velocity according to what the
tangential velocity would be in order to have a circular orbit.  It does not,
however, adjust the direction of velocity.
"""

from    __imports__ import *

################################################################################
################################################################################

files   = [
    "disk.dat", "randy.dat", "randy_disk.dat"
]

G       = 6.67e-11
Av      = 1

unit_t  = 1e14            # s     -> 10*Myr = 6.14e13
unit_l  = 3.10e16         # m     -> pc
unit_m  = 1.989e30         # kg    -> solar

################################################################################

##  read in file

for f in files:

    ##  read in the file.

    print( "Reading in " + f + "..." )

    dat = Io.read( f )

    ##  calculate total mass of the system.
    ##  adjust for mass unit.

    M   = unit_m * np.sum( dat["mass"] )

    ##  calculate the magnitude of tangential velocity for each particle.

    r   = unit_l * np.sqrt( dat["x"]**2 + dat["y"]**2 + dat["z"]**2 )
    v   = np.sqrt( G * M / r )

    ##  calculate the current velocity.
    ##  scale the velocity to give the velocity above.
    ##  v   = a * V     =>      a   = v / V

    dat["vx"]   *=  Av * np.sqrt( np.random.rand( dat.size ) * v**2 )
    dat["vy"]   *=  Av * np.sqrt( np.random.rand( dat.size ) * ( v**2 - dat["vx"]**2 ) )
    dat["vz"]   *=  Av * ( 1 / dat["z"] ) * ( dat["x"] * dat["vx"] + dat["y"] * dat["vy"] )

    ##  write the file.

    Io.write( f, dat )

    print( "...done.")
