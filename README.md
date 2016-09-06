# GMuNu

At the present moment, this simulation selects a set of previously created
N-Particle distributions as specified from the file "Distributions".  Each
N-Particle file should have the following columns:
    mass, body, temp, x, y, z, vx, vy, vz.

The simulation then instantiates the class<Particles> for each distribution
and through class<Interactions> allows for NxN interactions.  The
interactions involved is currently only point particle gravitational
interactions.

The simulation writes a set of output files, one for each input distribution per
time interval.  At any point, Animate.py can be run for the animation.  The
Animate.py script has a set of user variables that must be adjusted for the
output created during the simulation as specified in the files "Configs" and
"Distributions".

In the near future, there should be a particle distribution creator.  Instead of
initializing from previously created particle files, a distribution profile
would be created from a set of parameters.  The problem now is that the initial
velocities in the particle files may not agree with the units of the simulation
specified in the file "Configs".

The next change should be an interactions grid.  Instead of class<Interactions>
acting on one interaction at a time, an NxN grid would be created so that the
interactions could be parallelized.  The class<Interactions> would still take
care of units in the same way and calculate individual interactions.

A Quick Run
-----------

* Make sure all output directories from "Distributions" are made.
* Run GMuNu
* Make sure that Animate.py has the correct inputs.
* Type:  >> python Animate.py

Dependencies
------------

* python3
* numpy
* matplotlib
