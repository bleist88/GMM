#include "Interactions.hh"

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

//  ////////////////////////////////////////////////////////////////////////////
//  Constructors

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

//  ////////////////////////////////////////////////////////////////////////////
//  Members


//  ////////////////////////////////////////////////////////////////////////////
//  Methods

//  calculations.

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

void        Interactions :: gravitate( Particles A, Particles B, double zero )
{
    for( int i = 0; i < A.size(); i++ ){
        for( int j = 0; j < B.size(); j++ ){

            calc_radial( A.particle(i), B.particle(j) );

            if( _radial.mag() > 0.0 ){

                A.acceleration(i).add(
                    _radial.scaled(
                        (_radial.mag() / (_radial.mag() + zero)) *
                            _G * B.mass(j) / pow(_radial.mag(), 3)
                    )
                );

                B.acceleration(i).add(
                    _radial.scaled(
                        (_radial.mag() / (_radial.mag() + zero)) *
                            _G * A.mass(j) / pow(_radial.mag(), 3)
                    )
                );

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
}

void        Interactions :: scale_length( double factor )
{
    _unit_l     *= factor;
}

void        Interactions :: scale_mass( double factor )
{
    _unit_m     *= factor;
}

void        Interactions :: scale_temperature( double factor )
{
    _unit_T     *= factor;
}

//////////////////////////////////////////////////////////////////   O U T P U T
