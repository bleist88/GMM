#ifndef INTERACTIONS_HH
#define INTERACTIONS_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "Vector.hh"
#include "Vectors.hh"
#include "Particle.hh"
#include "Particles.hh"

////////////////////////////////////////////////////////////////////////////////

class Interactions
{

//////////////////////////////////////////////////////   C O N S T R U C T O R S

public:

    Interactions();
    virtual ~Interactions();

////////////////////////////////////////////////////////////////   M E M B E R S

private:

    // Unit Dimensions.

    double      _unit_t;        // time         - seconds
    double      _unit_l;        // length       - meters
    double      _unit_m;        // mass         - kilograms
    double      _unit_T;        // temperature  - kelvin

    // Physical Constants.

    double      _G;             // Gravitational    -   [L3]/[M][t2]
    double      _k;             // Boltzmann's      -   [L2][M]/[t2][T]
    double      _R;             // Resistance       -   1/[L3]

    // Variables.

    Vector      _radial;
    Vector      _acceleration;
    double      _mass_a, _mass_b;
    double      _bump_a, _bump_b;

public:

////////////////////////////////////////////////////////////////   M E T H O D S

private:

public:

    // Calculations.

    void        calc_radial( Particle A, Particle B );
    void        calc_masses( Particle A, Particle B );
    void        calc_bumps( Particle A, Particle B );

    // Interactions.

    void        gravitate( Particles A, Particles B );
    void        collide( Particles A, Particles B );

    // Scaling units.

    void        scale_time( double factor );
    void        scale_length( double factor );
    void        scale_mass( double factor );
    void        scale_temperature( double factor );

//////////////////////////////////////////////////////////////////   O U T P U T

private:

public:

////////////////////////////////////////////////////////////////////////////////
};
#endif
