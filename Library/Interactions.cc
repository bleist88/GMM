#include "../Include/Interactions.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "../Include/Vector.hh"
#include "../Include/Vectors.hh"
#include "../Include/Particle.hh"
#include "../Include/Particles.hh"

//////////////////////////////////////////////////////   C O N S T R U C T O R S

Interactions :: Interactions()
{
    _unit_t         = 1.0;              // seconds
    _unit_l         = 1.0;              // meters
    _unit_m         = 1.0;              // kilograms
    _unit_T         = 1.0;              // kelvin

    _G              = 6.674e-11;        // [L3]/[M][t2]
    _k              = 1.381e-23;        // [L2][M]/[t2][T]
    _R              = 1;                // 1/[L3]
}

Interactions :: ~Interactions(){};

////////////////////////////////////////////////////////////////   M E M B E R S


////////////////////////////////////////////////////////////////   M E T H O D S

// Calculations.

void        Interactions :: calc_radial( Particle A, Particle B )
{
    _radial     = B.position().subtracted( A.position() );
}

void        Interactions :: calc_masses( Particle A, Particle B )
{
    _mass_a     = A.mass() * exp( -pow(_radial.mag()/A.body(),2) );
    _mass_b     = B.mass() * exp( -pow(_radial.mag()/B.body(),2) );
}

void        Interactions :: calc_bumps( Particle A, Particle B )
{
    _bump_a     = pow( _mass_a / A.mass(), 3 );
    _bump_b     = pow( _mass_b / B.mass(), 3 );
}

// Interactions.

void        Interactions :: gravitate( Particles A, Particles B )
{
    for( int i = 0; i < A.size(); i++ ){
        for( int j = 0; j < B.size(); j++ ){

            calc_radial( A.particle(i), B.particle(j) );
            calc_masses( A.particle(i), B.particle(j) );

            if( _radial.mag() > 0.0 ){

                _radial.scale( _G / pow(_radial.mag(),3) );

                A.acceleration(i).add( _radial.scaled( _mass_b ) );
                B.acceleration(j).add( _radial.scaled( _mass_a ) );

            };
        };
    };
}

void        Interactions :: collide( Particles A, Particles B )
{
    for( int i = 0; i < A.size(); i++ ){
        for( int j = 0; j < B.size(); j++ ){

            calc_radial( A.particle(i), B.particle(j) );
            calc_masses( A.particle(i), B.particle(j) );

            A.acceleration(i).add( B.velocity(j).scaled(_bump_b/_unit_t) );
            B.acceleration(j).add( B.velocity(i).scaled(_bump_b/_unit_t) );

        };
    };
}

// Scaling units.

void        Interactions :: scale_time( double factor )
{
    _unit_t     *= factor;
    _G          *= pow( factor, 2 );
    _k          *= pow( factor, 2 );
}

void        Interactions :: scale_length( double factor )
{
    _unit_l     *= factor;
    _G          *= 1. / pow( factor, 3 );
    _k          *= pow( factor, 2 );
    _R          *= pow( factor, 3 );
}

void        Interactions :: scale_mass( double factor )
{
    _unit_m     *= factor;
    _G          *= factor;
    _k          *= factor;
}

void        Interactions :: scale_temperature( double factor )
{
    _unit_T     *= factor;
    _k          *= 1. / factor;
}

//////////////////////////////////////////////////////////////////   O U T P U T
