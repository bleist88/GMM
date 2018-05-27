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

void        Interactions :: set_time( double unit_t )
{
    _unit_t         = unit_t;
    _G             *= pow(unit_t, 2);
    _k             *= pow(unit_t, 2);
}

void        Interactions :: set_length( double unit_l )
{
    _unit_l         = unit_l;
    _G             *= 1 / pow(unit_l, 3);
    _k             *= 1 / pow(unit_l, 3);
}

void        Interactions :: set_mass( double unit_m )
{
    _unit_m         = unit_m;
    _G             *= unit_m;
}

void        Interactions :: set_temperature( double unit_T )
{
    _unit_T         = unit_T;
}

//  ////////////////////////////////////////////////////////////////////////////
//  Methods

//  calculations

void        Interactions :: calc_radial( Particle A, Particle B )
{
    _radial     = B.position().subtracted( A.position() );
}

//  interactions

void        Interactions :: gravitate( Particles particles )
{
    for( int i = 0; i < particles.size(); i++ ){
        for( int j = i+1; j < particles.size(); j++ ){
            
            calc_radial( particles.particle(i), particles.particle(j) );

            particles.acceleration(i).add(
                _radial.scaled(
                _G * particles.mass(j) * (1 - exp( -pow(_radial.mag()/particles.body(j), 2) ))  / pow(_radial.mag(), 3)
                )
            );

            particles.acceleration(j).add(
                _radial.scaled(
                -_G * particles.mass(i) * (1 - exp( -pow(_radial.mag()/particles.body(i), 2) )) / pow(_radial.mag(), 3)
                )
            );
        };
    };
}

void        Interactions :: collide( Particles particles )
{
    for( int i = 0; i < particles.size(); i++ ){
        for( int j = i+1; j < particles.size(); j++ ){
            
            particles.acceleration(i).scale( (1 - exp( -_radial.mag() * _radial.mag() / particles.body(i) / particles.body(j) )) );
            particles.acceleration(j).scale( (1 - exp( -_radial.mag() * _radial.mag() / particles.body(i) / particles.body(j) )) );

        };
    };
}

//////////////////////////////////////////////////////////////////   O U T P U T
