
from __imports__ import *

##  ============================================================================

out_dir = "Output/randy/"
i       = 2027

##  ============================================================================

T   = len( os.listdir( out_dir ) )

R   = np.zeros( T )
V   = np.zeros( T )
K   = np.zeros( T )

for t in range( T ):

    dat = Io.read( out_dir + str(t) + ".dat" )

    R[t]    = np.mean(
        np.sqrt( dat["x"]**2 + dat["y"]**2 + dat["z"]**2 )
    )

    V[t]    = np.mean(
        np.sqrt( dat["vx"]**2 + dat["vy"]**2 + dat["vz"]**2 )
    )

    K[t]    = np.mean(
        .5 * dat["mass"] * V[t]**2
    )

R   = R / np.max( R )
V   = V / np.max( V )
K   = K / np.max( K )

time    = np.arange( T )

pyplot.plot( time, R, "b" )
pyplot.plot( time, V, "g" )
pyplot.plot( time, K, "r" )
pyplot.ylim( 0, 1.1 )
pyplot.show()
