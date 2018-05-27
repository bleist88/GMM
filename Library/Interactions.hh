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

public:

////////////////////////////////////////////////////////////////   M E T H O D S

private:

public:
    
    //  units

    void        set_time( double unit_t );
    void        set_length( double unit_l );
    void        set_mass( double unit_m );
    void        set_temperature( double unit_T );

    //  calculations

    void        calc_radial( Particle A, Particle B );

    //  interactions

    void        gravitate( Particles particles );
    void        collide( Particles particles );

//////////////////////////////////////////////////////////////////   O U T P U T

private:

public:

////////////////////////////////////////////////////////////////////////////////
};
#endif
